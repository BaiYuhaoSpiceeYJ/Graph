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
		int nbEdge;//show the number of Edges in the Graph
		int nbVertex;//show the number of Vertex in the Vertex
		int nbTopSortVertex; //when we use the function DFS, store the order of Vertex visited
	    bool directed;    //0 = undirected, 1 = directed
	  	bool struct_type;   // 0 = liste, 1 = matrix
	  	int connectedComponent;// to store the number of connected components of the graph if we traverse the graph
	  	
		Vertex* listVertex;// it¡¯s the list of Vertex stored in the graph
        Edge* listEdge;//it¡¯s the list of Edge stored in the graph
        Vertex* TopSortVertex;//it records the topologic order of the graph
        Edge* sortedEdge;//it records the edges sorted
        
		int** matrixAdj;//it¡¯s the adjacent matrix of the Graph
        vector< vector<int> > listAdj;// it¡¯s the adjacent list of the Graph

        
        
    public:
    	/*12*/Graph();
    	/*12*/Graph(int a,int b);
        /*13*/~Graph();
        /*32*/void clear();//It will clear all the Vertex and the Edges in the Graph.
        /*33*/bool isEmpty();//We use this function to determine if the Graph is empty. 
		/*01*/void InsertVertex(Vertex *v);
		/*02*/void InsertEdge(Edge *e);
		/*23*/void DeleteVertex(int id);
        /*04*/void DeleteEdge(Edge *e);
        /*21*/void file2graph();//This function permit us to make the graph.
        /*17*/void graph_o_matrix();//This function is used to make directed matrix.
        /*18*/void graph_n_matrix();//This function is used to make undirected matrix.
        /*19*/void graph_o_list();//This function is used to make directed list.
        /*20*/void graph_n_list();//This function is used to make undirected list.
        /*22*/int readFile(string filename);//We use this function to read the file.
        
        
        /*07*/void visit_toWhite(Vertex *v);
        /*07*/void visit_toGray(Vertex *v);
        /*07*/void visit_toBlack(Vertex *v);
        /*36*/void visitEdge_0(Edge *e);
        /*36*/void visitEdge_1(Edge *e);
        /*37*/int findEdge(int i,int j);
        
		/*28*/int DFS(int id,int date);//this function return a pointor (a list) which contain the Vertex that need to be traversed.
		/*24*/void DFSTraverse(int id);
		/*09*/Vertex* BFS(Vertex* bfs);
		/*25*/void BFSTraverse(int id);
		/*26*/void shortestPath_BF(int id);//BelLnam-Ford 
		/*27*/void shortestPath_DJ(int id);//Dijkstra
		/*22*/bool union_find(Vertex v1,Vertex v2);
		/*35*/void sortEdge();
        /*14*/void MST_KR_id();//Kruskal
        /*16*/void MST_PR_id();//Prim
        /*34*/void TopSort();//to show the topologic order of the graph
        /*06*/void show_id();//We show the adjecent matrix or the adjecent list by using this function. 
    
};

#endif // GRAPH_H
