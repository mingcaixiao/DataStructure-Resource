//【例8.6】的算法:输出图G中从顶点u到v的所有简单路径
#include "graph.cpp"
int visited[MAXV];					//全局数组
void FindAllPath(AdjGraph *G,int u,int v,int path[],int d)
{	//d表示path中的路径长度，初始为-1
	int w,i; 	ArcNode *p;
	d++; path[d]=u;					//路径长度d增1，顶点u加入到路径中
	visited[u]=1;					//置已访问标记
	if (u==v && d>=0)				//找到一条路径则输出
	{	for (i=0;i<=d;i++)
			printf("%2d",path[i]);
		printf("\n");
	}
	p=G->adjlist[u].firstarc;		//p指向顶点u的第一个邻接点
	while (p!=NULL)
	{	w=p->adjvex;				//w为顶点u的邻接点
		if (visited[w]==0)			//若w顶点未访问,递归访问它
			FindAllPath(G,w,v,path,d);
		p=p->nextarc;				//p指向顶点u的下一个邻接点
	}
	visited[u]=0;					//恢复环境,使该顶点可重新使用
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
	int u=0, v=3;
	int path[MAXV];
	printf("\n图G中顶点%d到顶点%d的所有简单路径:\n",u,v);
	FindAllPath(G,u,v,path,-1);
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
