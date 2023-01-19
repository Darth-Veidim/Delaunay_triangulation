//
// Created by gally on 15.01.2023.
//

#ifndef DELAUNAY_EDGE_H
#define DELAUNAY_EDGE_H

#include "main.h"
#include "Vertex.h"

class Triangle;

class Edge{

public:

    vector<Triangle*>           triangles;
    vector<Vertex*>             vertices;


    Edge(
            Vertex* _a,
            Vertex* _b
            ) {

        vertices.resize(2);

        vertices[0] = _a;
        vertices[1] = _b;

        vertices[0]->edges.push_back(this);
        vertices[1]->edges.push_back(this);

    }

    void output_edge () {
        cout << "1st node: ";
        vertices[0]->output_vertex();

        cout << "2nd node: ";
        vertices[1]->output_vertex();
        cout  << endl;
    }
};

#endif //DELAUNAY_EDGE_H
