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

/*Edge Edge::operator=(Edge e)
{
	Edge new_e;
	new_e.src = e.src;
	new_e.dst = e.dst;
	new_e.weight = e.weight;
	new_e.id = e.id;
	return new_e;
}*/
