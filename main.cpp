#include <iostream>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
using namespace std;

int main()
{
    
    
    Graph* G = new Graph();//cout<<"1";
    string filename = "test2.txt";
    G->readFile(filename);
	//cout<<G->listVertex[0].nom<<G->listVertex[2].nom<<endl;
    G->show_id();
    G->DFSTraverse(2);
    G->BFSTraverse(2);
    G->shortestPath_BF(2);
    G->shortestPath_DJ(2);
	G->shortestPath_BF(4);
    G->shortestPath_DJ(4);
    //cout<<G->findEdge(0,1);
    G->MST_KR_id();
    G->MST_PR_id();
    G->TopSort();
    G->sortEdge();
    /*G->isEmpty();
    G->clear();*/
    
}
