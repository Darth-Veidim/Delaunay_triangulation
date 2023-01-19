//
// Created by gally on 15.01.2023.
//

#ifndef DELAUNAY_VERTEX_H
#define DELAUNAY_VERTEX_H

#include "main.h"

class Edge;
class Triangle;

class Vertex {

public:
    int                         id;
    const Eigen::Vector2d       x;

    vector<Edge*>               edges;
    vector<Triangle*>           triangles;

public:
    Vertex(int _i, double _x, double _y) : id{_i}, x{_x, _y} {};

    Vertex(double _x, double _y) : x{_x, _y} {};

    ~Vertex(){
        delete &x;
    };

    void output_vertex () {
        cout << "x: " << x(0) << ", y: " << x(1) << endl;
    }

    void output_msh (ostream &os) {
        os << setw(6) << id;

        os << setw(16) << setprecision(8) << scientific;
        os << setw(16) << x[0];
        os << setw(16) << x[1];
        os << setw(16) << 0.0 << endl;
    }



};

#endif //DELAUNAY_VERTEX_H
