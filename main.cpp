#include <iostream>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
using namespace std;

int main()
{
    /*Graph* G = new Graph();//cout<<"1";
    Vertex v0= Vertex(0,"v0");//cout<<"1";
    Vertex v1= Vertex(1,"v1");
    Vertex v2= Vertex(2,"v2");
    Vertex v3= Vertex(3,"v3");
    Vertex v4= Vertex(4,"v4");
    //G->DFS(v0);
    G->InsertVertex(&v0);//cout<<"1";
    G->InsertVertex(&v1);
    G->InsertVertex(&v2);
    G->InsertVertex(&v3);
    G->InsertVertex(&v4);
    Edge e1= Edge(v0,v1,2);//cout<<"1";
    Edge e2= Edge(v1,v2,3);
    Edge e3= Edge(v2,v3,6);
    Edge e4= Edge(v3,v4,4);
    Edge e5= Edge(v0,v4,1);
    Edge e6= Edge(v0,v2,6);
    //e4 = Edge(v2,v4,7);
    G->InsertEdge(&e1);//cout<<"1";
    G->InsertEdge(&e2);
    G->InsertEdge(&e3);
    G->InsertEdge(&e4);
    G->InsertEdge(&e5);
    G->InsertEdge(&e6);
    G->file2graph();
    //G->graph_n_matrix();
    //G->graph_n_list();
    //G->DeleteEdge(&e4);
    //G->DeleteVertex("v4");
    //Vertex v6= Vertex(4,"v6");
	//G->InsertVertex(&v6);
    G->show();//cout<<"1";
    G->DFSTraverse("v2");
    G->BFSTraverse("v2");
    G->shortestPath_BF("v2");
    G->shortestPath_DJ("v2");
	G->shortestPath_BF("v4");
    G->shortestPath_DJ("v4");
    G->MST_KR();
    G->MST_PR();
    cout << "end" << endl;//cout<<"1";
    return 0;*/
    
    /*Graph* G = new Graph();
    G->show_nom();//cout<<"1";
    Vertex v0= Vertex(0,"A");
    Vertex v1= Vertex(1,"B");
    Vertex v2= Vertex(2,"C");
    Vertex v3= Vertex(3,"D");
    Vertex v4= Vertex(4,"E");
    Vertex v5= Vertex(5,"F");
    Vertex v6= Vertex(6,"G");
    Vertex v7= Vertex(7,"H");
    Vertex v8= Vertex(8,"I");
    
    G->InsertVertex(&v0);
    G->InsertVertex(&v1);
    G->InsertVertex(&v2);
    G->InsertVertex(&v3);
    G->InsertVertex(&v4);
    G->InsertVertex(&v5);
    G->InsertVertex(&v6);
    G->InsertVertex(&v7);
    G->InsertVertex(&v8);
    
    Edge e1= Edge(v0,v1,5);
    Edge e2= Edge(v0,v3,2);
    Edge e3= Edge(v1,v2,4);
    Edge e4= Edge(v2,v5,3);
    Edge e5= Edge(v5,v8,4);
    Edge e6= Edge(v7,v8,2);
    Edge e7= Edge(v6,v3,6);
    Edge e8= Edge(v6,v7,4);
    Edge e9= Edge(v4,v1,5);
    Edge e10= Edge(v4,v3,7);
    Edge e11= Edge(v4,v5,1);
    Edge e12= Edge(v4,v7,3);
    Edge e13= Edge(v1,v3,3);
    Edge e14= Edge(v3,v7,8);
    Edge e15= Edge(v7,v5,4);
    Edge e16= Edge(v5,v1,6);
    
    G->InsertEdge(&e1);
    G->InsertEdge(&e2);
    G->InsertEdge(&e3);
    G->InsertEdge(&e4);
    G->InsertEdge(&e5);
    G->InsertEdge(&e6);
    G->InsertEdge(&e7);
    G->InsertEdge(&e8);
    G->InsertEdge(&e9);
    G->InsertEdge(&e10);
    G->InsertEdge(&e11);
    G->InsertEdge(&e12);
    G->InsertEdge(&e13);
    G->InsertEdge(&e14);
    G->InsertEdge(&e15);
    G->InsertEdge(&e16);

    G->file2graph();
    G->DFSTraverse("A");
    G->BFSTraverse("A");
    G->shortestPath_BF("B");
    G->shortestPath_DJ("B");
	G->shortestPath_BF("C");
    G->shortestPath_DJ("C");
    G->MST_KR_nom();
    G->MST_PR_nom();
    cout << "end" << endl;//cout<<"1";
    return 0;*/
    
    Graph* G = new Graph();//cout<<"1";
    string filename = "test1.txt";
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
    G->clear();
    G->isEmpty();
    G->readFile(filename);
	//cout<<G->listVertex[0].nom<<G->listVertex[2].nom<<endl;
    G->show_id();
    G->DFSTraverse(2);
    G->BFSTraverse(2);
    G->shortestPath_BF(2);
    G->shortestPath_DJ(2);
	G->shortestPath_BF(4);
    G->shortestPath_DJ(4);
    G->MST_KR_id();
    G->MST_PR_id();
    
    cout << "end" << endl;//cout<<"1";*/
}
