//链队运算算法
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct DataNode
{	
	ElemType data;
	struct DataNode *next;
} DataNode;				//链队数据节点类型定义
typedef struct
{	
	DataNode *front;
	DataNode *rear;
} LinkQuNode;			//链队类型定义
void InitQueue(LinkQuNode *&q)	//初始化队列q
{	
	q=(LinkQuNode *)malloc(sizeof(LinkQuNode));
	q->front=q->rear=NULL;
}
void DestroyQueue(LinkQuNode *&q)	//销毁队列q
{
	DataNode *p=q->front,*r;//p指向队头数据节点
	if (p!=NULL)			//释放数据节点占用空间
	{	r=p->next;
		while (r!=NULL)
		{	free(p);
			p=r;r=p->next;
		}
	}
	free(p);
	free(q);				//释放链队节点占用空间
}
bool QueueEmpty(LinkQuNode *q)	//判断队q是否空
{
	return(q->rear==NULL);
}
void enQueue(LinkQuNode *&q,ElemType e)	//进队
{	DataNode *p;
	p=(DataNode *)malloc(sizeof(DataNode));
	p->data=e;
	p->next=NULL;
	if (q->rear==NULL)		//若链队为空,则新节点是队首节点又是队尾节点
		q->front=q->rear=p;
	else
	{	q->rear->next=p;	//将p节点链到队尾,并将rear指向它
		q->rear=p;
	}
}
bool deQueue(LinkQuNode *&q,ElemType &e)	//出队
{	DataNode *t;
	if (q->rear==NULL)		//队列为空
		return false;
	t=q->front;				//t指向第一个数据节点
	if (q->front==q->rear)  //队列中只有一个节点时
		q->front=q->rear=NULL;
	else					//队列中有多个节点时
		q->front=q->front->next;
	e=t->data;
	free(t);
	return true;
}
