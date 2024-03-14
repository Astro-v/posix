cmake_minimum_required(VERSION 3.0)

project(PosixSever)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib-posix)

add_subdirectory(server)