cmake_minimum_required(VERSION 3.28)
project(web_server.out)
add_executable(${PROJECT_NAME} main.c)

set( CMAKE_CXX_FLAGS "-g" )

target_link_libraries(${PROJECT_NAME} server_lib)

add_subdirectory(lib)
