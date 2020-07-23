//求解报数问题
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef int ElemType;
//----------------------------------------------------------
//-环形队列的基本运算算法-----------------------------------
//----------------------------------------------------------
typedef struct 
{	ElemType data[MaxSize];				//存放队中元素
	int front,rear;						//队头和队尾指针
} SqQueue;								//顺序队类型
void InitQueue(SqQueue *&q)				//初始化队列
{	q=(SqQueue *)malloc (sizeof(SqQueue));
	q->front=q->rear=0;
}
void DestroyQueue(SqQueue *&q)			//销毁队列
{
	free(q);
}
bool QueueEmpty(SqQueue *q)				//判断队列是否为空
{
	return(q->front==q->rear);
}
bool enQueue(SqQueue *&q,ElemType e)	//进队列
{	if ((q->rear+1)%MaxSize==q->front)	//队满上溢出
		return false;
	q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=e;
	return true;
}
bool deQueue(SqQueue *&q,ElemType &e)	//出队列
{	if (q->front==q->rear)				//队空下溢出
		return false;
	q->front=(q->front+1)%MaxSize;
	e=q->data[q->front];
	return true;
}
//----------------------------------------------------------

void number(int n)
{
	int i;  ElemType e;
	SqQueue *q;					//环形队列指针
	InitQueue(q);				//初始化队列
	for (i=1;i<=n;i++)			//构建初始序列
		enQueue(q,i);
	printf("报数出列顺序:");
	while (!QueueEmpty(q))		//队列不空循环
	{
		deQueue(q,e);			//出队一个元素e
		printf("%d ",e);		//输出元素编号
		if (!QueueEmpty(q))		//队列不空
		{
			deQueue(q,e);		//出队一个元素e
			enQueue(q,e);		//将刚出列的元素进队
		}
	}
	printf("\n");
	DestroyQueue(q);			//销毁队列q
}
int main()
{
	int i,n=8;
	printf("初始序列:");
	for (i=1;i<=n;i++)
		printf("%d ",i);
	printf("\n");
	number(n);
	return 1;
}
