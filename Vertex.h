#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <string>
using namespace std;


class Vertex
{
	friend class Graph;
	friend class Edge;
	
    private:
        int id;
        string nom;
        int visited;
  
	public:
        Vertex(int id,string nom);
        Vertex(int id);
        Vertex(string nom);
        Vertex();
        ~Vertex();


};

#endif // VERTEX_H
