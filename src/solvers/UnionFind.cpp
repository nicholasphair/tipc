#include "UnionFind.h"
#include <iostream>

UnionFind::UnionFind(std::vector<Term *> seed) {
    for(auto term : seed) {
        edges.insert(std::pair<Term *, Term *>(term, term));
    }
}

Term *UnionFind::find(Term *t) {
    Term * parent = get_parent(t);
    if(!parent) {
        return nullptr;
    }

    while(get_parent(parent) != parent) {
        parent = get_parent(parent);
    }
    return parent;
}

void UnionFind::quick_union(Term *t1, Term *t2) {
    Term * t1_root = get_parent(t1);
    Term * t2_root = get_parent(t2);
    if(t1_root == nullptr || t2_root == nullptr) {
        std::cout << "can't union elements not in structure" << std::endl;
        return;
    }

    edges[t1_root] = t2_root;
}

bool UnionFind::connected(Term *t1, Term *t2) {
    auto f = find(t1);
    auto f2 = find(t2);
    return find(t1) == find(t2);
}

Term *UnionFind::get_parent(Term * term) {
    return edges[term];
}

