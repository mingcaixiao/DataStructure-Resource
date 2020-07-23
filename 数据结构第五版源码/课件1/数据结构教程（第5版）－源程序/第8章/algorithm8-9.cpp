//【例8.9】的算法:求不带权无向连通图G中从顶点u到顶点v的一条最短路径。
#include "graph.cpp"
int visited[MAXV];
typedef struct
{	int data;						//顶点编号
	int parent;						//前一个顶点的位置
} QUERE;							//非环形队列类型
void ShortPath(AdjGraph *G,int u,int v)
{	//输出从顶点u到顶点v的最短逆路径
	ArcNode *p;
	int w,i;
	QUERE qu[MAXV];					//非环形队列
	int front=-1,rear=-1;			//队列的头、尾指针
	int visited[MAXV];
	for (i=0;i<G->n;i++)			//访问标记置初值0
		visited[i]=0;
	rear++;							//顶点u进队
	qu[rear].data=u;
	qu[rear].parent=-1;
	visited[u]=1;
	while (front!=rear)				//队不空循环
	{	front++;					//出队顶点w
		w=qu[front].data;
		if (w==v)					//找到v时输出路径之逆并退出
		{	i=front;				//通过队列输出逆路径
			while (qu[i].parent!=-1)
			{	printf("%2d ",qu[i].data);
				i=qu[i].parent;
			}
			printf("%2d\n",qu[i].data);
			break; 
		}
		p=G->adjlist[w].firstarc;	//找w的第一个邻接点
		while (p!=NULL)
		{	if (visited[p->adjvex]==0)
			{	visited[p->adjvex]=1;
				rear++;				//将w的未访问过的邻接点进队
				qu[rear].data=p->adjvex;
				qu[rear].parent=front;
			}
			p=p->nextarc;			//找w的下一个邻接点
		}
	}
}

int main()
{ 
	int n=5, e=7;
	int A[MAXV][MAXV]={
		{0,1,1,0,0},{0,0,1,0,0},{0,0,0,1,1},
		{0,0,0,0,1},{1,0,0,0,0}};	

	AdjGraph *G;
	CreateAdj(G,A,n,e);			////建立图8.19的邻接表
	printf("图G:\n");DispAdj(G);//输出邻接表
	int u=0,v=4;
	printf("图G中顶点%d到%d的最短逆路径:\n",u,v);
	ShortPath(G,u,v);
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
