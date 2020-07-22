add_executable(solvers_tests)
target_sources(solvers_tests
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/UnionFindTest.cpp
        )
target_include_directories(solvers_tests PUBLIC ${CMAKE_SOURCE_DIR}/src/types/solver)
target_link_libraries(solvers_tests types_lib tip_lib)