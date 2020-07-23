//【例3.8】的算法：用只有尾结点指针rear的循环单链表作为链队
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct node
{
	ElemType data;
	struct node *next;
} LinkNode;
void initQueue(LinkNode *&rear)				//初始化队运算算法
{
	rear=NULL;
}
void enQueue(LinkNode *&rear,ElemType e)	//进队运算算法
{	
	LinkNode *p;
	p=(LinkNode *)malloc(sizeof(LinkNode));	//创建新结点
	p->data=e;
	if (rear==NULL)							//原链队为空
	{
		p->next=p;							//构成循环链表
		rear=p;
	}
	else
	{
		p->next=rear->next;					//将p结点插入到rear结点之后
		rear->next=p;
		rear=p;								//让rear指向这个新插入的结点
	}
}
bool deQueue(LinkNode *&rear,ElemType &e)	//出队运算算法
{
	LinkNode *q;
	if (rear==NULL)							//队空
		return false;
	else if (rear->next==rear)				//原队中只有一个结点
	{
		e=rear->data;
		free(rear);
		rear=NULL;
	}
	else									//原队中有两个或以上的结点
	{	
		q=rear->next;
		e=q->data;
		rear->next=q->next;
		free(q);
	}
	return true;
}
bool queueEmpty(LinkNode *rear)				//判队空运算算法
{
	return(rear==NULL);
}

int main()
{
	LinkNode *q;
	ElemType e;
	initQueue(q);
	enQueue(q,1);
	enQueue(q,2);
	enQueue(q,3);
	enQueue(q,4); 
	printf("出队顺序:");
	while (!queueEmpty(q))
	{
		deQueue(q,e);
		printf("%d ",e);
	}
	printf("\n"); 
	return 1;
}
