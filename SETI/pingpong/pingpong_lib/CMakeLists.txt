cmake_minimum_required(VERSION 3.3)
project(pingpong_lib)

add_library(pingpong_lib fail.c readwrite.c statistics.c)