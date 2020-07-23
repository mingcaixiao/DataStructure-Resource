//【例7.18】的算法：采用层次遍历方法输出从根节点到每个叶子节点的路径逆序列
#include "btree.cpp"
#define MaxSize 100

//----------------------------------------------------------
//-非环形队列的基本运算算法---------------------------------
//----------------------------------------------------------
typedef struct snode
{
	BTNode *pt;						//存放当前节点指针
	int parent;						//存放双亲节点在队列中的位置
} NodeType;							//非环形队列元素类型

typedef struct
{
	NodeType data[MaxSize];			//存放队列元素
	int front,rear;					//队头指针和队尾指针
} QuType;							//顺序队类型


void InitQueue(QuType *&q)			//初始化队列
{	q=(QuType *)malloc (sizeof(QuType));
	q->front=q->rear=-1;
}
void DestroyQueue(QuType *&q)		//销毁队列
{
	free(q);
}
bool QueueEmpty(QuType *q)			//判断队列是否为空
{
	return(q->front==q->rear);
}
bool enQueue(QuType *&q,NodeType e)	//进队列
{	if (q->rear==MaxSize-1)			//队满上溢出
		return false;				//返回假
	q->rear++;						//队尾增1
	q->data[q->rear]=e;				//rear位置插入元素e
	return true;					//返回真
}
bool deQueue(QuType *&q,NodeType &e) //出队列
{	if (q->front==q->rear)			//队空下溢出
		return false;
	q->front++;
	e=q->data[q->front];
	return true;
}
//----------------------------------------------------------
void AllPath2(BTNode *b)
{
	int k;
	BTNode *p;
	NodeType qelem;
	QuType *qu;							//定义非非环形队列指针
	InitQueue(qu);						//初始化队列
	qelem.pt=b; qelem.parent=-1;		//创建根节点对应的队列元素
	enQueue(qu,qelem);					//根节点进队
	while (!QueueEmpty(qu))				//队不空循环
	{
		deQueue(qu,qelem);				//出队元素qelem,它在队中下标为qu->front
		p=qelem.pt;						//取元素qelem的节点p
		if (p->lchild==NULL && p->rchild==NULL)	//节点p为叶子节点
		{
			k=qu->front;				//输出节点p到根节点的路径逆序列
			while (qu->data[k].parent!=-1)
			{
				printf("%c->",qu->data[k].pt->data);
				k=qu->data[k].parent;
			}
			printf("%c\n",qu->data[k].pt->data);
		}
		if (p->lchild!=NULL)			//节点p有左孩子
		{
			qelem.pt=p->lchild;			//创建节点p的左孩子对应的队列元素
			qelem.parent=qu->front;		//节点p的左孩子的双亲位置为qu->front
			enQueue(qu,qelem);			//节点p的左孩子进队
		}
		if (p->rchild!=NULL)			//节点p有右孩子
		{
			qelem.pt=p->rchild;			//创建节点p的右孩子对应的队列元素
			qelem.parent=qu->front;		//节点p的右孩子的双亲位置为qu->front
			enQueue(qu,qelem);			//节点p的右孩子进队
		}
	}
}

int main()
{
	BTNode *b;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTree(b);printf("\n");
	printf("从根节点到每个叶子节点的路径逆序列:\n");
	AllPath2(b);
	DestroyBTree(b);
	return 1;
}