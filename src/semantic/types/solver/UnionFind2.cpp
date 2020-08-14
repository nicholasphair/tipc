#include <iostream>
#include <assert.h>
#include "UnionFind.h"
#include "UnionFind2.h"

UnionFind2::UnionFind2(): seeded(false) { }

UnionFind2::UnionFind2(std::vector<std::shared_ptr<TipType>> seed): seeded(true) {
    for(auto &term : seed) {
        edges.insert(std::pair<std::shared_ptr<TipType>, std::shared_ptr<TipType>>(term, term));
    }
}

std::shared_ptr<TipType> UnionFind2::find(std::shared_ptr<TipType> t) {
    // Unify on the fly.
    if(!seeded) {
        auto ret = edges.insert(std::pair<std::shared_ptr<TipType>, std::shared_ptr<TipType>>(t, t));
        if (ret.second==false) {
            std::cout << "element 't' already existed" << std::endl;
        }
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

void UnionFind2::quick_union(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) {
    // TODO (nphair): Weight the subtrees and be smarter about our unioning.
    auto t1_root = find(t1);
    auto t2_root = find(t2);
    if(t1_root == nullptr || t2_root == nullptr) {
        std::cerr << "can't union elements not in structure" << std::endl;
        assert(0);
    }

    edges[t1_root] = t2_root;

}

bool UnionFind2::connected(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) {
    return *find(t1) == *find(t2);
}

void UnionFind2::print_edges() {
    for(auto const &e : edges) {
        std::cout << *e.first << " --> " << *find(e.first) << ")" << std::endl;
    }
}

std::map<std::shared_ptr<TipType>, std::shared_ptr<TipType>> &UnionFind2::get_edges() {
    return edges;
}

std::shared_ptr<TipType> UnionFind2::get_parent(std::shared_ptr<TipType> t) {
    for(auto const &edge : edges) {
        if(*t == *edge.first) {
            return edge.second;
        }
    }
    assert(0);
}
