file(GLOB SOURCE_FILES *.cpp)

#add_executable(types_tests ${SOURCE_FILES}
#../../TIPtreeGen.cpp
#../../TIPtreePrint.cpp
#        )
add_executable(types_tests ${SOURCE_FILES})
target_link_libraries(types_tests typesLib tipTreeLib)
