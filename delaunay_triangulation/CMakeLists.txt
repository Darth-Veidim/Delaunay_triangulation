cmake_minimum_required(VERSION 3.24)
project(delaunay)

set(CMAKE_CXX_STANDARD 17)

add_executable(delaunay main.cpp Vertex.h Edge.h Triangle.h main.h)
