#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <utility>
using namespace std;

const double eps = 1e-8;

struct line {
    int id;
    double k, b;
    line () {}
    line (int id_, double k_, double b_) :
        id (id_), k (k_), b (b_) {}
};

inline
bool operator< (const line &u, const line &v) {
    if (fabs (u.k - v.k) < eps) return u.b < v.b;
    else return u.k < v.k;
}

inline
double intersect (const line &u, const line &v) {
    return (v.b - u.b) / (u.k - v.k);
}

void insert (deque<line> &Q, line el) {
    while (Q.size ()

            && ((       Q.size () > 1
                    &&  intersect (Q.rbegin()[0], Q.rbegin()[1])
                            >= intersect (el, Q.rbegin()[0]))

                || fabs (Q.rbegin()[0].k - el.k) < eps))

        Q.pop_back ();
    Q.push_back (el);
}



int main () {
    int n;
    scanf ("%d", &n);
    line buf[n];
    for (int i = 0; i < n; i ++) {
        buf[i].id = i;
        scanf ("%lf%lf", &buf[i].k, &buf[i].b);
    }
    sort (buf, buf + n);
    deque<line> Q;
    for (int i = 0; i < n; i ++) insert (Q, buf[i]);
    int visible[n];
    for (int i = 0; i < n; i ++) visible[i] = 0;
    for (deque<line>::iterator i = Q.begin (); i != Q.end (); i ++)
        visible[i->id] = 1;
    for (int i = 0; i < n; i ++)
        if (visible[i]) printf ("%d ", i + 1);
    puts ("");
}
