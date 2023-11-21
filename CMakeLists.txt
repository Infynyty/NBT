cmake_minimum_required(VERSION 3.22.3)

project(NBT)

set(CMAKE_CXX_STANDARD 17)

add_executable(NBT NBT.cpp
        NbtTag.cpp
        NbtTag.h)