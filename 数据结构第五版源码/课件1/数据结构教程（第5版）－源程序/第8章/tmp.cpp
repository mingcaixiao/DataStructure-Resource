
#include "graph.cpp"
int visited[MAXV];					//全局变量
void hasCycle(AdjGraph *G,int v,bool &has)
//判断从顶点v出发能否找到环
{
	ArcNode *p;
	int w;
	visited[v]=1;				//置已访问标记
	p=G->adjlist[v].firstarc;	//p指向顶点v的第一个邻接点
	while (p!=NULL)
	{	w=p->adjvex;
		if (visited[w]==0)		//若顶点w未访问，递归访问它
			hasCycle(G,w,has);
		else					//又找到了已访问过的顶点说明有回路
			has=true;
		p=p->nextarc;			//找下一个邻接点
	}
	visited[v]=0;
}
bool Cycle(AdjGraph *G)         //判断有向图G中是否存在环
{
	bool has=false;
	for (int i=0;i<G->n;i++)
	{
		hasCycle(G,i,has);
		if (has) return true;
	}
	return false;
}
int main()
{ 
/*	int n=7, e=12;
	int A[MAXV][MAXV]={
		{0,  2,  5,  3,  INF,INF,INF},
		{INF,0,  2,  INF,INF,8,  INF},
		{INF,INF,0,  1,  3,  5,  INF},
		{INF,INF,INF,0,  5,  INF,INF},
		{INF,INF,INF,INF,0,  3,  9},
		{INF,INF,INF,INF,INF,0,  5},
		{INF,INF,INF,INF,INF,INF,0}
	};	
*/

	int n=4, e=4;
	int A[MAXV][MAXV]={
		{0,  1,  1,INF},
		{INF, 0, INF,INF},
		{INF,1,    0,1},
		{INF,INF,INF,0}

	};	

	AdjGraph *G;
	CreateAdj(G,A,n,e);			////建立图8.19的邻接表
	for (int i=0;i<n;i++) 		//visited数组置初值
		visited[i]=0;
	printf("图G:\n");DispAdj(G);//输出邻接表
	bool has=false;
	printf("has=%d\n",Cycle(G));
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
