add_library(MD5 STATIC 
    ${CMAKE_CURRENT_LIST_DIR}/md5.cpp)

target_include_directories(MD5 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
