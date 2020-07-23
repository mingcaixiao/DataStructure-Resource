//【例8.3】的算法:判断无向图G是否连通
#include "graph.cpp"
int visited[MAXV];					//全局数组
void DFS(AdjGraph *G,int v)			//深度优先遍历算法
{	ArcNode *p;
	visited[v]=1;					//置已访问标记
	printf("%d  ",v);				//输出被访问顶点的编号
	p=G->adjlist[v].firstarc;		//p指向顶点v的第一个邻接点
	while (p!=NULL)
	{	if (visited[p->adjvex]==0)	//若p->adjvex顶点未访问,递归访问它
			DFS(G,p->adjvex);
		p=p->nextarc;				//p指向顶点v的下一个邻接点
	}
}

bool Connect(AdjGraph *G)	//判断无向图G的连通性
{	int i;
	bool flag=true;
	for (i=0;i<G->n;i++)	//visited数组置初值
		visited[i]=0;
	DFS(G,0);				//调用前面的中DSF算法,从顶点0开始深度优先遍历
	for (i=0;i<G->n;i++)
		if (visited[i]==0)
		{	flag=false;
			break;
		}
	return flag;
}

int main()
{
	AdjGraph *G;
	int A[MAXV][MAXV]={{0,1,0,1,1},{1,0,1,1,0},
			{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0}};
	int n=5, e=8;
	CreateAdj(G,A,n,e);			//建立《教程》中图8.1(a)的邻接表
	printf("图G的邻接表:\n");
	DispAdj(G);					//输出邻接表G
	printf("\n图G%s连通的\n",(Connect(G)?"是":"不是"));
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
