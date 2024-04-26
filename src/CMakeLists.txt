set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRC})

add_subdirectory(md5)

target_link_libraries(${PROJECT_NAME} MD5_lib)
target_link_libraries(${PROJECT_NAME} Boost::boost)
