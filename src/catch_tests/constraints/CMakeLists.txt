file(GLOB SOURCE_FILES *.cpp)

add_executable(constraints_tests ${SOURCE_FILES})
target_link_libraries(constraints_tests tipTreeLib typesLib constraintsLib validatorsLib testUtilsLib)
