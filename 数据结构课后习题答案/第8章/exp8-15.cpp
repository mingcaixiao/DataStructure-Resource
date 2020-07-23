//文件名:exp8-15.cpp
#include "graph.cpp"			//包含图的存储结构及基本运算算法
#define MAXE 100	//最多的边数
typedef struct 
{	
	int u;			//边的起始顶点
    int v;			//边的终止顶点
    int w;			//边的权值
} Edge;

int visited[MAXV];		//全局变量

void MDFS(MatGraph g,int v)				//采用邻接矩阵的图深度优先遍历
{	int w;
	visited[v]=1;						//置访问标记
	for (w=0;w<g.n;w++)					//找顶点v的所有邻接点
		if (g.edges[v][w]!=0 && g.edges[v][w]!=INF && visited[w]==0)
			MDFS(g,w);					//找顶点v的未访问过的邻接点w
}
bool connect(MatGraph g)				//判定图g的连通性
{
	bool flag=true;
	int k;
	for (k=0;k<g.n;k++)
		visited[k]=0;
	MDFS(g,0);
	for (k=0;k<g.n;k++)
		if (visited[k]==0)
			flag=false;
	return flag;
}
void spantree(MatGraph &g)					//求图g的最小生成树
{
	int i,j,k,e;
	k=0;
	Edge tmp;
	Edge edges[MAXE];
	for (i=0;i<g.n;i++)						//获取图中所有边信息
		for (j=0;j<i;j++)
			if (g.edges[i][j]!=0 && g.edges[i][j]!=INF)
			{
				edges[k].u=i;
				edges[k].v=j;
				edges[k].w=g.edges[i][j];
				k++;
			}
	for (i=1;i<g.e;i++)						//将edges数组按w递减排序
	{	if (edges[i].w>edges[i-1].w) 
		{	tmp=edges[i];
			j=i-1; 
			do
			{	edges[j+1]=edges[j];
				j--;
			}  while  (j>=0 && edges[j].w<tmp.w);
			edges[j+1]=tmp;
		} 
	}
	k=0; e=g.e;
	while (e>=g.n)
	{
		g.edges[edges[k].u][edges[k].v]=INF;	//删除第k条边
		g.edges[edges[k].v][edges[k].u]=INF;
		if (connect(g))							//若连通,则删除
		{
			e--;
			printf("  (%d)删除边(%d,%d):%d\n",g.e-e,edges[k].u,edges[k].v,edges[k].w);
			//输出最小生成树的一条边
		}
		else									//若不连通,则恢复
		{
			g.edges[edges[k].u][edges[k].v]=edges[k].w;	//恢复第k条边
			g.edges[edges[k].v][edges[k].u]=edges[k].w;
		}
		k++;
	}
	g.e-=e;										//修改图中的边数
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
	printf("产生最小生成树的过程:\n");
	spantree(g);
	printf("最小生成树如下:\n");
	DispMat(g);					//输出邻接矩阵
	return 1;
}

