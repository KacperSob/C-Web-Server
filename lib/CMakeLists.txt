add_library(server_lib SHARED server.c fileintegration.c posthandler.c)

target_include_directories(server_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
