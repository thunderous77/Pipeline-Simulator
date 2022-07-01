cmake_minimum_required(VERSION 3.16)
project(Pipeline_Simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp CPU.hpp Execute.hpp)
