//广度优先遍历算法
#include "graph.cpp"
#define MaxSize 100
//---------------------------------------------------------
//--广度优先遍历中使用队列的基本运算算法-------------------
//---------------------------------------------------------
typedef int ElemType;
typedef struct 
{	
	ElemType data[MaxSize];
	int front,rear;		//队首和队尾指针
} SqQueue;
void InitQueue(SqQueue *&q)
{	q=(SqQueue *)malloc (sizeof(SqQueue));
	q->front=q->rear=0;
}
void DestroyQueue(SqQueue *&q)
{
	free(q);
}
bool QueueEmpty(SqQueue *q)
{
	return(q->front==q->rear);
}
bool enQueue(SqQueue *&q,ElemType e)
{	if ((q->rear+1)%MaxSize==q->front)	//队满上溢出
		return false;
	q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=e;
	return true;
}
bool deQueue(SqQueue *&q,ElemType &e)
{	if (q->front==q->rear)				//队空下溢出
		return false;
	q->front=(q->front+1)%MaxSize;
	e=q->data[q->front];
	return true;
}
//---------------------------------------------------------

void BFS(AdjGraph *G,int v)  
{
	int w,i;
	ArcNode *p;
	SqQueue *qu;							//定义环形队列指针
	InitQueue(qu);							//初始化队列
	int visited[MAXV];            			//定义顶点访问标志数组
	for (i=0;i<G->n;i++) visited[i]=0;		//访问标志数组初始化
	printf("%2d",v); 						//输出被访问顶点的编号
	visited[v]=1;              				//置已访问标记
	enQueue(qu,v);
	while (!QueueEmpty(qu))       			//队不空循环
	{	
		deQueue(qu,w);						//出队一个顶点w
		p=G->adjlist[w].firstarc; 			//指向w的第一个邻接点
		while (p!=NULL)						//查找w的所有邻接点
		{	
			if (visited[p->adjvex]==0) 		//若当前邻接点未被访问
			{
				printf("%2d",p->adjvex);  	//访问该邻接点
				visited[p->adjvex]=1;		//置已访问标记
				enQueue(qu,p->adjvex);		//该顶点进队
           	}
           	p=p->nextarc;              		//找下一个邻接点
		}
	}
	printf("\n");
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
	printf("广度优先序列:");BFS(G,2);printf("\n");
	DestroyAdj(G);				//销毁邻接表
	return 1;
}
