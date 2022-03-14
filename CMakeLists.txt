cmake_minimum_required(VERSION 3.21)
project(tokenizer_ch)

set(CMAKE_CXX_STANDARD 14)

add_executable(tokenizer_ch main.cpp utf8.h utf8.cpp trieCH.h trieCH.cpp)
