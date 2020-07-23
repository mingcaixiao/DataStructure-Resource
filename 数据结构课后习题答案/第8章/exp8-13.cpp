//文件名:exp8-13.cpp
#include "graph.cpp"			//包含图的存储结构及基本运算算法
void Dispapath(int path[][MAXV],int i,int j)	//输出顶点i到j的一条最短路径
{
	int apath[MAXV],d;			//存放一条最短路径中间顶点(反向)及其顶点个数
	int k=path[i][j];
	d=0; apath[d]=j;			//路径上添加终点
	while (k!=-1 && k!=i)		//路径上添加中间点
	{	
		d++; apath[d]=k;
		k=path[i][k];
	}
	d++; apath[d]=i;			//路径上添加起点
	for (int s=d;s>=0;s--)		//输出路径上的中间顶点
		printf("%d→",apath[s]);
}
int Mincycle(MatGraph g,int A[MAXV][MAXV],int &mini,int &minj)	//在图g和A中的查找一个最小环
{
	int i,j,min=INF;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
			if (i!=j && g.edges[j][i]<INF)
			{
				if (A[i][j]+g.edges[j][i]<min)
				{
					min=A[i][j]+g.edges[j][i];
					mini=i; minj=j;
				}
			}
	return min;
}

void Floyd(MatGraph g)						//Floyd算法求图g中的一个最小环
{	int A[MAXV][MAXV],path[MAXV][MAXV];
	int i,j,k,min,mini,minj;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++) 
		{	A[i][j]=g.edges[i][j];
			if (i!=j && g.edges[i][j]<INF)
				path[i][j]=i;				//顶点i到j有边时
			else
				path[i][j]=-1;				//顶点i到j没有边时
		}
	for (k=0;k<g.n;k++)						//依次考察所有顶点
	{	for (i=0;i<g.n;i++)
			for (j=0;j<g.n;j++)
				if (A[i][j]>A[i][k]+A[k][j])
				{	A[i][j]=A[i][k]+A[k][j];	//修改最短路径长度
					path[i][j]=path[k][j];		//修改最短路径
				}
	}
	min=Mincycle(g,A,mini,minj);
	if (min!=INF)
	{
		printf("  图中最小环：");
		Dispapath(path,mini,minj);	//输出一条最短路径
		printf("%d, 长度：%d\n",mini,min);
	}
	else
		printf("  图中没有任何环\n");


}
int main()
{
	MatGraph g;
	int A[MAXV][MAXV]={
		{0,10,1,INF},
		{21,0,INF,6},
		{INF,1,0,INF},
		{5,INF,INF,0} };
	int n=4, e=6;
	CreateMat(g,A,n,e);		//建立图的邻接矩阵
	printf("有向图G的邻接矩阵:\n"); DispMat(g);
	printf("求解结果:\n");
	Floyd(g);
	return 1;
}