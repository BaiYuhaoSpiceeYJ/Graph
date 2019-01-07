#include "Edge.h"
#include "Vertex.h"

using namespace std;
Edge::Edge(Vertex src,Vertex dst,int weight)
{
    this->src=src;
    this->dst=dst;
    this->weight=weight;
}

Edge::~Edge()
{
    
}

Edge::Edge()
{
	
}


