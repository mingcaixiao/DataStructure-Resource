//Dijkstra算法
#include "graph.cpp"
void Dispath(MatGraph g,int dist[],int path[],int S[],int v)
//输出从顶点v出发的所有最短路径
{	int i,j,k;
	int apath[MAXV],d;					//存放一条最短路径(逆向)及其顶点个数
	for (i=0;i<g.n;i++)					//循环输出从顶点v到i的路径
		if (S[i]==1 && i!=v)
		{	printf("  从顶点%d到顶点%d的路径长度为:%d\t路径为:",v,i,dist[i]);
			d=0; apath[d]=i;			//添加路径上的终点
			k=path[i];
			if (k==-1)					//没有路径的情况
				printf("无路径\n");
			else						//存在路径时输出该路径
			{	while (k!=v)
				{	d++; apath[d]=k;
					k=path[k];
				}
				d++; apath[d]=v;		//添加路径上的起点
				printf("%d",apath[d]);	//先输出起点
				for (j=d-1;j>=0;j--)	//再输出其他顶点
					printf(",%d",apath[j]);
				printf("\n");
			}
		}
}

void Dijkstra(MatGraph g,int v)	//Dijkstra算法
{	int dist[MAXV],path[MAXV];
	int S[MAXV];				//S[i]=1表示顶点i在S中, S[i]=0表示顶点i在U中
	int Mindis,i,j,u;
	for (i=0;i<g.n;i++)
	{	dist[i]=g.edges[v][i];	//距离初始化
		S[i]=0;					//S[]置空
		if (g.edges[v][i]<INF)	//路径初始化
			path[i]=v;			//顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i]=-1;			//顶点v到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[v]=1;path[v]=0;			//源点编号v放入S中
	for (i=0;i<g.n-1;i++)		//循环直到所有顶点的最短路径都求出
	{	Mindis=INF;				//Mindis置最大长度初值
		for (j=0;j<g.n;j++)		//选取不在S中（即U中）且具有最小最短路径长度的顶点u
			if (S[j]==0 && dist[j]<Mindis) 
			{	u=j;
				Mindis=dist[j];
			}
		S[u]=1;					//顶点u加入S中
		for (j=0;j<g.n;j++)		//修改不在S中（即U中）的顶点的最短路径
			if (S[j]==0)
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j])
				{	dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}
	}
	Dispath(g,dist,path,S,v);	//输出最短路径
}

int main()
{
	MatGraph g;
	int A[MAXV][MAXV]={
		{0,4,6,6,INF,INF,INF},
		{INF,0,1,INF,7,INF,INF},
		{INF,INF,0,INF,6,4,INF},
		{INF,INF,2,0,INF,5,INF},
		{INF,INF,INF,INF,0,INF,6},
		{INF,INF,INF,INF,1,0,8},
		{INF,INF,INF,INF,INF,INF,0}};
	int n=7, e=12;
	CreateMat(g,A,n,e);			//建立《教程》中图8.35的邻接矩阵
	printf("图G的邻接矩阵:\n");
	DispMat(g);					//输出邻接矩阵
	int v=0;
	printf("从%d顶点出发的最短路径如下:\n",v);
	Dijkstra(g,v);
	return 1;
}