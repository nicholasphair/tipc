#ifndef TIPC_UNIONFIND_H
#define TIPC_UNIONFIND_H
#include <map>
#include "Term.hpp"
#include <vector>

class UnionFind {
public:
    UnionFind() = delete ;
    UnionFind(std::vector<Term *> edges);

    Term * find(Term * t);
    void quick_union(Term * t1, Term * t2);
    bool connected(Term * t1, Term * t2);
    void print_edges();
private:
    // A mapping from terms to parents.
    Term * get_parent(Term *);
    std::map<Term *, Term *> edges;

};


#endif //TIPC_UNIONFIND_H
