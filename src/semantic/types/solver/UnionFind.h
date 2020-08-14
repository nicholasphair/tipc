#pragma once

#include <map>
#include <vector>

template <class T>
class UnionFind {
public:
    UnionFind();
    explicit UnionFind(std::vector<T *> seed);
    ~UnionFind() = default;
    UnionFind(const UnionFind& other) = default;
    UnionFind(UnionFind&& other) noexcept = default;
    UnionFind& operator=(const UnionFind& other) = default;
    UnionFind& operator=(UnionFind&& other) noexcept = default;

    T const * find(T const * t);
    void quick_union(T const * t1, T const * t2);
    bool connected(T * t1, T * t2);
    void print_edges();
    std::map<T *, T *>& get_edges();
private:
    // A mapping from terms to parents.
    T const * get_parent(T const *);
    bool seeded;
    std::map<T const *, T const *> edges;

};

#include "UnionFind.tpp"
