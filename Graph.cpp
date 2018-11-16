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

/*13*/
Graph::~Graph()
{
    
}

/*32*/
void Graph::clear()
{
	nbEdge = 0;
	nbVertex = 0;
	listAdj.clear();
	cout<<"Clear the graph"<<endl;
}

/*33*/
bool Graph::isEmpty()
{
	if(nbEdge==0&&nbVertex==0) cout<<"The Graph is empty"<<endl;
	else cout<<"The Graph is not empty"<<endl;
	return nbEdge==0&&nbVertex==0;
}

/*34*/
void Graph::TopSort()
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
void Graph::DeleteVertex(string v_nom)
{
	int i;
    for (i = 0; i<nbVertex; i++) //找到删除的是几号点 
    {
		if	(listVertex[i].nom == v_nom)
        {
			break;
		}	
	}
	
    if (i == nbVertex)
        cout<<"the vertex n'existe pas"<<endl;
	else
    {
		for (int j = 0; j < nbVertex; j++)             // 删除与顶点v相关联的边 
			if (matrixAdj[i][j] != 0)
			{ 
				nbEdge--;
				matrixAdj[i][j] = 0;	
        		matrixAdj[j][i] = 0;	
			} 
	      
    	nbVertex--; 
    	if (i < nbVertex)   //操作矩阵，把最后的顶点补掉删除的顶点的位置 
		{
        	listVertex[i] = listVertex[nbVertex];
	    	for (int j = 0; j <= nbVertex; j++) 
				matrixAdj[i][j] = matrixAdj[nbVertex][j];
	   		for (int j = 0; j <= nbVertex; j++) 
            	matrixAdj[j][i] = matrixAdj[j][nbVertex];
   		} 
	}
}

/*23*/
void Graph::DeleteVertex(int id)
{
	int i;
    for (i = 0; i<nbVertex; i++) //找到删除的是几号点 
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
		for (int j = 0; j < nbVertex; j++)             // 删除与顶点v相关联的边 
			if (matrixAdj[i][j] != 0)
			{ 
				nbEdge--;
				matrixAdj[i][j] = 0;	
        		matrixAdj[j][i] = 0;	
			} 
	      
    	nbVertex--; 
    	if (i < nbVertex)   //操作矩阵，把最后的顶点补掉删除的顶点的位置 
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
	
    	  
	matrixAdj[i][j] = 0;	
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
int Graph::findEdge(int i,int j)
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

/*5*/
int Graph::DFS(string v_nom,int date)
{
	
	int i;
    for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].nom == v_nom)
        {
			break;
		}	
	}
	
	cout<<"entrer "<<listVertex[i].nom<<" date="<<date<<endl;
	//cout<<"entrer "<<v_nom<<" date="<<date<<endl;
	visit_toGray(&listVertex[i]);

	for(int j=0;j<nbVertex;j++)//递归 
	{

		if(matrixAdj[i][j]!=0 && listVertex[j].visited==false)
		{
			date++;
			date = DFS(listVertex[j].nom,date);
		
		}

	}
	
	date++;
	
	cout<<"sortir "<<listVertex[i].nom<<" date="<<date<<endl;
	TopSortVertex[nbTopSortVertex] = listVertex[i];
	nbTopSortVertex++;
	//cout<<"sortir "<<v_nom<<" date="<<date<<endl;
	visit_toBlack(&listVertex[i]);
	return date;
	
	 
}

/*28*/
int Graph::DFS(int id,int date)
{
	
	int i;
    for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	
	cout<<"entrer v"<<listVertex[i].id<<" date="<<date<<endl;
	//cout<<"entrer "<<v_nom<<" date="<<date<<endl;
	visit_toGray(&listVertex[i]);

	for(int j=0;j<nbVertex;j++)//递归 
	{

		if(matrixAdj[i][j]!=0 && listVertex[j].visited==false)
		{
			date++;
			date = DFS(listVertex[j].id,date);
		
		}

	}
	
	date++;
	
	cout<<"sortir v"<<listVertex[i].id<<" date="<<date<<endl;
	TopSortVertex[nbTopSortVertex] = listVertex[i];
	nbTopSortVertex++;
	//cout<<"sortir "<<v_nom<<" date="<<date<<endl;
	visit_toBlack(&listVertex[i]);
	return date;
	
	 
}

/*8*/
void Graph::DFSTraverse(string v_nom)
{
	
	int date=1;
	for(int j=0;j<nbVertex;j++)
		visit_toWhite(&listVertex[j]);
	cout<<"DFS = "<<endl;
	cout<<"Le point de depart est "<<v_nom<<endl;
	
	int connectedComponent=1;
	cout<<"Connected Component "<<connectedComponent<<endl;
	
	date = DFS(v_nom,date);
	
	int i;
    for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].nom == v_nom)
        {
			break;
		}	
	}
	for(int j=0;j<nbVertex;j++)//保证所有点都被遍历一次 
	{
		if (listVertex[j].visited==false) 
		{
			connectedComponent++;
			cout<<"connectedComponent "<<connectedComponent<<endl;
			date++;
			date= DFS(listVertex[j].nom,date);
		}
	}
	cout<<endl;
	this->connectedComponent = connectedComponent;
	
}

/*24*/
void Graph::DFSTraverse(int id)
{
	int date=1;
	for(int j=0;j<nbVertex;j++)
		visit_toWhite(&listVertex[j]);
	cout<<"DFS = "<<endl;
	cout<<"Le point de depart est v"<<id<<endl;
	
	int connectedComponent=1;
	cout<<"Connected Component "<<connectedComponent<<endl;
	
	int i;
    for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	
	date = DFS(listVertex[i].id,date);
	
	for(int j=0;j<nbVertex;j++)//保证所有点都被遍历一次 
	{
		if (listVertex[j].visited==false) 
		{
			connectedComponent++;
			cout<<"connectedComponent "<<connectedComponent<<endl;
			date++;
			date= DFS(listVertex[j].id,date);
		}
	}
	cout<<endl;
	this->connectedComponent = connectedComponent;
	
}

/*9*/
Vertex* Graph::BFS(Vertex* bfs)
{
	cout<<"entrer v"<<bfs[0].id<<endl;
	//cout<<"entrer "<<bfs[0].nom<<endl;
	
	int i;
	for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].nom == bfs[0].nom)
        {
			break;
		}	
	}

	int k;
	for (k = 0; k<nbVertex; k++) //求当前队列中元素数量 
    {
    	
		if	(bfs[k].nom == "null")
        {
			break;
		}	
	}
	int date=k;
	visit_toBlack(&listVertex[i]);
	
	for(int j=0;j<nbVertex;j++)//将当前点的相邻点放入队列 
	{
		if(matrixAdj[i][j]!=0 && listVertex[j].visited==false)
		{
			
			date++;
			bfs[date-1] = listVertex[j];
			visit_toGray(&listVertex[j]);
		}
	}
	

	for (int i=0;i<nbVertex-1;i++)//从队列中移除当前点 
	{
		bfs[i] = bfs[i+1];
		
	}
	
	return bfs;
	 
}

/*10*/
void Graph::BFSTraverse(string v_nom)
{
	cout<<"BFS = "<<endl;
	cout<<"Le point de depart est "<<v_nom<<endl;
	Vertex* bfs;
	bfs = new Vertex[nbVertex];
	
	for(int j=0;j<nbVertex;j++)//初始化 
	{
		visit_toWhite(&listVertex[j]);
		bfs[j] = Vertex("null");	
	}
	
	int i=0;
	for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].nom == v_nom)
        {
			break;
		}	
	}
	
	bfs[0]=listVertex[i];//将起点放入队列 
	visit_toGray(&listVertex[i]);
	int connectedComponent=1;
	cout<<"Connected Component "<<connectedComponent<<endl;
	
	bfs = BFS(bfs); //从起始点开始搜索直到搜索完以起始点构成的连通图 
	while (bfs[0].nom!="null")//队列不为空，就继续搜索，BFS函数返回新的队列 
	{
		bfs = BFS(bfs);
	}
	
	 
	for(int j=0;j<nbVertex;j++)//队列为空，可能并未搜索完，保证所有点都被遍历一次 
	{
		if (listVertex[j].visited==false) 
		{
			connectedComponent++;
			cout<<"connectedComponent "<<connectedComponent<<endl;
			bfs[0]=listVertex[j];
			bfs = BFS(bfs);
		}
	}
	cout<<endl;
	this->connectedComponent = connectedComponent;
}

/*25*/
void Graph::BFSTraverse(int id)
{
	cout<<"BFS = "<<endl;
	cout<<"Le point de depart est v"<<id<<endl;
	Vertex* bfs;
	bfs = new Vertex[nbVertex];
	
	for(int j=0;j<nbVertex;j++)//初始化 
	{
		visit_toWhite(&listVertex[j]);
		bfs[j] = Vertex("null");	
	}
	
	int i=0;
	for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	
	bfs[0]=listVertex[i];//将起点放入队列 
	visit_toGray(&listVertex[i]);
	int connectedComponent=1;
	cout<<"Connected Component "<<connectedComponent<<endl;
	
	bfs = BFS(bfs); //从起始点开始搜索直到搜索完以起始点构成的连通图 
	while (bfs[0].nom!="null")//队列不为空，就继续搜索，BFS函数返回新的队列 
	{
		bfs = BFS(bfs);
	}
	
	 
	for(int j=0;j<nbVertex;j++)//队列为空，可能并未搜索完，保证所有点都被遍历一次 
	{
		if (listVertex[j].visited==false) 
		{
			connectedComponent++;
			cout<<"connectedComponent "<<connectedComponent<<endl;
			bfs[0]=listVertex[j];
			bfs = BFS(bfs);
		}
	}
	cout<<endl;
	this->connectedComponent = connectedComponent;
}

/*11*/
void Graph::shortestPath_BF(string v_nom)//BelLnam-Ford 
{
	int i=0;
	for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].nom == v_nom)
        {
			break;
		}	
	}
	int index=i;
	
	int belford[2][nbVertex]; //对数组初始化
	for (i=0;i<nbVertex;i++)
	{
		belford[0][i]=INT_MAX;
		belford[1][i]=-1;
	} 
	
	for (i=0;i<nbVertex;i++)//访问源点，把和它有联系的边都记录进来 
	{
		if (matrixAdj[index][i]!=0)
		{
			belford[0][i] = matrixAdj[index][i];
			belford[1][i] = index;
		} 
	}
	belford[0][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//循环n-1次，每次判断是否路线更短 
	{
		int belford_old[2][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//复制一次上一次的belford数组 
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
					if (belford[0][j]>belford_old[0][m]+matrixAdj[m][j])
					{
						
							belford[0][j] = belford_old[0][m]+matrixAdj[m][j];
							belford[1][j] = m;		
					}
				}
			}
		}
	}
	
	cout<<"Shortest Path (BelLnam-Ford) :"<<endl; 
	cout<<"Le point de depart est "<<v_nom<<endl;
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

/*26*/
void Graph::shortestPath_BF(int id)//BelLnam-Ford 
{
	int i=0;
	for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	int index=i;
	
	int belford[2][nbVertex]; //对数组初始化
	for (i=0;i<nbVertex;i++)
	{
		belford[0][i]=INT_MAX;
		belford[1][i]=-1;
	} 
	
	for (i=0;i<nbVertex;i++)//访问源点，把和它有联系的边都记录进来 
	{
		if (matrixAdj[index][i]!=0)
		{
			belford[0][i] = matrixAdj[index][i];
			belford[1][i] = index;
		} 
	}
	belford[0][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//循环n-1次，每次判断是否路线更短 
	{
		int belford_old[2][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//复制一次上一次的belford数组 
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
					if (belford[0][j]>belford_old[0][m]+matrixAdj[m][j])
					{
						
							belford[0][j] = belford_old[0][m]+matrixAdj[m][j];
							belford[1][j] = m;		
					}
				}
			}
		}
	}
	
	cout<<"Shortest Path (BelLnam-Ford) :"<<endl; 
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

/*15*/
void Graph::shortestPath_DJ(string v_nom)//Dijkstra
{
	int i=0;
	for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].nom == v_nom)
        {
			break;
		}	
	}
	int index=i;
	
	int djks[3][nbVertex]; //对数组初始化
	for (i=0;i<nbVertex;i++)
	{
		djks[0][i]=0;
		djks[1][i]=INT_MAX;
		djks[2][i]=-1;
	} 
	
	for (i=0;i<nbVertex;i++)//访问源点，把和它有联系的边都记录进来 
	{
		if (matrixAdj[index][i]!=0)
		{
			djks[0][index]=1;
			djks[1][i] = matrixAdj[index][i];
			djks[2][i] = index;
		} 
	}
	djks[1][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//循环n-1次，每次判断是否路线更短 
	{
		int djks_old[3][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//复制一次上一次的djks数组 
		{
			djks_old[0][k] = djks[0][k];
			djks_old[1][k] = djks[1][k];
			djks_old[2][k] = djks[2][k];
		}
		
		index=0;
		int min=INT_MAX;
		for(int k=0;k<nbVertex;k++)//找到当前循环对应的最小的dist，并且记录位置 
		{
			if(djks_old[0][k]==0 && djks_old[1][k]<min)
			{
				min = djks_old[1][k];
				index = k;
			}
		}
		djks[0][index]=1;
		
		for(int k=0;k<nbVertex;k++)//找到下一个最短的路径，首先要更新所有路径的最小值 
		{
			if(djks_old[1][index]+matrixAdj[index][k] < djks_old[1][k] && matrixAdj[index][k]!=0)
			{
				djks[1][k] = djks[1][index]+matrixAdj[index][k];
				djks[2][k]=index; 
			}
		}
	}
	
	cout<<"Shortest Path (Dijkstra) :"<<endl; 
	cout<<"Le point de depart est "<<v_nom<<endl;
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

/*27*/
void Graph::shortestPath_DJ(int id)//Dijkstra
{
	int i=0;
	for (i = 0; i<nbVertex; i++) //找到当前的是几号点 
    {
		if	(listVertex[i].id == id)
        {
			break;
		}	
	}
	int index=i;
	
	int djks[3][nbVertex]; //对数组初始化
	for (i=0;i<nbVertex;i++)
	{
		djks[0][i]=0;
		djks[1][i]=INT_MAX;
		djks[2][i]=-1;
	} 
	
	for (i=0;i<nbVertex;i++)//访问源点，把和它有联系的边都记录进来 
	{
		if (matrixAdj[index][i]!=0)
		{
			djks[0][index]=1;
			djks[1][i] = matrixAdj[index][i];
			djks[2][i] = index;
		} 
	}
	djks[1][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//循环n-1次，每次判断是否路线更短 
	{
		int djks_old[3][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//复制一次上一次的djks数组 
		{
			djks_old[0][k] = djks[0][k];
			djks_old[1][k] = djks[1][k];
			djks_old[2][k] = djks[2][k];
		}
		
		index=0;
		int min=INT_MAX;
		for(int k=0;k<nbVertex;k++)//找到当前循环对应的最小的dist，并且记录位置 
		{
			if(djks_old[0][k]==0 && djks_old[1][k]<min)
			{
				min = djks_old[1][k];
				index = k;
			}
		}
		djks[0][index]=1;
		
		for(int k=0;k<nbVertex;k++)//找到下一个最短的路径，首先要更新所有路径的最小值 
		{
			if(djks_old[1][index]+matrixAdj[index][k] < djks_old[1][k] && matrixAdj[index][k]!=0)
			{
				djks[1][k] = djks[1][index]+matrixAdj[index][k];
				djks[2][k]=index; 
			}
		}
	}
	
	cout<<"Shortest Path (Dijkstra) :"<<endl; 
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
bool Graph::union_find(Vertex v1,Vertex v2)//找到能否通过v1的已联通部分找到v2 
{
	
	int index = v1.id;
	int i;
	int belford[2][nbVertex]; //对数组初始化
	for (i=0;i<nbVertex;i++)
	{
		belford[0][i]=INT_MAX;
		belford[1][i]=-1;
	} 
	
	for (i=0;i<nbVertex;i++)//访问源点，把和它有联系的边都记录进来 
	{
		if (matrixAdj[index][i]!=0 )
		{//cout<<"jj"<<listEdge[10].visited;
			if(listEdge[findEdge(v1.id,i)].visited == 1 )//||listEdge[findEdge(i,v1.id)].visited == 1
			{
				
				belford[0][i] = matrixAdj[index][i];
				belford[1][i] = index;
			}
		} 
	}
	
	belford[0][index] = 0;
	
	for (int i=0;i<nbVertex-1;i++)//循环n-1次，每次判断是否路线更短 
	{
		int belford_old[2][nbVertex] ;
		for (int k=0;k<nbVertex;k++)//复制一次上一次的belford数组 
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
					if( listEdge[findEdge(m,j)].visited == 1 ||listEdge[findEdge(j,m)].visited == 1)
					{
					//cout<<"A"<<listEdge[findEdge(m,j)].visited ;
						if (belford[0][j]>belford_old[0][m]+matrixAdj[m][j])
						{
						
								belford[0][j] = belford_old[0][m]+matrixAdj[m][j];
								belford[1][j] = m;		
						}
					}
				}
			}
		}
	}

	
	if(belford[0][v2.id]==INT_MAX) return 0;
	else return 1;
	
	/*bool result = 0;//cout<<"result="<<result<<endl;
	for (int i=0;i<nbVertex;i++)
	{
		if(result!=0)
		{
			break;
		}
		else
		{
			if (matrixAdj[v1.id][i] != 0 ) //&& listVertex[i].visited != 0
			{cout<<"A"<<matrixAdj[v1.id][i]<<endl;
				if( listEdge[findEdge(v1.id,i)].visited == 1)
				{
					if(listVertex[i].id == v2.id)
					{
						result = 1;
					}
					else
					{
						result = union_find(listVertex[i],v2);
						
					}
				}
			}
		}
	}
	return result;*/
}

/*35*/
void Graph::sortEdge()
{
	Edge* copyEdge ;
	copyEdge = new Edge [nbEdge]; 
	for (int i=0;i<nbEdge;i++)
	{
			copyEdge[i] = listEdge[i];
	}
	
	
	for (int i=0;i<nbEdge;i++)
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
	if(connectedComponent==1)
	{
		
		for(int j=0;j<nbVertex;j++)//初始化 
		{
			visit_toWhite(&listVertex[j]);
		}
		
		for(int j=0;j<nbEdge;j++)//初始化 
		{
			visitEdge_0(&listEdge[j]);
		}
		sortEdge();
		/*int copy_matrix[nbVertex][nbVertex]; //copy一个新的邻接矩阵 
		for (int i=0;i<nbVertex;i++)
		{
			for(int j=0;j<nbVertex;j++)
			{
				copy_matrix[i][j] = matrixAdj[i][j];
			}
		} 
		
	
		int current_shortest_edge;
		int index1,index2;
	
		int sum = 0;
		for(int count=0;count<nbVertex-1;count++)//循环n-1次，每次遍历一次邻接矩阵找到最短边 
		{
			index1 = -1;
			index2 = -1; 
			current_shortest_edge = INT_MAX;
			for (int m=0;m<nbVertex;m++)
			{
				for (int n=0;n<nbVertex;n++)//当前最短边要保证至少连接一个新的顶点 ,判断点1是否已经可以到达点2 
				{
					if (!union_find(listVertex[m],listVertex[n]) && copy_matrix[m][n]<current_shortest_edge&&copy_matrix[m][n]!=0)
					{
						current_shortest_edge=copy_matrix[m][n];
						index1 = m;
						index2 = n;
					}
				}
			}*/
		int sum = 0;
		int count=0;
		for (int i=0;i<nbEdge;i++)
		{	
			if(! union_find(listVertex[sortedEdge[i].src.id],listVertex[sortedEdge[i].dst.id]) || ! union_find(listVertex[sortedEdge[i].dst.id],listVertex[sortedEdge[i].src.id]))
			{
				count++;
				sum += sortedEdge[i].weight;
				visitEdge_1(&listEdge[findEdge(sortedEdge[i].src.id,sortedEdge[i].dst.id)]);
				visitEdge_1(&listEdge[findEdge(sortedEdge[i].dst.id,sortedEdge[i].src.id)]);
				visit_toBlack(&listVertex[sortedEdge[i].src.id]);
				visit_toBlack(&listVertex[sortedEdge[i].dst.id]);
				cout<<"step"<<count<<" Add (v"<<sortedEdge[i].src.id<<",v"<<sortedEdge[i].dst.id<<") weight = "<<sortedEdge[i].weight<<endl;
			}
		}
			//visit_toBlack(&listVertex[index1]);
			//visit_toBlack(&listVertex[index2]);
			//copy_matrix[index1][index2] = 0;//访问顶点 
			//copy_matrix[index2][index1] = 0;//有向图去掉这一行 
			//sum += current_shortest_edge;
			//cout<<"step"<<count+1<<" Add (v"<<listVertex[index1].id<<",v"<<listVertex[index2].id<<") weight = "<<current_shortest_edge<<endl;
			//cout<<"step"<<count+1<<" Add ("<<listVertex[index1].nom<<","<<listVertex[index2].nom<<") weight = "<<current_shortest_edge<<endl;
		
		cout<<"Sum of weight is = "<<sum<<endl;
		cout<<endl;
	}
	
	else if(connectedComponent==0)
	{
		cout<<"Error. Must traverse (BFS,DFS) to calcul connected component before this step."<<endl;
		cout<<endl;
	}
	
	else
	{
		cout<<"Error. The graph is not connected."<<endl;
		cout<<endl;
	}
}

/*29*/
void Graph::MST_KR_nom()//Kruskal
{
	/*cout<<"MST (Kruskal) : "<<endl;
	if (connectedComponent==1)
	{
		
		for(int j=0;j<nbVertex;j++)//初始化 
		{
			visit_toWhite(&listVertex[j]);
		}
	
		int copy_matrix[nbVertex][nbVertex]; //copy一个新的邻接矩阵 
		for (int i=0;i<nbVertex;i++)
		{
			for(int j=0;j<nbVertex;j++)
			{
				copy_matrix[i][j] = matrixAdj[i][j];
			}
		} 
	
		int current_shortest_edge;
		int index1,index2;
	
		int sum = 0;
		for(int count=0;count<nbVertex-1;count++)//循环n-1次，每次遍历一次邻接矩阵找到最短边 
		{
			index1 = -1;
			index2 = -1; 
			current_shortest_edge = INT_MAX;
			for (int m=0;m<nbVertex;m++)
			{
				cout<<endl;
				for (int n=0;n<nbVertex;n++)//当前最短边要保证至少连接一个新的顶点 ,判断点1是否已经可以到达点2 
				{
					cout<<union_find(listVertex[m],listVertex[n]);
					if (!union_find(listVertex[m],listVertex[n]) && copy_matrix[m][n]<current_shortest_edge&&copy_matrix[m][n]!=0)
					{
						
						current_shortest_edge=copy_matrix[m][n];
						index1 = m;
						index2 = n;
			
					}
				}
			}
			visit_toBlack(&listVertex[index1]);
			visit_toBlack(&listVertex[index2]);
			copy_matrix[index1][index2] = 0;//访问顶点 
			copy_matrix[index2][index1] = 0;//有向图去掉这一行 
			sum += current_shortest_edge;
			//cout<<"step"<<count+1<<" Add (v"<<listVertex[index1].id<<",v"<<listVertex[index2].id<<") weight = "<<current_shortest_edge<<endl;
			cout<<"step"<<count+1<<" Add ("<<listVertex[index1].nom<<","<<listVertex[index2].nom<<") weight = "<<current_shortest_edge<<endl;
		}
		cout<<"Sum of weight is = "<<sum<<endl;
		cout<<endl;
	}*/
		cout<<"MST (Kruskal) : "<<endl;
	if(connectedComponent==1)
	{
		
		for(int j=0;j<nbVertex;j++)//初始化 
		{
			visit_toWhite(&listVertex[j]);
		}
		
		for(int j=0;j<nbEdge;j++)//初始化 
		{
			visitEdge_0(&listEdge[j]);
		}
		sortEdge();
		
		int sum = 0;
		int count=0;
		for (int i=0;i<nbEdge;i++)
		{	
			if(! union_find(listVertex[sortedEdge[i].src.id],listVertex[sortedEdge[i].dst.id]) || ! union_find(listVertex[sortedEdge[i].dst.id],listVertex[sortedEdge[i].src.id]))
			{
				count++;
				sum += sortedEdge[i].weight;
				visitEdge_1(&listEdge[findEdge(sortedEdge[i].src.id,sortedEdge[i].dst.id)]);
				visitEdge_1(&listEdge[findEdge(sortedEdge[i].dst.id,sortedEdge[i].src.id)]);
				visit_toBlack(&listVertex[sortedEdge[i].src.id]);
				visit_toBlack(&listVertex[sortedEdge[i].dst.id]);
				cout<<"step"<<count<<" Add ("<<sortedEdge[i].src.nom<<","<<sortedEdge[i].dst.nom<<") weight = "<<sortedEdge[i].weight<<endl;
			}
		}
		
		cout<<"Sum of weight is = "<<sum<<endl;
		cout<<endl;
	}
		
	else if(connectedComponent==0)
	{
		cout<<"Error. Must traverse (BFS,DFS) to calcul connected component before this step."<<endl;
		cout<<endl;
	}
	
	else
	{
		cout<<"Error. The graph is not connected."<<endl;
		cout<<endl;
	}
}

/*16*/
void Graph::MST_PR_id()//Prim
{
	cout<<"MST (Prim) : "<<endl;
	if (connectedComponent==1)
	{
		
		for(int j=0;j<nbVertex;j++)//初始化 
		{
			visit_toWhite(&listVertex[j]);
		}
	
		int copy_matrix[nbVertex][nbVertex]; //copy_matrix一个新的邻接矩阵 
		for (int i=0;i<nbVertex;i++)
		{
			for(int j=0;j<nbVertex;j++)
			{
				copy_matrix[i][j] = matrixAdj[i][j];
			}
		} 
		int current_shortest_edge;
		int index1,index2;
		int sum = 0;
	
		visit_toBlack(&listVertex[0]);
	
		for(int count=0;count<nbVertex-1;count++)//循环n-1次，每次遍历一次邻接矩阵找到最短边 
		{
			index1 = -1;
			index2 = -1; 
			current_shortest_edge = INT_MAX;
		
			for (int i=0;i<nbVertex;i++)//找到所有已添加入的定点的最短边，且该最短边至少要连接一个新顶点 
			{
				if(listVertex[i].visited!=0)
				{ 
					for(int j=0;j<nbVertex;j++)
					{
						if(listVertex[j].visited==0)
						{
							if(matrixAdj[i][j]<current_shortest_edge && matrixAdj[i][j]!=0)
							{
								 current_shortest_edge = matrixAdj[i][j];
								index1 = i;
								index2 = j;
							}
						}
					}	
				}
			}
			visit_toBlack(&listVertex[index1]);
			visit_toBlack(&listVertex[index2]);
			sum += current_shortest_edge;
			cout<<"step"<<count+1<<" Add (v"<<listVertex[index1].id<<",v"<<listVertex[index2].id<<") weight = "<<current_shortest_edge<<endl;
			//cout<<"step"<<count+1<<" Add ("<<listVertex[index1].nom<<","<<listVertex[index2].nom<<") weight = "<<current_shortest_edge<<endl;
		}
		cout<<"Sum of weight is = "<<sum<<endl;
		cout<<endl;
	}
	
	else if(connectedComponent==0)
	{
		cout<<"Error. Must traverse (BFS,DFS) to calcul connected component before this step."<<endl;
		cout<<endl;
	}
	
	else
	{
		cout<<"Error. The graph is not connected."<<endl;
		cout<<endl;
	}
	
}

/*30*/
void Graph::MST_PR_nom()//Prim
{
	cout<<"MST (Prim) : "<<endl;
	if(connectedComponent==1)
	{
		
		for(int j=0;j<nbVertex;j++)//初始化 
		{
			visit_toWhite(&listVertex[j]);
		}
	
		int copy_matrix[nbVertex][nbVertex]; //copy_matrix一个新的邻接矩阵 
		for (int i=0;i<nbVertex;i++)
		{
			for(int j=0;j<nbVertex;j++)
			{
				copy_matrix[i][j] = matrixAdj[i][j];
			}
		} 
		int current_shortest_edge;
		int index1,index2;
		int sum = 0;
	
		visit_toBlack(&listVertex[0]);
	
		for(int count=0;count<nbVertex-1;count++)//循环n-1次，每次遍历一次邻接矩阵找到最短边 
		{
			index1 = -1;
			index2 = -1; 
			current_shortest_edge = INT_MAX;
		
			for (int i=0;i<nbVertex;i++)//找到所有已添加入的定点的最短边，且该最短边至少要连接一个新顶点 
			{
				if(listVertex[i].visited!=0)
				{ 
					for(int j=0;j<nbVertex;j++)
					{
						if(listVertex[j].visited==0)
						{
							if(matrixAdj[i][j]<current_shortest_edge && matrixAdj[i][j]!=0)
							{
								 current_shortest_edge = matrixAdj[i][j];
								index1 = i;
								index2 = j;
							}
						}
					}
				}
			}
			visit_toBlack(&listVertex[index1]);
			visit_toBlack(&listVertex[index2]);
			sum += current_shortest_edge;
			//cout<<"step"<<count+1<<" Add (v"<<listVertex[index1].id<<",v"<<listVertex[index2].id<<") weight = "<<current_shortest_edge<<endl;
			cout<<"step"<<count+1<<" Add ("<<listVertex[index1].nom<<","<<listVertex[index2].nom<<") weight = "<<current_shortest_edge<<endl;
		}
		cout<<"Sum of weight is = "<<sum<<endl;
		cout<<endl;
	}
	
	else if(connectedComponent==0)
	{
		cout<<"Error. Must traverse (BFS,DFS) to calcul connected component before this step."<<endl;
		cout<<endl;
	}
	
	else
	{
		cout<<"Error. The graph is not connected."<<endl;
		cout<<endl;
	}
	
}

/*6*/
void Graph::show_id()
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

/*31*/
void Graph::show_nom()
{
	if(struct_type)
	{
		cout<<"Adjacency Matrix : "<<endl;
    	for (int i=0;i<nbVertex;i++)
    	{
    		//cout<<"v"<<listVertex[i].id<<" ";
    		cout<<listVertex[i].nom<<" ";
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
    		cout<<listVertex[i].nom<<": ";
    		int current_size = listAdj[i].size();
    		for (int j=0;j<current_size;j++)
    		{
    			cout<<"("<<listAdj[i][j]<<","<<matrixAdj[i][listAdj[i][j]]<<") ";
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
void Graph::file2graph(){
	
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
void Graph::graph_o_matrix()
{
	matrixAdj = new int *[nbVertex];
	for (int i = 0; i<nbVertex; i++)
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
   		matrixAdj[m][n] = listEdge[i].weight;	//双向为无向图，单向为有向图 	
  	} 
}

/*18*/
void Graph::graph_n_matrix()
{
	matrixAdj = new int *[nbVertex];
	for (int i = 0; i<nbVertex; i++)//初始化 
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
   		matrixAdj[m][n] = listEdge[i].weight;	//双向为无向图，单向为有向图 
   		matrixAdj[n][m] = listEdge[i].weight;
  	} 
}

/*19*/
void Graph::graph_o_list()
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
void Graph::graph_n_list()
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
    
    ifstream infile(filename_);// 定义输入文件流类对象infile
    
    if(!infile)// 判断文件是否存在
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
            Vertex v = Vertex(i);//Vertex *v = new Vertex(i);
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
    if(ml=="l") struct_type=0;
    else if(ml=="m") 
		struct_type=1;
    else 
    {
        cout<<"The type of the graph is unknown. "<<endl;
        return -1;
    }
    
    cout<<"Third line: "<<ml<<endl;  

    if(infile.eof()!=0)
    {
        cout<<"We do not have numbers on the following lines"<<endl;
        exit(1);
    }

    char ch;
    double *tab=new double[100];
    int i=0,k1=0,k2=0;
    while (!infile.eof())
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
            k1++;k2=0;
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

