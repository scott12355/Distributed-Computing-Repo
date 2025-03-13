cmake_minimum_required(VERSION 3.30)
project(Ex15)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ex15 main.cpp
        cmake-build-debug/old.cpp
        cmake-build-debug/old.h)
