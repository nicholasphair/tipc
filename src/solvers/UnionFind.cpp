#include "UnionFind.h"
#include <iostream>
#include <assert.h>

UnionFind::UnionFind(std::vector<Term *> seed) {
    for(auto term : seed) {
        edges.insert(std::pair<Term *, Term *>(term, term));
    }
}

Term *UnionFind::find(Term *t) {
    if(!get_parent(t)) {
        assert(0);
    }

    Term * parent = t;
    while(*get_parent(parent) != *parent) {
        parent = get_parent(parent);
    }

    // HACK (nphair): Wrap parent in a get_parent call so we don't introduce a term that
    // is equal but not identical.
    return get_parent(parent);
}

void UnionFind::quick_union(Term *t1, Term *t2) {
    Term * t1_root = find(t1);
    Term * t2_root = find(t2);
    if(t1_root == nullptr || t2_root == nullptr) {
        std::cerr << "can't union elements not in structure" << std::endl;
        assert(0);
    }

    edges[t1_root] = t2_root;
}

bool UnionFind::connected(Term *t1, Term *t2) {
    return *find(t1) == *find(t2);
}

Term *UnionFind::get_parent(Term * term) {
    for(auto t : edges) {
        if(*t.first == *term) return t.second;
    }
    assert(0);
}

void UnionFind::print_edges() {
    for(auto e : edges) {
        std::cout << e.first->toString() << " --> " << find(e.first)->toString() << ")" << std::endl;
    }
}
