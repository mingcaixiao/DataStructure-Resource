//Prim算法
#include "graph.cpp"

void Prim(MatGraph g,int v)
{
	int lowcost[MAXV];			//顶点i是否在U中
	int min;
	int closest[MAXV],i,j,k;
	for (i=0;i<g.n;i++)          //给lowcost[]和closest[]置初值
	{	
		lowcost[i]=g.edges[v][i];
		closest[i]=v;
	}
	for (i=1;i<g.n;i++)          //找出n-1个顶点
	{
		min=INF;
		for (j=0;j<g.n;j++)       //在(V-U)中找出离U最近的顶点k
			if (lowcost[j]!=0 && lowcost[j]<min) 
			{
				min=lowcost[j];
				k=j;			//k记录最近顶点的编号
			}
		printf(" 边(%d,%d)权为:%d\n",closest[k],k,min);
		lowcost[k]=0;         	//标记k已经加入U
		for (j=0;j<g.n;j++)   	//修改数组lowcost和closest
			if (g.edges[k][j]!=0 && g.edges[k][j]<lowcost[j]) 
			{
				lowcost[j]=g.edges[k][j];
				closest[j]=k; 
			}
	}
}
int main()
{
	MatGraph g;
	int A[MAXV][MAXV]={
		{0,28,INF,INF,INF,10,INF},
		{28,0,16,INF,INF,INF,14},
		{INF,16,0,12,INF,INF,INF},
		{INF,INF,12,0,22,INF,18},
		{INF,INF,INF,22,0,25,24},
		{10,INF,INF,INF,25,0,INF},
		{INF,14,INF,18,24,INF,0}};
	int n=7, e=9;
	CreateMat(g,A,n,e);			//建立《教程》中图8.27的邻接矩阵
	printf("图G的邻接矩阵:\n");
	DispMat(g);					//输出邻接矩阵
	int v=0;
	printf("Prim算法结果(起始点为%d)\n",v);
	Prim(g,v);
	return 1;
}
