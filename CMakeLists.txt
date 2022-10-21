cmake_minimum_required(VERSION 3.23)
project(biseccion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(biseccion
        Biseccion.cpp
        Biseccion.h)
