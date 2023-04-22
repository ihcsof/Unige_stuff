cmake_minimum_required(VERSION 3.3)
project(udp_ping)

include_directories("../pingpong_lib")

add_executable(udp_ping udp_ping.c)
target_link_libraries(udp_ping pingpong_lib)