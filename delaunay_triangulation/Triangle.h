//
// Created by gally on 15.01.2023.
//

#ifndef DELAUNAY_TRIANGLE_H
#define DELAUNAY_TRIANGLE_H

#include "Vertex.h"
#include "Edge.h"
#include "main.h"

class Triangle{

public:

    vector<Edge*>               edges;
    vector<Vertex*>             vertices;

public:

    Triangle(
            Edge* _a,
            Edge* _b,
            Edge* _c
            ) {

        edges.resize(3);
        edges[0] = _a;
        edges[1] = _b;
        edges[2] = _c;

        edges[0]->triangles.push_back(this);
        edges[1]->triangles.push_back(this);
        edges[2]->triangles.push_back(this);

        vertices.resize(3);
        vertices[0] = edges[0]->vertices[0];
        vertices[1] = edges[0]->vertices[1];
        vertices[2] = edges[1]->vertices[1];

        vertices[0]->triangles.push_back(this);
        vertices[1]->triangles.push_back(this);
        vertices[2]->triangles.push_back(this);
    }

    void output_msh (ostream &os) {
        for (int i=0; i<3; i++)
            os << setw(6) << vertices[i]->id;

        os << endl;

    }

};

#endif //DELAUNAY_TRIANGLE_H
