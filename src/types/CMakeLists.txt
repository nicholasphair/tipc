add_library(types_lib STATIC)
target_sources(types_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Cons.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Cons.h
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Mu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Mu.h
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Term.h
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Var.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Var.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipAlpha.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipAlpha.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipFunction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipInt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipInt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipMu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipMu.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipRef.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipRef.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipType.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipVar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipVar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/constraints/TypeConstraintVisitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/constraints/TypeConstraintVisitor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/constraints/TypeConstraint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/constraints/TypeConstraint.h
        ${CMAKE_CURRENT_SOURCE_DIR}/solver/UnificationError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/solver/UnificationError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/solver/Unifier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/solver/Unifier.h
        ${CMAKE_CURRENT_SOURCE_DIR}/solver/UnionFind.h
        ${CMAKE_CURRENT_SOURCE_DIR}/solver/UnionFind.tpp
        )
target_include_directories(types_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete
        ${CMAKE_CURRENT_SOURCE_DIR}/constraints
        )

