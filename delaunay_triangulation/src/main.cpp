#include "main.h"

#include "Vertex.h"
#include "Edge.h"
#include "Triangle.h"
#include "center_search.h"

int main() {

    int suppress_output =0;

    cout << "----------------------------------------------------" << endl;
    cout << "   Start of the Delaunay Triangulation Algorithm" << endl;
    cout << "----------------------------------------------------" << endl;

    //      Coordinates of the supertriangle.
    //      For this triangle the square with nodes
    //      (4,6) --- (6,6)
    //       |           |
    //      (4,4) --- (6,4)   lies inside.
    Eigen::Matrix<double, 3, 2> super_triangle{
            {0,  3},
            {10, 3},
            {5,  9}};

    //      Creation of the set of nodes (Voronoi space)
#if 0
    //      Sample of the simple nodes set
    Eigen::Matrix<double,4,2>   coord{
            {5.0,   4.0},
            {4.0,   5.5},
            {6.0,   5.5},
            {5.0,   8.0} };
#else

    //      Randomized Voronoi space
    //      Number of points
    const int points = 777;
    Eigen::Matrix<double, points, 2> coord;
    srand(time(NULL));
    Eigen::IOFormat HeavyFmt(Eigen::FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");

    //      400k and 600k define the square,
    //      which entirely lies in the supertriangle
    int lb = 400000, ub = 600000;
    for (int i = 0; i < points; i++)
        for (int j = 0; j < 2; j++)
            coord(i, j) = ((rand() % (ub - lb + 1)) + lb) / 100000.;

#if suppress_output
    cout << "Set of nodes for triangulation: " << endl;
    cout << coord.format(HeavyFmt);
    cout << endl;
#endif

#endif

    //      Define triangulation pointer;
    vector<Triangle*>       triangulation;
    //      vector, containing points (3) of the supertriangle;
    vector<Vertex*>         allVertices;
    //      vector, containing all vertices.
    vector<Vertex*>         point_sup;
    point_sup.resize(3);

    //      Initialize id for vertices
    int vertex_id =         1;

    for (int i=0; i<3; i++) {
        point_sup[i] = new Vertex(
                            vertex_id++,
                            super_triangle(i, 0),
                            super_triangle(i, 1));

        //  add each of the node to the vector, pointing to vertices
        allVertices.push_back(point_sup[i]);
    }

    //      Define edges of the super triangle
    vector<Edge*>           edges_sup;
    edges_sup.resize(3);
    edges_sup[0] = new Edge(point_sup[0],point_sup[1]);
    edges_sup[1] = new Edge(point_sup[1],point_sup[2]);
    edges_sup[2] = new Edge(point_sup[2],point_sup[0]);

    //      Initialize super triangle
    //      and add it to the triangulation pointers vector
    Triangle tria_super(
            edges_sup[0],
            edges_sup[1],
            edges_sup[2]);
    triangulation.push_back(&tria_super);

    //      Initialize vertices pointers vector
    vector<Vertex*>         point_list;
    point_list.resize(coord.rows());
    for (int i=0; i<coord.rows(); i++) {
        point_list[i] = new Vertex(
                                vertex_id++,
                                coord(i, 0),
                                coord(i, 1));

        //  add each of the node to the vector, pointing to vertices
        allVertices.push_back(point_list[i]);
    }

    //    ----------------------------------------------
    //    Start the triangulation adding one point
    //    from the point_list each iteration
    int iter = 0;

    for (auto & act_point : point_list) {

        iter++;

#if suppress_output
        cout << endl;
        cout << "====================================================" << endl;
        cout << "Point -" << iter << "- added to triangulation" << endl;
        act_point->output_vertex();
        cout << "----------------------------------------------------" << endl;
#endif
        //      Create vector pointing to bad triangles
        vector<Triangle*>           badTria;

        //      Start of a loop along all the triangles in the triangulation
        //      to check if they are good or bad
        for (auto & act_tria : triangulation) {

#if suppress_output
             cout << "New triangle from the triangulation was taken" << endl;
#endif
            //  Find the center of the circumcircle for the current triangle
            Eigen::Vector2d         center = findCircumCenter(
                    act_tria->vertices[0],
                    act_tria->vertices[1],
                    act_tria->vertices[2]
                    );
            //  Find the distances from the circumcircle
            //  to one of the triangle's node (radius) and to the added point
            double r0 = radius(center, act_tria->vertices[0]);
            double r1 = radius(center, act_point);

#if suppress_output
            cout << " - radius of the circumcircle: " << r0 << endl;
            cout << " - distance from center to point: " << r1 << endl << endl;
#endif
            //  If the distance to the added point is smaller than the radius,
            //  the triangle is bad, and it is added to the bad triangles pointers list
            if (r1 < r0) {
                badTria.push_back(act_tria);

#if suppress_output
                cout << " + 1 bad triangle, total: " << badTria.size() << endl << endl;
#endif
            }
        }
#if suppress_output
        cout << endl;
        cout << "Update of the triangulation" << endl;
#endif
        //      Initialize the pointer vector, which contains all edges,
        //      from whic new triangles will be built,
        vector<Edge*>           polygon;
        //      and the pointer vector containing all edges,
        //      which connects bad triangles.
        vector<Edge*>           double_edges;

        //      Add all edges of the bad triangles
        for (int i=0; i<badTria.size(); i++)
            for (int j=0; j<badTria[i]->edges.size(); j++)
                polygon.push_back(badTria[i]->edges[j]);

#if suppress_output
        cout << " - number of all-edges: " << polygon.size() << endl;
#endif
        //      Algorithm to find all edges in polygon, that are written two times,
        //      meaning they are double_edges
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
        //      Delete all double edges from the polygon
        for (int i=polygon.size()-1; i>-1; i--){
            for (int j=0; j<double_edges.size(); j++){
                if (polygon[i]==double_edges[j])
                    polygon.erase(polygon.begin()+i);

            }
        }

#if suppress_output
        cout << " - number of double edges: " << double_edges.size() << endl;
        cout << " - number of polygone edges: " << polygon.size() << endl;
#endif

        //      Delete all pointers to bad triangles from the triangulation
        int size = triangulation.size();

        for (int i = size-1; i>-1; i--) {
            for (int j = 0; j < badTria.size(); j++) {
                if (triangulation[i] == badTria[j]) {
                    triangulation.erase(triangulation.begin()+i);
                }
            }
        }

        //      Create new triangles from the polygon,
        //      and add their pointers to the triangulation
        for (auto & act_edge : polygon) {
            triangulation.push_back(
                    new Triangle(
                            new Edge(act_edge->vertices[0], act_point),
                            new Edge(act_point, act_edge->vertices[1]),
                            act_edge)
                            );
        }

#if suppress_output
        cout << " - size of the updated triangulation: ";
        cout << triangulation.size() << endl;
#endif

#if 0
    //     If point-by-point mesh output is needed
    cout << "----------------------------------------------------" << endl;
    std::ostringstream fn;
    fn << "dt_temp_" << iter << ".msh";

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

    //      Remove all triangles containing the nodes
    //      of the suppertriangle from triangulation
    for (int i = size-1; i>-1; i--) {
        for (int j = 0; j < triangulation[i]->vertices.size(); j++) {
            if (triangulation[i]->vertices[j]->id < 4) {
                triangulation.erase(triangulation.begin() + i);
                break;
            }
        }
    }

    //      Output of the mesh for the GID
    ofstream os("../dt_output.msh");
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
