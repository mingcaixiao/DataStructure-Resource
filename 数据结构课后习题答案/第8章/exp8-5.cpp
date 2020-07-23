//文件名:exp8-5.cpp
#include "graph.cpp"			//包含图的存储结构及基本运算算法
void Prim(MatGraph g,int v)
{
	int lowcost[MAXV],min,n=g.n;
	int closest[MAXV],i,j,k;
	for (i=0;i<n;i++)          	//给lowcost[]和closest[]置初值
	{	
		lowcost[i]=g.edges[v][i];
		closest[i]=v;
	}
	for (i=1;i<n;i++)          	//找出n-1个顶点
	{   
		min=INF;
	    for (j=0;j<n;j++)       //在(V-U)中找出离U最近的顶点k
		   	if (lowcost[j]!=0 && lowcost[j]<min) 
			{	
				min=lowcost[j]; k=j;  
			}
		printf("  边(%d,%d)权为:%d\n",closest[k],k,min);
		lowcost[k]=0;         	//标记k已经加入U
		for (j=0;j<n;j++)   	//修改数组lowcost和closest
           	if (g.edges[k][j]!=0 && g.edges[k][j]<lowcost[j]) 
			{	lowcost[j]=g.edges[k][j];
				closest[j]=k; 
			}
	}
}
int main()
{
	int v=3;
	MatGraph g;
	int A[MAXV][MAXV]={
		{0,5,8,7,INF,3},
		{5,0,4,INF,INF,INF},
		{8,4,0,5,INF,9},
		{7,INF,5,0,5,6},
		{INF,INF,INF,5,0,1},
		{3,INF,9,6,1,0}};
	int n=6,e=10;
	CreateMat(g,A,n,e);		//建立图8.10的邻接矩阵
	printf("图G的邻接矩阵:\n");	DispMat(g);
	printf("普里姆算法求解结果:\n");
	Prim(g,0);
	return 1;
}
