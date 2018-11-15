#ifndef GRAPH_H
#define GRAPH_H
#include "Edge.h"
#include "Vertex.h"
#include <iostream>
#include <limits.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Graph
{
	private:
		int nbEdge;
		int nbVertex;
		int nbTopSortVertex;
	    bool directed;    //0 = undirected, 1 = directed
	  	bool struct_type;   // 0 = liste, 1 = matrix
	  	int connectedComponent;
	  	
		Vertex* listVertex;
        Edge* listEdge;
        Vertex* TopSortVertex;
        Edge* sortedEdge;
        
		int** matrixAdj;
        vector<vector<int> > listAdj;
        
        
    public:
    	/*12*/Graph();
        /*13*/~Graph();
        /*32*/void clear();
        /*33*/bool isEmpty();
		/*01*/void InsertVertex(Vertex *v);
		/*02*/void InsertEdge(Edge *e);
		/*03*/void DeleteVertex(string v);
		/*23*/void DeleteVertex(int id);
        /*04*/void DeleteEdge(Edge *e);
        /*21*/void file2graph();
        /*17*/void graph_o_matrix();
        /*18*/void graph_n_matrix();
        /*19*/void graph_o_list();
        /*20*/void graph_n_list();
        /*22*/int readFile(string filename);
        
        
        /*07*/void visit_toWhite(Vertex *v);
        /*07*/void visit_toGray(Vertex *v);
        /*07*/void visit_toBlack(Vertex *v);
        /*36*/void visitEdge_0(Edge *e);
        /*36*/void visitEdge_1(Edge *e);
        /*37*/int findEdge(int i,int j);
		/*05*/int DFS(string v,int date);
		/*28*/int DFS(int id,int date);
		/*08*/void DFSTraverse(string v);
		/*24*/void DFSTraverse(int id);
		/*09*/Vertex* BFS(Vertex* bfs);
		/*10*/void BFSTraverse(string v);
		/*25*/void BFSTraverse(int id);
		/*11*/void shortestPath_BF(string v);//BelLnam-Ford 
		/*26*/void shortestPath_BF(int id);//BelLnam-Ford 
		/*15*/void shortestPath_DJ(string v);//Dijkstra
		/*27*/void shortestPath_DJ(int id);//Dijkstra
		/*22*/bool union_find(Vertex v1,Vertex v2);
		/*35*/void sortEdge();
        /*14*/void MST_KR_id();//Kruskal
        /*29*/void MST_KR_nom();//Kruskal
        /*16*/void MST_PR_id();//Prim
        /*30*/void MST_PR_nom();//Prim
        /*34*/void TopSort();
        /*06*/void show_id();
        /*31*/void show_nom();
    
};

#endif // GRAPH_H
