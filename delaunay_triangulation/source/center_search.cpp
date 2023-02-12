#include "../include/center_search.h"

void lineFromPoints(
        Vertex* _v1,
        Vertex* _v2,
        double &a,
        double &b,
        double &c
)
{
    a = _v2->x[1] - _v1->x[1];
    b = _v1->x[0] - _v2->x[0];
    c = a*(_v1->x[0])+ b*(_v1->x[1]);
}

// Function which converts the input line to its
// perpendicular bisector. It also inputs the points
// whose mid-point lies on the bisector
void perpendicularBisectorFromLine(
        Vertex* _v1,
        Vertex* _v2,
        double &a,
        double &b,
        double &c
)
{
    pdd mid_point = make_pair((_v1->x[0] + _v2->x[0])/2,
                              (_v1->x[1] + _v2->x[1])/2);

    // c = -bx + ay
    c = -b*(mid_point.first) + a*(mid_point.second);

    double temp = a;
    a = -b;
    b = temp;
}

// Returns the intersection point of two lines
pdd lineLineIntersection(double a1, double b1, double c1,
                         double a2, double b2, double c2)
{
    double determinant = a1*b2 - a2*b1;
    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return make_pair(FLT_MAX, FLT_MAX);
    }

    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return make_pair(x, y);
    }
}
double radius (
        Eigen::Vector2d center,
        Vertex* _v1
) {

    double a, b;

    a = center[0] - _v1->x[0];
    b = center[1] - _v1->x[1];

    return sqrt(a*a + b*b);
}

Eigen::Vector2d findCircumCenter(
        Vertex* _v1,
        Vertex* _v2,
        Vertex* _v3
)
{
    // Line PQ is represented as ax + by = c
    double a, b, c;
    lineFromPoints(_v1, _v2, a, b, c);

    // Line QR is represented as ex + fy = g
    double e, f, g;
    lineFromPoints(_v2, _v3, e, f, g);

    // Converting lines PQ and QR to perpendicular
    // vbisectors. After this, L = ax + by = c
    // M = ex + fy = g
    perpendicularBisectorFromLine(_v1, _v2, a, b, c);
    perpendicularBisectorFromLine(_v2, _v3, e, f, g);

    // The point of intersection of L and M gives
    // the circumcenter
    pdd circumcenter =
            lineLineIntersection(a, b, c, e, f, g);

    Eigen::Vector2d center{circumcenter.first,circumcenter.second};
    return center;
}
