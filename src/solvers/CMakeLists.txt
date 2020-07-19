add_library(solvers_lib STATIC)
target_sources(solvers_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/UnificationError.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UnificationError.h
        ${CMAKE_CURRENT_SOURCE_DIR}/UnionFind.tpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UnionFind.h
        )
