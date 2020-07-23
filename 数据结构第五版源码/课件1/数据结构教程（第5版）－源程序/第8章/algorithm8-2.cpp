//【例8.2】对应的算法：邻接矩阵和邻接表的相互转换
#include "graph.cpp"
void MatToList(MatGraph g,AdjGraph *&G)		//将邻接矩阵g转换成邻接表G
{	int i,j;
	ArcNode *p;
	G=(AdjGraph *)malloc(sizeof(AdjGraph));
	for (i=0;i<g.n;i++)				//将邻接表中所有头结点的指针域置初值
		G->adjlist[i].firstarc=NULL;
	for (i=0;i<g.n;i++)				//检查邻接矩阵中每个元素
		for (j=g.n-1;j>=0;j--)
			if (g.edges[i][j]!=0 && g.edges[i][j]!=INF)	//存在一条边
			{	p=(ArcNode *)malloc(sizeof(ArcNode));	//创建一个边结点p
				p->adjvex=j; p->weight= g.edges[i][j];
				p->nextarc=G->adjlist[i].firstarc;		//采用头插法插入结点p
				G->adjlist[i].firstarc=p;
			}
	G->n=g.n;G->e=g.e;
}
void ListToMat(AdjGraph *G,MatGraph &g) //将邻接表G转换成邻接矩阵g
{	int i;
	ArcNode *p;
	for (i=0;i<G->n;i++)			//扫描所有的单链表
	{	p=G->adjlist[i].firstarc;	//p指向第i个单链表的首结点
		while (p!=NULL)				//扫描第i个单链表
		{	g.edges[i][p->adjvex]=p->weight;
			p=p->nextarc;
		}
	}
	g.n=G->n;g.e=G->e;
}

int main()
{
	MatGraph g;
	AdjGraph *G;
	int A[MAXV][MAXV]={{0,1,0,1,1},{1,0,1,1,0},
			{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0}};
	int n=5, e=8;
	CreateMat(g,A,n,e);			//建立《教程》中图8.1(a)的邻接矩阵
	printf("图G的邻接矩阵:\n");
	DispMat(g);					//输出邻接矩阵g
	printf("将g转换为邻接表G\n");
	MatToList(g,G);				//输出邻接表G
	printf("图G的邻接表:\n");
	DispAdj(G);
	DestroyAdj(G);				//销毁邻接表
	CreateAdj(G,A,n,e);			//建立《教程》中图8.1(a)的邻接表
	printf("图G的邻接表:\n");
	DispAdj(G);					//输出邻接表G
	printf("将G转换为邻接矩阵g\n");
	ListToMat(G,g);
	DispMat(g);					//输出邻接矩阵g
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
