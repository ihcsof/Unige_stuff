cmake_minimum_required(VERSION 3.3)
project(tcp_ping)

include_directories("../pingpong_lib")

add_executable(tcp_ping tcp_ping.c)
target_link_libraries(tcp_ping pingpong_lib)