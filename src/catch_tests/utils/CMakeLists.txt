file(GLOB SOURCE_FILES *.cpp)

add_library(testUtilsLib ${SOURCE_FILES})
target_link_libraries(testUtilsLib tipTreeLib validatorsLib)
