#ifndef DELAUNAY_CENTER_SEARCH_H
#define DELAUNAY_CENTER_SEARCH_H

#include "main.h"

#include "Vertex.h"
#include "Edge.h"
#include "Triangle.h"

void lineFromPoints(
        Vertex* _v1,
        Vertex* _v2,
        double &a,
        double &b,
        double &c
);

void perpendicularBisectorFromLine(
        Vertex* _v1,
        Vertex* _v2,
        double &a,
        double &b,
        double &c
);

pdd lineLineIntersection(
        double a1, double b1, double c1,
        double a2, double b2, double c2);

double radius (
        Eigen::Vector2d center,
        Vertex* _v1
);

Eigen::Vector2d findCircumCenter(
        Vertex* _v1,
        Vertex* _v2,
        Vertex* _v3
);

#endif //DELAUNAY_CENTER_SEARCH_H
