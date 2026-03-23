cmake_minimum_required(VERSION 4.1)
project(RV1)

set(CMAKE_CXX_STANDARD 20)

add_executable(RV1 main.cpp
        classes/TextCategorization.cpp
        classes/TextCategorization.h
        classes/Token.h
        classes/Token.cpp
        classes/Util.h
        classes/Util.cpp
)
