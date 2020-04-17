cmake_minimum_required (VERSION 3.15)
project (SymFun)

file(GLOB Library_Sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" ) 


add_library (SymFun STATIC ${Library_Sources})

target_compile_features(SymFun PUBLIC cxx_std_11)

target_include_directories (SymFun PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



