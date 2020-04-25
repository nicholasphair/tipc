file(GLOB SOURCE_FILES *.cpp)

add_executable(solvers_tests ${SOURCE_FILES})
target_link_libraries(solvers_tests solversLib)
