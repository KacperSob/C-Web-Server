add_library(server_lib SHARED server.c)

target_include_directories(server_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})