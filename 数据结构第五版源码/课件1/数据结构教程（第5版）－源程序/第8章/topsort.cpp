//拓扑排序算法
#include "graph.cpp"
void TopSort(AdjGraph *G)			//拓扑排序算法
{	int i,j;
	int St[MAXV],top=-1;			//栈St的指针为top
	ArcNode *p;
	for (i=0;i<G->n;i++)			//入度置初值0
		G->adjlist[i].count=0;
	for (i=0;i<G->n;i++)			//求所有顶点的入度
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	G->adjlist[p->adjvex].count++;
			p=p->nextarc;
		}
	}
	for (i=0;i<G->n;i++)			//将入度为0的顶点进栈
		if (G->adjlist[i].count==0)
		{	top++;
			St[top]=i;
		}
	while (top>-1)					//栈不空循环
	{	i=St[top];top--;			//出栈一个顶点i
		printf("%d ",i);			//输出该顶点
		p=G->adjlist[i].firstarc;	//找第一个邻接点
		while (p!=NULL)				//将顶点i的出边邻接点的入度减1
		{	j=p->adjvex;
			G->adjlist[j].count--;
			if (G->adjlist[j].count==0)//将入度为0的邻接点进栈
			{	top++;
				St[top]=j;
			}
			p=p->nextarc;			//找下一个邻接点
		}
	}
}

int main()
{
	AdjGraph *G;
	int A[MAXV][MAXV]=
	{{0,1,INF,INF,INF,INF},
	{INF,0,1,INF,INF,INF},
	{INF,INF,0,1,INF,INF},
	{INF,INF,INF,0,INF,INF},
	{INF,1,INF,INF,0,1},
	{INF,INF,INF,1,INF,0}};
	int n=6, e=6;
	CreateAdj(G,A,n,e);			//建立《教程》中图8.44的邻接表
	printf("图G的邻接表:\n");
	DispAdj(G);					//输出邻接表G
	printf("拓扑序列:");TopSort(G);printf("\n");
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
