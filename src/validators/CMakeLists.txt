file(GLOB HEADER_FILES *.hpp)
file(GLOB SOURCE_FILES *.cpp)

add_library(validatorsLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(validatorsLib tipTreeLib)
