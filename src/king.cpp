/// -Ivendor/king
/// vendor/king/grader.cpp
#include <vector>

#include "king.h"

using namespace std;

typedef int flea_t;

const int bf_and = 8, bf_not_a = 3, bf_xor = 6;

struct a_plus_1_seg {
    int n;
    vector<flea_t> tree;

    void build_tree(int id, int lb, int rb) {
        if (lb == rb) tree[id] = lb;
        else {
            int mid = (lb + rb) >> 1;
            build_tree(id << 1, lb, mid);
            build_tree(id << 1 | 1, mid + 1, rb);
            tree[id] = add_flea(tree[id << 1], tree[id << 1 | 1], bf_and);
        }
    }

    flea_t query_tree(int r, int id, int lb, int rb) {
        if (r > rb) r = rb;
        if (r == rb) return tree[id];

        else {
            int mid = (lb + rb) >> 1;
            if (r <= mid)
                return query_tree(r, id << 1, lb, mid);
            else
                return add_flea(
                        tree[id << 1],
                        query_tree(r, id << 1 | 1, mid + 1, rb),
                        bf_and);

        }
    }

    a_plus_1_seg(int n_) : n(n_), tree((unsigned long) 4 * (n_ + 1)) { }

    void go() {
        build_tree(1, 0, n - 1);
        set_output(0, add_flea(0, 0, bf_not_a));
        for (int i = 1; i < n; i ++)
            set_output(i, add_flea(i, query_tree(i - 1, 1, 0, n - 1), bf_xor));
    }
};

struct a_plus_1_fenwick {
    int n;
    vector<flea_t> tree, res;

    a_plus_1_fenwick(int n_) : n(n_), tree((unsigned long) n_ + 1), res((unsigned long) n_ + 1) { }

    int lowbit(int i) {
        return i & - i;
    }

    void go() {
        for (int i = 0; i < n - 1; i ++) tree[i + 1] = i;

        for (int M = 1; 1 << M < n - 1; M ++)
            for (int i = 1 << M; i <= n - 1; i += 1 << M) {
                tree[i] = add_flea(tree[i], tree[i - (1 << (M - 1))], bf_and);
            }

        set_output(0, res[0] = add_flea(0, 0, bf_not_a));
        for (int i = 1; i < n; i ++) {
            int vx = i - lowbit(i);
            if (vx == 0)
                set_output(i, add_flea(i, res[i] = tree[i], bf_xor));
            else
                set_output(i,
                           add_flea(i, res[i] = add_flea(tree[i], res[vx], bf_and),
                                    bf_xor));
        }
    }
};

void build_computer(int task_id, int n, int M, int T) {
    if (task_id == 1) {
        if (M >= 915024) a_plus_1_seg(n).go();
        else a_plus_1_fenwick(n).go();
    }
}
