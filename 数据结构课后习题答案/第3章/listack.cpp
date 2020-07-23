//链栈运算算法
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct linknode
{	
	ElemType data;				//数据域
	struct linknode *next;		//指针域
} LinkStNode;					//链栈类型定义
void InitStack(LinkStNode *&s)	//初始化链栈
{
	s=(LinkStNode *)malloc(sizeof(LinkStNode));
	s->next=NULL;
}
void DestroyStack(LinkStNode *&s)	//销毁链栈
{
	LinkStNode *p=s->next;
	while (p!=NULL)
	{	
		free(s);
		s=p;
		p=p->next;
	}
	free(s);	//s指向尾节点,释放其空间
}
bool StackEmpty(LinkStNode *s)	//判断栈空否
{
	return(s->next==NULL);
}
void Push(LinkStNode *&s,ElemType e)	//进栈
{	LinkStNode *p;
	p=(LinkStNode *)malloc(sizeof(LinkStNode));
	p->data=e;				//新建元素e对应的节点p
	p->next=s->next;		//插入p节点作为开始节点
	s->next=p;
}
bool Pop(LinkStNode *&s,ElemType &e)	//出栈
{	LinkStNode *p;
	if (s->next==NULL)		//栈空的情况
		return false;
	p=s->next;				//p指向开始节点
	e=p->data;
	s->next=p->next;		//删除p节点
	free(p);				//释放p节点
	return true;
}
bool GetTop(LinkStNode *s,ElemType &e)	//取栈顶元素
{	if (s->next==NULL)		//栈空的情况
		return false;
	e=s->next->data;
	return true;
}
