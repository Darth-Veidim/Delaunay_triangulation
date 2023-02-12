cmake_minimum_required(VERSION 3.24)
project(delaunay)

set(CMAKE_CXX_STANDARD 17)

add_executable(delaunay source/main.cpp include/Vertex.h include/Edge.h include/Triangle.h include/main.h source/center_search.cpp include/center_search.h)
