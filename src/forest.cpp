#include <iostream>

const int __ = 400000;

using namespace std;

struct Node {
    int x;

    template<typename X>
    X &_(X y[]) {
        return y[x];
    }

    operator int() const {
        return x;
    }

    Node operator-() {
        return Node(-x);
    }

    int flag();
    void push();

    void update();

    Node() { }

    Node(int x_) : x(x_) { }

    void rotate();
    void splay();
    void access();
    void reverse();
} c[2][__], par[__];

int mx[__], mxdir[__], val[__], rev[__];

bool operator==(const Node &x, const Node &y) {
    return x.x == y.x;
}

int Node::flag() {
    return _(par)._(c[1]) == *this;
}

void Node::reverse() {
    _(rev) = !_(rev);
    swap(_(c[0]), _(c[1]));
}

void Node::push() {
    if (_(rev)) {
        _(rev) = 0;
        if (_(c[0]) > 0) _(c[0])._(rev) ^= 1;
        if (_(c[1]) > 0) _(c[1])._(rev) ^= 1;
    }
}

void Node::update() {
    _(mx) = _(val);
    _(mxdir) = -1;
    if (_(c[0]) > 0 && _(c[0])._(mx) > _(mx)) _(mx) = _(c[0])._(mx), _(mxdir) = 0;
    if (_(c[1]) > 0 && _(c[1])._(mx) > _(mx)) _(mx) = _(c[1])._(mx), _(mxdir) = 1;
}

void Node::rotate() {
    Node p = _(par), g = p._(par);
    int fx = flag(), fp = g > 0 ? p.flag() : -1;
    Node r = _(c[!fx]);

    p.push();
    push();

    if (r) r._(par) = p;
    p._(par) = x;
    _(par) = g;

    if (g > 0) g._(c[fp]) = x;
    _(c[!fx]) = p;
    p._(c[fx]) = r;
}

void Node::splay() {
    for (; _(par) > 0; rotate())
        if (_(par)._(par) > 0) {
            if (flag() == _(par).flag())
                _(par).rotate();
            else
                rotate();
        }
}

void Node::access() {
    splay();
    push();

    if(_(c[1])) {
        _(c[1])._(par) = -*this;
        _(c[1]) = Node(0);
        update();
    }

    if(_(par) < 0) {
        Node w = -_(par);
        w.access();
        w._(c[1]) = *this;
        _(par) = w;
        w.update();
        rotate();
    }
}
int main() {

}
