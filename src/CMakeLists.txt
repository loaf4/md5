set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

add_executable(${PROJECT_NAME} SRC)

add_subdirectory(md5)

target_link_libraries(${PROJECT_NAME} MD5)
