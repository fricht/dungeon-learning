cmake_minimum_required(VERSION 3.22)
project(
    CPP-PPO
    VERSION 0.0.1
    DESCRIPTION "A c++ PPO project."
    LANGUAGES CXX
)

set(CMAKE_CXX_COMPILER g++)

set(SOURCE_FILE
    src/matrix.hpp
)

add_executable(main src/main.cpp)
