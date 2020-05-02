#include "UnionFind.h"
#include <iostream>
#include <assert.h>

UnionFind::UnionFind(std::vector<Term *> seed) {
    for(auto term : seed) {
        edges.insert(std::pair<Term *, Term *>(term, term));
    }
    std::cout << "EDGES SIZE: " << edges.size() << std::endl;
}

Term *UnionFind::find(Term *t) {
    Term * parent = get_parent(t);
    if(!parent) {
        assert(0);
    }

    while(*get_parent(parent) != *parent) {
        parent = get_parent(parent);
    }
    return parent;
}

void UnionFind::quick_union(Term *t1, Term *t2) {
    Term * t1_root = get_parent(t1);
    Term * t2_root = get_parent(t2);
    if(t1_root == nullptr || t2_root == nullptr) {
        std::cout << "can't union elements not in structure" << std::endl;
        assert(0);
    }

    edges[t1_root] = t2_root;
}

bool UnionFind::connected(Term *t1, Term *t2) {
    return *find(t1) == *find(t2);
}

Term *UnionFind::get_parent(Term * term) {
    return edges[term];
}

void UnionFind::print_edges() {
    std::cout << "EDGES SIZE: " << edges.size() << std::endl;
    for(auto e : edges) {
        std::cout << e.first->toString() << "--> parent(" << e.second->toString() << ")" << std::endl;
    }
}
