#pragma once

#include <map>
#include <vector>
#include <TipType.h>

class UnionFind2 {
public:
    UnionFind2();
    explicit UnionFind2(std::vector<std::shared_ptr<TipType>> seed);
    ~UnionFind2() = default;

    std::shared_ptr<TipType> find(std::shared_ptr<TipType> t1);
    void quick_union(std::shared_ptr<TipType> t1, std::shared_ptr<TipType>t2);
    bool connected(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2);
    void print_edges();
    std::map<std::shared_ptr<TipType>, std::shared_ptr<TipType>>& get_edges();
private:
    // A mapping from terms to parents.
    bool seeded;
    std::shared_ptr<TipType> get_parent(std::shared_ptr<TipType>);
    std::map<std::shared_ptr<TipType>, std::shared_ptr<TipType>> edges;

};

