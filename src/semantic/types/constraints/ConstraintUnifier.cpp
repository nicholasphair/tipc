#include "ConstraintUnifier.h"

// once we call this the rawptr is stored which i think is a weak reference. Then
// we return and no object is using the shared_ptr so the destructor is called...
void ConstraintUnifier::handle(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) {
    std::cout << i << std::endl;
    unifier.unify(t1, t2);
    i++;
}

