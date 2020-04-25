file(GLOB HEADER_FILES *.hpp)
file(GLOB SOURCE_FILES *.cpp)

#add_library(typesLib STATIC ${SOURCE_FILES} ${HEADER_FILES} ../TIPtree.h ../TIPtreePrint.cpp)
add_library(typesLib STATIC ${SOURCE_FILES} ${HEADER_FILES} )
target_link_libraries(typesLib antlr4_static ${llvm_libs} solversLib tipTreeLib)