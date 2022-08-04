cmake_minimum_required(VERSION 3.22)
project(LIB C)

set(CMAKE_C_STANDARD 99)

add_executable(LIB main.c frac.h pch.h pch.c frac.c)
