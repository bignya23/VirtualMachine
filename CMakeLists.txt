cmake_minimum_required(VERSION 3.29)
project(VMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(VMachine
        src/headers/tokenizer.hpp
        src/main.cpp
        src/tokenizer.cpp
        src/parser.cpp
        src/execution.cpp
        src/headers/parser.hpp
        src/headers/labelsprocess.hpp
        src/labels.cpp)
