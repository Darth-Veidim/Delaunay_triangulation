//
// Created by gally on 16.01.2023.
//
//#include "main.h"
//
//vector<Vertex*> nodes;
//nodes.resize(3);
//
//nodes[0] = new Vertex(6,0);
//nodes[1] = new Vertex(0,0);
//nodes[2] = new Vertex(0,8);
//
//for (int i=0; i<3; i++)
//nodes[i]->output_vertex();
//
//vector<Edge*> edges;
//edges.resize(3);
//edges[0] = new Edge(nodes[0],nodes[1]);
//edges[1] = new Edge(nodes[1],nodes[2]);
//edges[2] = new Edge(nodes[2],nodes[0]);
//
//for (int i=0; i<3; i++)
//edges[i]->output_edge();
//
//cout << "check connectivity between nodes and edges" << endl;
//cout << nodes[2]->edges[0] << endl;
//nodes[2]->edges[0]->output_edge();
//
//cout << nodes[2]->edges[1] << endl;
//nodes[2]->edges[1]->output_edge();
//
//Triangle tri1(edges[0], edges[1], edges[2]);
//
//cout << "check what happends with triangles" << endl;
//tri1.edges[0]->output_edge();
//for (int i=0; i<3; i++) {
//tri1.vertices[i]->output_vertex();
//cout << "pointer from node to triangle" << nodes[i]->triangles[0] << endl;
//}
//
//findCircumCenter(nodes[0], nodes[1], nodes[2]);