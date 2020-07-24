add_executable(types_test)
target_sources(types_test
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipAlphaTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipIntTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipRefTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipVarTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/constraints/ConstraintGenerationTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/constraints/TypeConstraintTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/solvers/UnionFindTest.cpp
        # TODO
        #${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipMuTest.cpp
        )
target_include_directories(types_test
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src/types/concrete
        ${CMAKE_SOURCE_DIR}/src/types/constraints
        ${CMAKE_SOURCE_DIR}/src/types/solver
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete
        )
target_link_libraries(types_test types_lib tip_lib test_helpers)



#file(GLOB SOURCE_FILES *.cpp)
#
#add_executable(constraints_tests ${SOURCE_FILES})
#target_link_libraries(constraints_tests tipTreeLib typesLib constraintsLib validatorsLib testUtilsLib)
