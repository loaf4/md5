add_library(MD5_lib STATIC 
    ${CMAKE_CURRENT_LIST_DIR}/md5.cpp
    ${CMAKE_CURRENT_LIST_DIR}/elgamal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/analysis.cpp)

target_include_directories(MD5 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
