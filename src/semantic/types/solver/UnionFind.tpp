#include <iostream>
#include <assert.h>
#include "UnionFind.h"

template<class T>
UnionFind<T>::UnionFind(): seeded(false) { }


template<class T>
UnionFind<T>::UnionFind(std::vector<T *> seed) : seeded(true) {
    for(auto &term : seed) {
        edges.insert(std::pair<T *, T *>(term, term));
    }
}

template<class T>
T const * UnionFind<T>::find(T const * t) {
    // Unify on the fly.
    if(!seeded) {
        auto ret = edges.insert(std::pair<T const *, T const *>(t, t));
        std::cout << ret.second << std::endl;
    }

    // TODO (nphair): Add path compression - its practically free performance.
    if(!get_parent(t)) {
        assert(0);
    }

    auto parent = t;
    while(*get_parent(parent) != *parent) {
        parent = get_parent(parent);
    }

    return parent;
}

template<class T>
void UnionFind<T>::quick_union(T const * t1, T const * t2) {
    // TODO (nphair): Weight the subtrees and be smarter about our unioning.
    auto t1_root = find(t1);
    auto t2_root = find(t2);
    if(t1_root == nullptr || t2_root == nullptr) {
        std::cerr << "can't union elements not in structure" << std::endl;
        assert(0);
    }

    edges[t1_root] = t2_root;
}

template<class T>
bool UnionFind<T>::connected(T* t1, T* t2) {
    return *find(t1) == *find(t2);
}

template<class T>
T const * UnionFind<T>::get_parent(T const * t) {
    for(auto const &edge : edges) {
        if(*t == *edge.first) {
            return edge.second;
        }
    }
    assert(0);
}

template<class T>
void UnionFind<T>::print_edges() {
    for(auto const &e : edges) {
        std::cout << *e.first << " --> " << *find(e.first) << ")" << std::endl;
    }
}

template<class T>
std::map<T *, T *>& UnionFind<T>::get_edges() {
    return edges;
}

