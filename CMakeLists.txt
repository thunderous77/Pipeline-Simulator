cmake_minimum_required(VERSION 3.16)
project(Pipeline_Simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pipeline_Simulator main.cpp CPU.hpp Execute.hpp)
