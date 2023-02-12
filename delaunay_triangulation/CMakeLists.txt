cmake_minimum_required(VERSION 3.24)
project(delaunay)

set(CMAKE_CXX_STANDARD 17)

add_executable(delaunay src/main.cpp src/Vertex.h src/Edge.h src/Triangle.h src/main.h src/center_search.cpp src/center_search.h)
