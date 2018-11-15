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
        int id;//�û���ʼ��ʱ���������������λ�ã��������ӻ�ɾ��Ԫ�ػ���֮�ı� 
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
