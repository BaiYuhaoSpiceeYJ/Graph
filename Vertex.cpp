#include "Vertex.h"
using namespace std;

Vertex::Vertex(int id,string nom)
{
	this->id=id;
	this->nom=nom;
	this->visited = false;
}

Vertex::Vertex(int id)
{
	this->id=id;
	this->nom=char(id+48);
	this->visited = false;
}

Vertex::Vertex(string nom)
{
	this->nom=nom;
	this->id=0;
	this->visited = false;
}
    

Vertex::~Vertex()
{
	
}

Vertex::Vertex()
{
	
}
