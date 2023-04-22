cmake_minimum_required(VERSION 3.3)
project(pong_server)

include_directories("../pingpong_lib")

add_executable(pong_server pong_server.c)
target_link_libraries(pong_server pingpong_lib)