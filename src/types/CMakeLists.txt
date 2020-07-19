add_library(types_lib STATIC)
target_sources(types_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Cons.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Cons.h
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Mu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Mu.h
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Term.h
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Var.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract/Var.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipAlpha.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipAlpha.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipFunction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipInt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipInt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipMu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipMu.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipRef.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipRef.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipType.h
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipVar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concrete/TipVar.h
        )
target_include_directories(types_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/abstract)

