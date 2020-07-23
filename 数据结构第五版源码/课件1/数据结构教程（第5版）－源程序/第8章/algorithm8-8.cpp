//【例8.8】的算法:输出一个有向图中通过某个顶点的所有回路
#include "graph.cpp"
int visited[MAXV];					//全局变量
void DFSPath(AdjGraph *G,int u,int v,int path[],int d)
{	//d表示path中的路径长度，初始为-1
	int w,i;
	ArcNode *p;
	visited[u]=1;
	d++; path[d]=u;
	p=G->adjlist[u].firstarc;		//p指向顶点u的第一个邻接点
	while (p!=NULL)
	{	w=p->adjvex;				//w为顶点u的邻接点
		if (w==v && d>0)			//找到一个回路，输出之
		{	printf("  ");
			for (i=0;i<=d;i++)
				printf("%d ",path[i]);
			printf("%d \n",v);
		}
		if (visited[w]==0)			//若w未访问,则递归访问之
			DFSPath(G,w,v,path,d);
		p=p->nextarc;				//找u的下一个邻接点
	}
	visited[u]=0;					//恢复环境：使该顶点可重新使用
}
void FindCyclePath(AdjGraph *G,int k)	//输出经过顶点k的所有回路
{	int path[MAXV];
	DFSPath(G,k,k,path,-1);
}

int main()
{ 
	int n=5, e=7;
	int A[MAXV][MAXV]={
		{0,1,1,0,0},{0,0,1,0,0},{0,0,0,1,1},
		{0,0,0,0,1},{1,0,0,0,0}};	

	AdjGraph *G;
	CreateAdj(G,A,n,e);			////建立图8.19的邻接表
	for (int i=0;i<n;i++) 		//visited数组置初值
		visited[i]=0;
	printf("图G:\n");DispAdj(G);//输出邻接表
	int k=0;
	printf("图G中经过顶点%d的所有回路:\n",k);
	FindCyclePath(G,k);
	printf("\n");
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
