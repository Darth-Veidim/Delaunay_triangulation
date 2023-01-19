#include "main.h"
#include "Vertex.h"
#include "Edge.h"
#include "Triangle.h"

#define pdd pair<double, double>

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

int main() {

    cout << "----------------------------------------------------" << endl;
    cout << "   Start of the Delaunay Triangulation Algorithm" << endl;
    cout << "----------------------------------------------------" << endl;

    Eigen::Matrix<double,3,2>   super_triangle {
            {0,     3},
            {10,    3},
            {5,     9}};

    //    Creation of the set of nodes
#if 0
    Eigen::Matrix<double,4,2>   coord{
            {5.0,   4.0},
            {4.0,   5.5},
            {6.0,   5.5},
            {5.0,   8.0} };
#else
    const int points = 100;
    Eigen::Matrix<double,points,2> coord;

    Eigen::IOFormat HeavyFmt(Eigen::FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");
    int lb = 400000, ub = 600000;
    for (int i=0; i<points; i++)
        for (int j=0; j<2; j++)
            coord(i,j) = ((rand() % (ub - lb + 1)) + lb)/100000.;

    cout << "Set of nodes for triangulation: " << endl;
    cout << coord.format(HeavyFmt);
    cout << endl;

#endif

    vector<Triangle*> triangulation;
    vector<Vertex*> point_sup;
    vector<Vertex*> allVertices;

    int vertex_iter = 1;

    point_sup.resize(3);

    for (int i=0; i<3; i++) {
        point_sup[i] = new Vertex(
                                vertex_iter++,
                                super_triangle(i, 0),
                                super_triangle(i, 1));
        allVertices.push_back(point_sup[i]);
    }

    vector<Edge*> edges_sup;
    edges_sup.resize(3);
    edges_sup[0] = new Edge(point_sup[0],point_sup[1]);
    edges_sup[1] = new Edge(point_sup[1],point_sup[2]);
    edges_sup[2] = new Edge(point_sup[2],point_sup[0]);

    Triangle tria_super(edges_sup[0],edges_sup[1],edges_sup[2]);
    triangulation.push_back(&tria_super);

    vector<Vertex*> point_list;

    point_list.resize(coord.rows());

    for (int i=0; i<coord.rows(); i++) {
        point_list[i] = new Vertex(
                                vertex_iter++,
                                coord(i, 0),
                                coord(i, 1));
        allVertices.push_back(point_list[i]);
    }

//    ----------------------------------------------
//    Start of the iterations along all new points

    int iter = 0;

    for (auto & act_point : point_list) {

        iter++;
        cout << endl;
        cout << "====================================================" << endl;
        cout << "Point -" << iter << "- added to triangulation" << endl;
        act_point->output_vertex();
        cout << "----------------------------------------------------" << endl;

        vector<Triangle*> badTria;

        for (auto & act_tria : triangulation) {

             cout << "New triangle from the triangulation was taken" << endl;

            Eigen::Vector2d center = findCircumCenter(act_tria->vertices[0],
                                                      act_tria->vertices[1],
                                                      act_tria->vertices[2]);

            double r0 = radius(center, act_tria->vertices[0]);
            double r1 = radius(center, act_point);

            cout << " - radius of the circumcircle: " << r0 << endl;
            cout << " - distance from center to point: " << r1 << endl << endl;

            if (r1 < r0) {
                badTria.push_back(act_tria);
                cout << " + 1 bad triangle, total: " << badTria.size() << endl << endl;
            }
        }
        cout << endl;
        cout << "Update of the triangulation" << endl;

        vector<Edge*> polygon;
        vector<Edge*> double_edges;

        for (int i=0; i<badTria.size(); i++) {
            for (int j=0; j<badTria[i]->edges.size(); j++) {
                polygon.push_back(badTria[i]->edges[j]);
            }
        }
        cout << " - number of all-edges: " << polygon.size() << endl;

        for (int i=0; i<polygon.size(); i++){
            for (int j=0; j<polygon.size(); j++){
                if (i != j) {
                    if ( (polygon[i]->vertices[0]->id == polygon[j]->vertices[0]->id &&\
                          polygon[i]->vertices[1]->id == polygon[j]->vertices[1]->id) ||\
                         (polygon[i]->vertices[0]->id == polygon[j]->vertices[1]->id &&\
                          polygon[i]->vertices[1]->id == polygon[j]->vertices[0]->id) ) {
                        double_edges.push_back(polygon[i]);
                    }
                }
            }
        }
        for (int i=polygon.size()-1; i>-1; i--){
            for (int j=0; j<double_edges.size(); j++){
                if (polygon[i]==double_edges[j])
                    polygon.erase(polygon.begin()+i);

            }
        }

        cout << " - number of double edges: " << double_edges.size() << endl;
        cout << " - number of polygone edges: " << polygon.size() << endl;

        int size = triangulation.size();

        for (int i = size-1; i>-1; i--) {
            for (int j = 0; j < badTria.size(); j++) {
                if (triangulation[i] == badTria[j]) {
                    triangulation.erase(triangulation.begin()+i);
                }
            }
        }

        for (auto & act_edge : polygon) {
            triangulation.push_back(
                    new Triangle(
                            new Edge(act_edge->vertices[0], act_point),
                            new Edge(act_point, act_edge->vertices[1]),
                            act_edge)
                            );
        }

        cout << " - size of the updated triangulation: ";
        cout << triangulation.size() << endl;


#if 0
        cout << "----------------------------------------------------" << endl;
    std::ostringstream fn;
    fn << "C:\\Users\\gally\\Desktop\\dt_temp_" << iter << ".msh";

    ofstream os(fn.str());
        os << "mesh dimension 2 elemtype triangle nnode 3" << endl;

        os << "coordinates" << endl;
        for(auto & i : allVertices)
            i->output_msh(os);
        os << "end coordinates" << endl;

        os << "elements" << endl;
        int temp = 1;
        for(auto & i : triangulation) {
            os << setw(6) << temp++;
            i->output_msh(os);
        }
        os << "end elements" << endl;

        os.close();
#endif

    }

    int size = triangulation.size();

    for (int i = size-1; i>-1; i--) {
//        cout << "iterator: " << i << endl;
        for (int j = 0; j < triangulation[i]->vertices.size(); j++) {
//            cout << "we check vertex: " << triangulation[i]->vertices[j]->id << endl;
            if (triangulation[i]->vertices[j]->id < 4) {
                triangulation.erase(triangulation.begin() + i);
//                cout << "triangle erased, num of triangles left: " << triangulation.size() << endl;
                break;
            }
        }
    }

    ofstream os("C:\\Users\\gally\\Desktop\\dt_output.msh");
    os << "mesh dimension 2 elemtype triangle nnode 3" << endl;

    os << "coordinates" << endl;
    for(auto & i : allVertices)
        if (i->id>3)
            i->output_msh(os);
    os << "end coordinates" << endl;

    os << "elements" << endl;
    int temp = 1;
    for(auto & i : triangulation) {
        os << setw(6) << temp++;
        i->output_msh(os);
    }
    os << "end elements" << endl;

    os.close();

    cout << endl;
    cout << "====================================================" << endl;
    cout << "           Triangular mesh was created" << endl;

    cout << "     number of triangles in the triangulation: ";
    cout << triangulation.size() << endl;
    cout << "====================================================" << endl;
}
