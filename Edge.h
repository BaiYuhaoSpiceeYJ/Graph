#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include "Vertex.h"

class Edge
{
	friend class Vertex;
	friend class Graph;
	
    private:
        Vertex src;
        Vertex dst;
        int weight;
        int id;
		bool visited;
		
	public:
        Edge();
        Edge(Vertex src,Vertex dst,int weight);
        ~Edge();
        
        //Edge operator=(Edge);

};

#endif // EDGE_H
