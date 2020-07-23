//【例8.4】的算法:判断图G中从顶点u到v是否存在简单路径
#include "graph.cpp"
int visited[MAXV];					//全局数组
void ExistPath(AdjGraph *G,int u,int v,bool &has)
{	//has表示u到v是否有路径,初值为false
	int w; ArcNode *p;
	visited[u]=1;					//置已访问标记
	if (u==v)						//找到了一条路径
	{	has=true;					//置has为true并返回
		return;
	}
	p=G->adjlist[u].firstarc;		//p指向顶点u的第一个邻接点
	while (p!=NULL)
	{	w=p->adjvex;				//w为顶点u的邻接点
		if (visited[w]==0)			//若w顶点未访问,递归访问它
			ExistPath(G,w,v,has);
		p=p->nextarc;				//p指向顶点u的下一个邻接点
	}
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
	bool has=false;
	int u=0, v=3;
	ExistPath(G,u,v,has);
	printf("\n图G中顶点%d到顶点%d%s路径\n\n",u,v,(has?"有":"没有"));
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
