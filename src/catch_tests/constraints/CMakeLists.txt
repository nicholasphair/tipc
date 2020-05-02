file(GLOB SOURCE_FILES *.cpp)

add_executable(constraints_tests ${SOURCE_FILES})
target_link_libraries(constraints_tests antlr4_static ${llvm_libs} solversLib tipTreeLib typesLib constraintsLib)
