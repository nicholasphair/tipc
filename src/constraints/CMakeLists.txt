file(GLOB HEADER_FILES *.hpp)
file(GLOB SOURCE_FILES *.cpp)

add_library(constraintsLib STATIC ${SOURCE_FILES} ${HEADER_FILES} )
target_link_libraries(constraintsLib antlr4_static ${llvm_libs} solversLib tipTreeLib typesLib)
