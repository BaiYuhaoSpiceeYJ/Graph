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
        int id;//用户初始化时决定放在数组里的位置，随着增加或删除元素会随之改变 
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
