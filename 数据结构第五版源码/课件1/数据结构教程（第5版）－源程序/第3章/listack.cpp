//链栈基本运算算法
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct linknode
{	
	ElemType data;				//数据域
	struct linknode *next;		//指针域
} LinkStNode;					//链栈类型
void InitStack(LinkStNode *&s)
{
	s=(LinkStNode *)malloc(sizeof(LinkStNode));
	s->next=NULL;
}
void DestroyStack(LinkStNode *&s)
{
	LinkStNode *p=s->next;
	while (p!=NULL)
	{	
		free(s);
		s=p;
		p=p->next;
	}
	free(s);	//s指向尾结点,释放其空间
}
bool StackEmpty(LinkStNode *s)
{
	return(s->next==NULL);
}
void Push(LinkStNode *&s,ElemType e)
{	LinkStNode *p;
	p=(LinkStNode *)malloc(sizeof(LinkStNode));
	p->data=e;				//新建元素e对应的结点p
	p->next=s->next;		//插入p结点作为开始结点
	s->next=p;
}
bool Pop(LinkStNode *&s,ElemType &e)
{	LinkStNode *p;
	if (s->next==NULL)		//栈空的情况
		return false;
	p=s->next;				//p指向开始结点
	e=p->data;
	s->next=p->next;		//删除p结点
	free(p);				//释放p结点
	return true;
}
bool GetTop(LinkStNode *s,ElemType &e)
{	if (s->next==NULL)		//栈空的情况
		return false;
	e=s->next->data;
	return true;
}
