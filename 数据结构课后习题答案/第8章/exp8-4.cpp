//文件名:exp8-4.cpp
#include "graph.cpp"					//包含图的存储结构及基本运算算法
#define MaxSize 100
int visited[MAXV]={0};
void DFSTree(AdjGraph *G,int v)			//求图G从顶点v出发的深度优先生成树
{
	ArcNode *p;
	visited[v]=1;						//置已访问标记
	p=G->adjlist[v].firstarc;      		//p指向顶点v的第一个相邻点
	while (p!=NULL) 
	{
		if (visited[p->adjvex]==0)		//若p->adjvex顶点未访问,递归访问它
		{
			printf("(%d,%d) ",v,p->adjvex);
			DFSTree(G,p->adjvex);    
		}
		p=p->nextarc;              		//p指向顶点v的下一个相邻点
	}
}
void BFSTree(AdjGraph *G,int v)			//求图G从顶点v出发的广度优先生成树
{
	int w,i;
	int qu[MAXV];						//定义环形队列
	int front=0,rear=0;
	ArcNode *p;
	int visited[MAXV];            		//定义顶点访问标志数组
	for (i=0;i<G->n;i++) visited[i]=0;	//访问标志数组初始化
	visited[v]=1;              			//置已访问标记
	rear++;								//顶点v进队
	qu[rear]=v;
	while (front!=rear)       			//队不空循环
	{	
		front=(front+1) % MAXV;			//出队一个顶点w
		w=qu[front];
		p=G->adjlist[w].firstarc; 		//p指向w的第一个相邻点
		while (p!=NULL)					//查找w的所有相邻点
		{	
			if (visited[p->adjvex]==0) 	//若当前邻接点未被访问
			{
				printf("(%d,%d) ",w,p->adjvex);
				visited[p->adjvex]=1;	//置已访问标记
				rear=(rear+1) % MAXV;	//顶点p->adjvex进队
				qu[rear]=p->adjvex;
           	}
           	p=p->nextarc;              	//p指向顶点v的下一个相邻点
		}
	}
	printf("\n");
}
int main()
{
	AdjGraph *G;
	int A[MAXV][MAXV];
	int n=11, e=13;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			A[i][j]=0;
	A[0][1]=1; 	A[0][2]=1; A[0][3]=1;
	A[1][0]=1; A[1][4]=1; A[1][5]=1;
	A[2][0]=1; A[2][3]=1; A[2][5]=1; A[2][6]=1;
	A[3][0]=1; A[3][2]=1; A[3][7]=1;
	A[4][1]=1;
	A[5][1]=1; A[5][2]=1;
	A[6][2]=1; A[6][7]=1; A[6][8]=1; A[6][9]=1;
	A[7][3]=1; A[7][6]=1; A[7][10]=1;
	A[8][6]=1;
	A[9][6]=1;
	A[10][7]=1;
	CreateAdj(G,A,n,e);			//建立《教程》中图8.24的邻接表
	printf("图G的邻接表:\n");
	DispAdj(G);	
	int v=3;					//输出邻接表G
	printf("深度优先生成树:\n");DFSTree(G,v);printf("\n");
	printf("广度优先生成树:\n");BFSTree(G,v);
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
