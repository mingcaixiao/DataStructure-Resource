//【例8.10】的算法:求不带权无向连通图G中距离顶点v的最远的一个顶点
#include "graph.cpp"

int Maxdist(AdjGraph *G,int v)
{	ArcNode *p;
	int Qu[MAXV];					//环形队列
	int front=0,rear=0;				//队列的头、尾指针
	int visited[MAXV];				//访问标记数组
	int i,j,k;
	for (i=0;i<G->n;i++)			//初始化访问标志数组
		visited[i]=0;
	rear++;Qu[rear]=v;				//顶点v进队
	visited[v]=1;					//标记v已访问
	while (rear!=front) 
	{	front=(front+1)%MAXV;
		k=Qu[front];				//顶点k出队
		p=G->adjlist[k].firstarc;	//找第一个邻接点
		while (p!=NULL)				//所有未访问过的邻接点进队
		{	j=p->adjvex;			//邻接点为顶点j
			if (visited[j]==0)		//若j未访问过
			{	visited[j]=1;
				rear=(rear+1)%MAXV;Qu[rear]=j; //进队
			}
			p=p->nextarc;			//找下一个邻接点
		}
	}
	return k;
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
	int v=0,k;
	k=Maxdist(G,v);
	printf("图G中距离顶点%d的最远的顶点是%d\n",v,k);
	DestroyAdj(G);				//销毁邻接表
	return 1;
}