//文件名:exp8-3.cpp
#include "graph.cpp"		//包含图的存储结构及基本运算算法
int visited[MAXV];
void DFSALL(AdjGraph *G,int v,int path[],int d)  
{
	ArcNode *p;
	visited[v]=1;                   //置已访问标记
	path[d]=v;
	d++;
	if (d==G->n)					//如果已访问所有顶点，则输出访问序列
	{
		for (int k=0;k<d;k++)
			printf("%2d",path[k]);
		printf("\n");
	}
	p=G->adjlist[v].firstarc;      	//p指向顶点v的第一个相邻点
	while (p!=NULL) 
	{
		if (visited[p->adjvex]==0)	//若p->adjvex顶点未访问,递归访问它
			DFSALL(G,p->adjvex,path,d);    
		p=p->nextarc;              	//找顶点v的下一个相邻点
	}
	visited[v]=0;
}
int main()
{
	AdjGraph *G;
	int A[MAXV][MAXV]={
		{0,1,0,1,1},
		{1,0,1,1,0},
		{0,1,0,1,1},
		{1,1,1,0,1},
		{1,0,1,1,0}};	
	int n=5,e=8;			//《教程》中图8.1中的数据
	CreateAdj(G,A,n,e);
	printf("图G的邻接表:\n"); DispAdj(G);
	
	int path[MAXV],v=1;
	printf("从顶点%d出发的所有深度优先序列:\n",v);
	DFSALL(G,v,path,0);
	printf("\n");

	DestroyAdj(G);
	return 1;

}
