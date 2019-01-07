#include "Graph.h"
using namespace std;

/*12*/
Graph::Graph()
{
    
    nbEdge = 0;
	nbVertex = 0;
	directed=0;    //0 = undirected, 1 = directed
	struct_type=1; // 0 = liste, 1 = matrix
	connectedComponent=0;
	nbTopSortVertex=0;

	listVertex = new Vertex [20];
	listEdge = new Edge [50];
	TopSortVertex = new Vertex[20];
	sortedEdge = new Edge [50];
}

Graph::Graph(int a,int b)
{
    
    nbEdge = 0;
	nbVertex = 0;
	directed=0;    //0 = undirected, 1 = directed
	struct_type=1; // 0 = liste, 1 = matrix
	connectedComponent=0;
	nbTopSortVertex=0;

	listVertex = new Vertex [a];
	listEdge = new Edge [b];
	TopSortVertex = new Vertex[a];
	sortedEdge = new Edge [b];
}

/*13*/
Graph::~Graph()
{
    
}

/*32*/
void Graph::clear()//It will clear all the Vertex and the Edges in the Graph.
{
	nbEdge = 0;
	nbVertex = 0;
	listAdj.clear();
	cout<<"Clear the graph"<<endl;
}

/*33*/
bool Graph::isEmpty()//We use this function to determine if the Graph is empty. 
{
	if(nbEdge==0&&nbVertex==0) cout<<"The Graph is empty"<<endl;
	else cout<<"The Graph is not empty"<<endl;
	return nbEdge==0&&nbVertex==0;
}

/*34*/
void Graph::TopSort()//to show the topologic order of the graph
{
	cout<<"TopSort : "<<endl;
	for (int i=nbTopSortVertex-1;i>=0;i--)
	{
		cout<<TopSortVertex[i].id<<" ";
	}
	cout<<endl;
}

/*2*/
void Graph::InsertEdge(Edge *e)
{
	listEdge[nbEdge]=*e;
	listEdge[nbEdge].id = nbEdge;
	this->nbEdge++;
	if(e->weight<=0)
	{
		cout<<"error,weight can not <= 0"<<endl;
	}
	
}

/*1*/
void Graph::InsertVertex(Vertex *v)
{
	listVertex[nbVertex]=*v;
    this->nbVertex++;
}

/*3*/
void Graph::DeleteVertex(int id)
{
	int i;
    for (i = 0; i<nbVertex; i++) //we find the location of the Vertex that we want to delete by using its id
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	
    if (i == nbVertex)
        cout<<"the vertex n'existe pas"<<endl;
	else
    {
		for (int j = 0; j < nbVertex; j++)          //we traverse the graph   
			if (matrixAdj[i][j] != 0)
			{ 
				nbEdge--;
				matrixAdj[i][j] = 0;	
        		matrixAdj[j][i] = 0;	
			} 
	      
    	nbVertex--; 
    	if (i < nbVertex)   //we use the last Vertex to replace the location of the Vertex deleted and we modify the matrix
		{
        	listVertex[i] = listVertex[nbVertex];
	    	for (int j = 0; j <= nbVertex; j++) 
				matrixAdj[i][j] = matrixAdj[nbVertex][j];
	   		for (int j = 0; j <= nbVertex; j++) 
            	matrixAdj[j][i] = matrixAdj[j][nbVertex];
   		} 
	}
}

/*4*/
void Graph::DeleteEdge(Edge *e)
{
	int i = e->src.id;
	int j = e->dst.id;
	
    	  
	matrixAdj[i][j] = 0;	//we set the weight of the edge that we delete to 0
    matrixAdj[j][i] = 0;
    this->nbEdge--; 
}

/*7*/
void Graph::visit_toWhite(Vertex *v)
{
	v->visited = 0;
	
}

/*7*/
void Graph::visit_toGray(Vertex *v)
{
	v->visited = 1;
	
}

/*7*/
void Graph::visit_toBlack(Vertex *v)
{
	v->visited = 2;
	
}

/*36*/
void Graph::visitEdge_0(Edge *e)
{
	e->visited = 0;
}

/*36*/
void Graph::visitEdge_1(Edge *e)
{
	e->visited = 1;
}

/*37*/
int Graph::findEdge(int i,int j)//by searching the id of src and dst
{
	int k;
	for(k=0;k<nbEdge;k++)
	{
		if(listEdge[k].src.id==i && listEdge[k].dst.id==j) 
		{
			return k;
			break;
		}
	}
	if(k==nbEdge)
	{
		cout<<"Error, can't find this edge!"<<endl;
		return -1;
	}
}

/*28*/
int Graph::DFS(int id,int date)//this function returns the date to record the order of traverse
{
	
	int i;
    for (i = 0; i<nbVertex; i++) //we find the location of the Vertex we are now in
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	
	cout<<"entrer v"<<listVertex[i].id<<" date="<<date<<endl;
	visit_toGray(&listVertex[i]);//we set 1 to Vertex.visited to show that we enter the Vertex but haven't quit

	for(int j=0;j<nbVertex;j++)
	{

		if(matrixAdj[i][j]!=0 && listVertex[j].visited==false)//we find the adjacent Vertex of this Vertex 
		{
			date++;//when we enter a new Vertex,date++
			date = DFS(listVertex[j].id,date);//we use recurrence to visit all the Vertex in the same component
		
		}

	}
	
	visit_toBlack(&listVertex[i]);
	date++;//when we quit this Vertex,date++
	
	cout<<"sortir v"<<listVertex[i].id<<" date="<<date<<endl;
	TopSortVertex[nbTopSortVertex] = listVertex[i];
	nbTopSortVertex++;
	
	return date;
	
	 
}

/*24*/
void Graph::DFSTraverse(int id)
{
	int date=1;
	for(int j=0;j<nbVertex;j++)//initialize, we set all Vertex unvisited
		visit_toWhite(&listVertex[j]);
	cout<<"DFS = "<<endl;
	cout<<"Le point de depart est v"<<id<<endl;
	
	int connectedComponent=1;
	cout<<"Connected Component "<<connectedComponent<<endl;
	
	int i;
    for (i = 0; i<nbVertex; i++) //we find the location of the start Vertex 
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	
	date = DFS(listVertex[i].id,date);//we research from the start point until find all the Vertex in the same component
	
	for(int j=0;j<nbVertex;j++)//if the list bfs is empty, we have researched all the Vertex in this component
	{                          //, but maybe we haven't traverse all the points in this Graph
		if (listVertex[j].visited==false) //We use a loop make sure that we will traverse all the Vertex
		{
			connectedComponent++;//we make sure that we will traverse all the Vertex in the Graph and we can also 
			cout<<"connectedComponent "<<connectedComponent<<endl;//calculate the number of connected Components in this graph
			date++;
			date= DFS(listVertex[j].id,date);
		}
	}
	cout<<endl;
	this->connectedComponent = connectedComponent;
	
}

/*9*/
Vertex* Graph::BFS(Vertex* bfs)//this function return a pointor (a list) which contain the Vertex that need to be traversed.
{
	cout<<"entrer v"<<bfs[0].id<<endl;
	//cout<<"entrer "<<bfs[0].nom<<endl;
	
	int i;
	for (i = 0; i<nbVertex; i++) //we find the location of the Vertex that we are now in
    {
		if	(listVertex[i].nom == bfs[0].nom)
        {
			break;
		}	
	}

	int k;
	for (k = 0; k<nbVertex; k++) //we calculate the number of element in the list bfs
    {
    	
		if	(bfs[k].nom == "null")
        {
			break;
		}	
	}
	int date=k;

	
	for(int j=0;j<nbVertex;j++)//we put the adjacent Vertex in the list bfs if this Vertex hasn't benn visited
	{
		if(matrixAdj[i][j]!=0 && listVertex[j].visited==false)
		{
			
			date++;
			bfs[date-1] = listVertex[j];
			visit_toGray(&listVertex[j]);
		}
	}
	
	visit_toBlack(&listVertex[i]);//we quit this Vertex that means this Vertex has been totally visited
	for (int i=0;i<nbVertex-1;i++)//we remove this Vertex from the list bfs
	{
		bfs[i] = bfs[i+1];
		
	}
	
	return bfs;
	 
}

/*25*/
void Graph::BFSTraverse(int id)
{
	cout<<"BFS = "<<endl;
	cout<<"Le point de depart est v"<<id<<endl;
	Vertex* bfs;
	bfs = new Vertex[nbVertex];//first of all, we create a list bfs to contain the Vertex that we have reached
	
	for(int j=0;j<nbVertex;j++)//initialize,we set all the vertex unvisited
	{
		visit_toWhite(&listVertex[j]);
		bfs[j] = Vertex("null");	
	}
	
	int i=0;
	for (i = 0; i<nbVertex; i++) //we find the location of the start Vertex 
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	
	bfs[0]=listVertex[i];//we put the start Vertex to the list
	visit_toGray(&listVertex[i]);
	int connectedComponent=1;
	cout<<"Connected Component "<<connectedComponent<<endl;
	
	bfs = BFS(bfs); //we research from the start point until find all the Vertex in the same component
	while (bfs[0].nom!="null")//if the list is not empty, we continue to research,and each time BFS() returns the new list bfs
	{
		bfs = BFS(bfs);
	}
	
	 
	for(int j=0;j<nbVertex;j++)//if the list bfs is empty, we have researched all the Vertex in this component
	{                          //, but maybe we haven't traverse all the points in this Graph
		if (listVertex[j].visited==false) //We use a loop make sure that we will traverse all the Vertex
		{
			connectedComponent++;//we make sure that we will traverse all the Vertex in the Graph and we can also 
			cout<<"connectedComponent "<<connectedComponent<<endl;//calculate the number of connected Components in this graph
			bfs[0]=listVertex[j];
			bfs = BFS(bfs);
		}
	}
	cout<<endl;
	this->connectedComponent = connectedComponent;
}

/*26*/
void Graph::shortestPath_BF(int id)//BelLnam-Ford 
{
	int i=0;
	for (i = 0; i<nbVertex; i++) //we find the location of the start Vertex
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	int index=i;
	
	int belford[2][nbVertex]; //we create a matrix called belford to record the shortest distance to other Vertex
	for (i=0;i<nbVertex;i++)
	{
		belford[0][i]=INT_MAX;
		belford[1][i]=-1;
	} 
	
	for (i=0;i<nbVertex;i++)//we visit the start Vertex and we record the distance of its adjacent Vertex
	{
		if (matrixAdj[index][i]!=0)
		{
			belford[0][i] = matrixAdj[index][i];//the first line of the Matrix is the distance
			belford[1][i] = index;//the second line of the Matrix record the source Vertex of this Vertex
		} 
	}
	belford[0][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//we use a loop of n-1 time, and we calculate if the path is shorter each time
	{
		int belford_old[2][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//we copy the matrix belford in the last loop to find the difference
		{
			belford_old[0][k] = belford[0][k];
			belford_old[1][k] = belford[1][k];
		}
		for (int j=0;j<nbVertex;j++)//we use a loop to calculate the new distance
		{
			for (int m=0;m<nbVertex;m++)
			{
				if (matrixAdj[m][j]!=0 && belford_old[0][m]!=INT_MAX)
				{
					if (belford[0][j]>belford_old[0][m]+matrixAdj[m][j])
					{
						
							belford[0][j] = belford_old[0][m]+matrixAdj[m][j];// if the new distance is shorter, we replace the shortest distance
							belford[1][j] = m;		
					}
				}
			}
		}
	}
	
	cout<<"Shortest Path (BelLnam-Ford) :"<<endl; //the part of print are as follow
	cout<<"Le point de depart est v"<<id<<endl;
	cout<<"dist ";
	for (i=0;i<nbVertex;i++)
	{
		cout<<belford[0][i]<<" ";
	}
	cout<<endl;
	cout<<"path ";
	for (i=0;i<nbVertex;i++)
	{
		cout<<belford[1][i]<<" ";
	}
	cout<<endl;
	cout<<endl;
}

/*27*/
void Graph::shortestPath_DJ(int id)//Dijkstra
{
	int i=0;
	for (i = 0; i<nbVertex; i++) //we find the location of the start Vertex
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	int index=i;
	
	int djks[3][nbVertex]; //we create a matrix called djks to record the shortest distance to other Vertex
	for (i=0;i<nbVertex;i++)
	{
		djks[0][i]=0;//the first line is record if the Vertex is in the shortest path
		djks[1][i]=INT_MAX;//the second line of the Matrix is the distance
		djks[2][i]=-1;//the third line of the Matrix record the source Vertex of this Vertex
	} 
	
	for (i=0;i<nbVertex;i++)//we visit the start Vertex and we record the distance of its adjacent Vertex
	{
		if (matrixAdj[index][i]!=0)
		{
			djks[0][index]=1;
			djks[1][i] = matrixAdj[index][i];
			djks[2][i] = index;
		} 
	}
	djks[1][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//we use a loop of n-1 time, and we calculate if the path is shorter each time
	{
		int djks_old[3][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//we copy the matrix djks in the last loop to find the difference
		{
			djks_old[0][k] = djks[0][k];
			djks_old[1][k] = djks[1][k];
			djks_old[2][k] = djks[2][k];
		}
		
		index=0;
		int min=INT_MAX;
		for(int k=0;k<nbVertex;k++)//we find the shortest path in current loop and we record the location
		{
			if(djks_old[0][k]==0 && djks_old[1][k]<min)
			{
				min = djks_old[1][k];
				index = k;
			}
		}
		djks[0][index]=1;
		
		for(int k=0;k<nbVertex;k++)//we find the next shortest path now but we shoule renovate all the distance
		{
			if(djks_old[1][index]+matrixAdj[index][k] < djks_old[1][k] && matrixAdj[index][k]!=0)
			{
				djks[1][k] = djks[1][index]+matrixAdj[index][k];//if the new distance is shorter, we replace the shortest distance
				djks[2][k]=index; 
			}
		}
	}
	
	cout<<"Shortest Path (Dijkstra) :"<<endl; //the part of print are as follow
	cout<<"Le point de depart est v"<<id<<endl;
	cout<<"dist ";
	for (i=0;i<nbVertex;i++)
	{
		cout<<djks[1][i]<<" ";
	}
	cout<<endl;
	cout<<"path ";
	for (i=0;i<nbVertex;i++)
	{
		cout<<djks[2][i]<<" ";
	}
	cout<<endl;
	cout<<endl;
	
}

/*22*/
bool Graph::union_find(Vertex v1,Vertex v2)//To determine if we can reach v2 as we start from v1 by going through 
{							               //the edges which have been added into the minimum spanning tree. 
	
	int index = v1.id;
	int i;
	int belford[2][nbVertex]; //we use the algorithm of BelLnam-Ford but there is a difference
	for (i=0;i<nbVertex;i++)//we create a matrix called belford to record the shortest distance to other Vertex
	{
		belford[0][i]=INT_MAX;
		belford[1][i]=-1;
	} 
	
	for (i=0;i<nbVertex;i++)//we visit the start Vertex and we record the distance of its adjacent Vertex
	{
		if (matrixAdj[index][i]!=0 )
		{
			if(listEdge[findEdge(v1.id,i)].visited == 1 )//||listEdge[findEdge(i,v1.id)].visited == 1
			{
				
				belford[0][i] = matrixAdj[index][i];
				belford[1][i] = index;
			}
		} 
	}
	
	belford[0][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//we use a loop of n-1 time, and we calculate if the path is shorter each time
	{
		int belford_old[2][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//we copy the matrix belford in the last loop to find the difference
		{
			belford_old[0][k] = belford[0][k];
			belford_old[1][k] = belford[1][k];
		}
		for (int j=0;j<nbVertex;j++)
		{
			for (int m=0;m<nbVertex;m++)
			{
				if (matrixAdj[m][j]!=0 && belford_old[0][m]!=INT_MAX)
				{
					if( listEdge[findEdge(m,j)].visited == 1 ||listEdge[findEdge(j,m)].visited == 1)//this is the difference!!!! we can only go through
					{																		//the edges which have been added into the minimum spanning tree. 
						if (belford[0][j]>belford_old[0][m]+matrixAdj[m][j])
						{
						
								belford[0][j] = belford_old[0][m]+matrixAdj[m][j];// if the new distance is shorter, we replace the shortest distance
								belford[1][j] = m;		
						}
					}
				}
			}
		}
	}

	
	if(belford[0][v2.id]==INT_MAX) return 0; //if the distance between v1 and v2 is INT_MAX, it means we can't reach v2 if we start from v1
	else return 1;
	
	
}

/*35*/
void Graph::sortEdge()//We sort the edge accrording to their weight
{
	Edge* copyEdge ;
	copyEdge = new Edge [nbEdge]; 
	for (int i=0;i<nbEdge;i++)
	{
			copyEdge[i] = listEdge[i];
	}
	
	
	for (int i=0;i<nbEdge;i++)//this is the algorithm of sorting
	{
		int current_shortest_edge = INT_MAX;
		int index=-1;
		for (int j=0;j<nbEdge;j++)
		{
			if (copyEdge[j].weight < current_shortest_edge && copyEdge[j].weight!=0)
			{
				current_shortest_edge = copyEdge[j].weight;
				index = j;
			}
		}
		sortedEdge[i] = copyEdge[index];
		copyEdge[index].weight = 0;

	}

}

/*14*/
void Graph::MST_KR_id()//Kruskal
{
	cout<<"MST (Kruskal) : "<<endl;
	if(connectedComponent==1)//we can do this only if the number connected component of this graph is 1
	{
		
		for(int j=0;j<nbVertex;j++)//we set all the vertex unvisited
		{
			visit_toWhite(&listVertex[j]);
		}
		
		for(int j=0;j<nbEdge;j++)//we set all the edges unvisited
		{
			visitEdge_0(&listEdge[j]);
		}
		sortEdge();
		
		int sum = 0;
		int count=0;
		for (int i=0;i<nbEdge;i++)
		{	
			if(! union_find(listVertex[sortedEdge[i].src.id],listVertex[sortedEdge[i].dst.id]) || ! union_find(listVertex[sortedEdge[i].dst.id],listVertex[sortedEdge[i].src.id]))
			{//if one of the Vertex (src or dst) is not in the MST, we can add this edge to the MST
				count++;//so that we make sure everytime we add at least a new Vertex into the MST.
				sum += sortedEdge[i].weight;
				visitEdge_1(&listEdge[findEdge(sortedEdge[i].src.id,sortedEdge[i].dst.id)]);//we set this edge visited
				visitEdge_1(&listEdge[findEdge(sortedEdge[i].dst.id,sortedEdge[i].src.id)]);//we set this edge visited
				visit_toBlack(&listVertex[sortedEdge[i].src.id]);//we set the dst and src of the edge visited
				visit_toBlack(&listVertex[sortedEdge[i].dst.id]);//we set the dst and src of the edge visited
				cout<<"step"<<count<<" Add (v"<<sortedEdge[i].src.id<<",v"<<sortedEdge[i].dst.id<<") weight = "<<sortedEdge[i].weight<<endl;
			}
		}
		
		cout<<"Sum of weight is = "<<sum<<endl;
		cout<<endl;
	}
	
	else if(connectedComponent==0)//if the number connected component of this graph is 0,it means we haven't traversed this graph to calculate it
	{
		cout<<"Error. Must traverse (BFS,DFS) to calcul connected component before this step."<<endl;
		cout<<endl;
	}
	
	else//if the number connected component of this graph is not 0 or 1, we can do this because the graph is not connected
	{
		cout<<"Error. The graph is not connected."<<endl;
		cout<<endl;
	}
}

/*16*/
void Graph::MST_PR_id()//Prim
{
	cout<<"MST (Prim) : "<<endl;
	if (connectedComponent==1)//we can do this only if the number connected component of this graph is 1
	{
		
		for(int j=0;j<nbVertex;j++)//we set all the vertex unvisited
		{
			visit_toWhite(&listVertex[j]);
		}
	

		int current_shortest_edge;
		int index1,index2;
		int sum = 0;
	
		visit_toBlack(&listVertex[0]);
	
		for(int count=0;count<nbVertex-1;count++)//we make a loop for n-1 tines and each time
		{										 //we find the shortest edge related to the Vertex in the MST
			index1 = -1;
			index2 = -1; 
			current_shortest_edge = INT_MAX;
		
			for (int i=0;i<nbVertex;i++)//find the current shortest edge
			{						//and at least one of the Vertex(src or dst) of this edge is not visited
				if(listVertex[i].visited!=0)//so that we make sure everytime we add at least a new Vertex into the MST.
				{ 
					for(int j=0;j<nbVertex;j++)
					{
						if(listVertex[j].visited==0)
						{
							if(matrixAdj[i][j]<current_shortest_edge && matrixAdj[i][j]!=0)
							{
								current_shortest_edge = matrixAdj[i][j];//we find the shortest edge related to the Vertex in the MST
								index1 = i;
								index2 = j;
							}
						}
					}	
				}
			}
			visit_toBlack(&listVertex[index1]);//we set the dst and src of the edge visited
			visit_toBlack(&listVertex[index2]);//we set the dst and src of the edge visited
			sum += current_shortest_edge;
			cout<<"step"<<count+1<<" Add (v"<<listVertex[index1].id<<",v"<<listVertex[index2].id<<") weight = "<<current_shortest_edge<<endl;
		}
		cout<<"Sum of weight is = "<<sum<<endl;
		cout<<endl;
	}
	
	else if(connectedComponent==0)//if the number connected component of this graph is 0,it means we haven't traversed this graph to calculate it
	{
		cout<<"Error. Must traverse (BFS,DFS) to calcul connected component before this step."<<endl;
		cout<<endl;
	}
	
	else//if the number connected component of this graph is not 0 or 1, we can do this because the graph is not connected
	{
		cout<<"Error. The graph is not connected."<<endl;
		cout<<endl;
	}
	
}

/*6*/
void Graph::show_id()//We show the adjecent matrix or the adjecent list by using this function. 
{
	if(struct_type)
	{
		cout<<"Adjacency Matrix : "<<endl;
    	for (int i=0;i<nbVertex;i++)
    	{
    		cout<<"v"<<listVertex[i].id<<" ";
    		//cout<<listVertex[i].nom<<" ";
    		for (int j=0;j<nbVertex;j++)
    		{
    			cout<<matrixAdj[i][j]<<"  ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	else
	{
		cout<<"Adjacency List : "<<endl;
		for (int i=0;i<nbVertex;i++)
   		{
    		cout<<"v"<<listVertex[i].id<<": ";
    		int current_size = listAdj[i].size();
    		for (int j=0;j<current_size;j++)
    		{
    			cout<<"<"<<listAdj[i][j]<<","<<matrixAdj[i][listAdj[i][j]]<<"> ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
    cout<<"the number of vertex = "<<nbVertex<<endl; 
    cout<<"the number of edges = "<<nbEdge<<endl; 
    cout<<endl;
}


/*21*/
void Graph::file2graph()//This function permit us to make the graph.
{
	
	if (directed)
	{
		graph_o_matrix();
		graph_o_list();
	}
	else
	{
		graph_n_matrix();
		graph_n_list();
	}
		
 }
 
/*17*/ 
void Graph::graph_o_matrix()//This function is used to make directed matrix.
{
	matrixAdj = new int *[nbVertex];
	for (int i = 0; i<nbVertex; i++)//initialize
	{
		matrixAdj[i] = new int[nbVertex];
		for (int j = 0; j<nbVertex ;  j++)
		{
			matrixAdj[i][j]=0;
		}	
	}
	
	for (int i = 0; i < nbEdge; i++)
	{
		int m = listEdge[i].src.id;
		int n = listEdge[i].dst.id;
   		matrixAdj[m][n] = listEdge[i].weight;	//it's undirected graph
  	} 
}

/*18*/
void Graph::graph_n_matrix()//This function is used to make undirected matrix.
{
	matrixAdj = new int *[nbVertex];
	for (int i = 0; i<nbVertex; i++)//initialize
	{
		matrixAdj[i] = new int[nbVertex];
		for (int j = 0; j<nbVertex ;  j++)
		{
			matrixAdj[i][j]=0;
		}	
	}
	
	for (int i = 0; i < nbEdge; i++)
	{
		int m = listEdge[i].src.id;
		int n = listEdge[i].dst.id;
   		matrixAdj[m][n] = listEdge[i].weight;	//it's directed graph
   		matrixAdj[n][m] = listEdge[i].weight;
  	} 
}

/*19*/
void Graph::graph_o_list()//This function is used to make directed list.
{
	vector<int> vect = vector<int>();
	for (int i=0;i<nbVertex;i++)
	{
		listAdj.push_back(vect);
	}
	
	for (int i = 0; i < nbEdge; i++)
	{
		int m = listEdge[i].src.id;
		int n = listEdge[i].dst.id;
   		listAdj[m].push_back(n);		
  	} 
	
}

/*20*/
void Graph::graph_n_list()//This function is used to make undirected list.
{
	vector<int> vect = vector<int>();
	for (int i=0;i<nbVertex;i++)
	{
		listAdj.push_back(vect);
	}
	
	for (int i = 0; i < nbEdge; i++)
	{
		int m = listEdge[i].src.id;
		int n = listEdge[i].dst.id;
   		listAdj[m].push_back(n);		
		listAdj[n].push_back(m);
  	} 
}


/*22*/
int Graph::readFile(string filename)
{
    cout<<filename<<endl;
    const char* filename_= filename.data();

    ifstream infile(filename_);//Define the input file stream class object infile

    if(!infile)// Determine if the file exists
	{
    	cout<<"open error."<<endl;
    	exit(1);
    }

    int nb;
	infile>>nb;
    if(nb<0)//If the number of vertices is negative.
    {
        cout<<"The number of vertices is negative."<<endl;
        return -1;
    }
    else
    {
        cout<<"First line: nbVertex="<<nb<<endl;
        for (int i=0;i<nb;i++)
        {
            Vertex v = Vertex(i);//or Vertex *v = new Vertex(i);
            InsertVertex(&v);
        }
    }
    string on,ml,temp;getline(infile,temp);getline(infile,on);

    if(on=="o")
		directed=1;
    else if(on=="n")
		directed=0;
    else
    {
        cout<<"The type of the graph is unknown. "<<endl;
        return -1;
    }

    cout<<"Second line: "<<on<<endl;


    getline(infile,ml);
    if(ml=="l") struct_type=0;//Determine the type of graph
    else if(ml=="m")
		struct_type=1;
    else
    {
        cout<<"The type of the graph is unknown. "<<endl;
        return -1;
    }

    cout<<"Third line: "<<ml<<endl;

    if(infile.eof()!=0)//Determine whether the file has been read
    {
        cout<<"We do not have numbers on the following lines"<<endl;
        exit(1);
    }

    if(struct_type==1)//if the graph is given by the type of matrix
    {
        char ch;
        double *tab=new double[100];//We create an array to hold what we read from the file each time.
        int i=0,k1=0,k2=0;//k1 represents the row k2 represents the column
        while (!infile.eof())//Judge the file is finished
        {
            infile>>tab[i];
            cout<<tab[i]<<"  ";
            ch=infile.get();
            if(tab[i]<0)
            {
                cout<<endl<<tab[i];
                cout<<" The weight can not be negative"<<endl;
                return 0;
            }
            else
            {
                if(tab[i]>0)
                {
                    Edge e=Edge(listVertex[k1],listVertex[k2],tab[i]);
                    InsertEdge(&e);
                }
                k2++;
            }
            i++;

            if(ch=='\n')
            {
                cout<<endl;
                k1++;k2=0;//Once you encounter a carriage return, k1 will add one.
                if(i%nb!=0)
                {
                    cout<<"The line is not entirely correct"<<endl;
                    return 0;
                }
            }
        }
        cout<<endl;
        cout<<endl;
        file2graph();
        return 1;
    }
    else
    {
        char ch; int k1=0,k2,w,count=0;
        while (!infile.eof())
        {
            ch=infile.get();
            if(ch=='<')
            {
                count++;//Count is used to determine the number of each line to prevent redundant edges
                ch=infile.get();k2=ch- '0';//Different types of ch and k1
                ch=infile.get();//,
                ch=infile.get();
                if(ch=='-')
                {
                    cout<<" The weight can not be negative"<<endl;
                    return 0;
                }
                w=ch-'0';//cout<<w<<endl;
                ch=infile.get();//>
                Edge e=Edge(listVertex[k1],listVertex[k2],w);
                InsertEdge(&e);
            }
            if(ch=='\n')
            {
                k1++;
                if(count>nb)
                {
                    cout<<"The line is not entirely correct"<<endl;
                    return 0;
                }
                count=0;
            }
        }
        file2graph();
        return 1;
    }

}
