//单链表运算算法
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct LNode  		//单链表结点类型
{
	ElemType data;
	struct LNode *next;		//指向后继结点
} LinkNode;
void CreateListF(LinkNode *&L,ElemType a[],int n)
//头插法建立单链表
{
	LinkNode *s;int i;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	for (i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点
		s->data=a[i];
		s->next=L->next;			//将结点s插在原开始结点之前,头结点之后
		L->next=s;
	}
}
void CreateListR(LinkNode *&L,ElemType a[],int n)
//尾插法建立单链表
{
	LinkNode *s,*r;int i;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	r=L;							//r始终指向终端结点,开始时指向头结点
	for (i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点
		s->data=a[i];
		r->next=s;					//将结点s插入结点r之后
		r=s;
	}
	r->next=NULL;					//尾结点next域置为NULL
}
void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
}
void DestroyList(LinkNode *&L)
{
	LinkNode *p=L,*q=p->next;
	while (q!=NULL)
	{	free(p);
		p=q;
		q=p->next;
	}
	free(p);						//此时q为NULL,p指向尾结点,释放它
}
bool ListEmpty(LinkNode *L)
{
	return(L->next==NULL);
}
int ListLength(LinkNode *L)
{
	LinkNode *p=L;int i=0;
	while (p->next!=NULL)
	{	i++;
		p=p->next;
	}
	return(i);
}
void DispList(LinkNode *L)
{
	LinkNode *p=L->next;
	while (p!=NULL)
	{	printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode *L,int i,ElemType &e)
{
	int j=0;
	LinkNode *p=L;
	while (j<i && p!=NULL)
	{	j++;
		p=p->next;
	}
	if (p==NULL)			//不存在第i个数据结点
		return false;
	else					//存在第i个数据结点
	{	e=p->data;
		return true;
	}
}
int LocateElem(LinkNode *L,ElemType e)
{
	LinkNode *p=L->next;
	int n=1;
	while (p!=NULL && p->data!=e)
	{	p=p->next;
		n++;
	}
	if (p==NULL)
		return(0);
	else
		return(n);
}
bool ListInsert(LinkNode *&L,int i,ElemType e)
{
	int j=0;
	LinkNode *p=L,*s;
	while (j<i-1 && p!=NULL)		//查找第i-1个结点p
	{	j++;
		p=p->next;
	}
	if (p==NULL)					//未找到位序为i-1的结点
		return false;
	else							//找到位序为i-1的结点p
	{	s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点s
		s->data=e;
		s->next=p->next;			//将结点s插入到结点p之后
		p->next=s;
		return true;
	}
}
bool ListDelete(LinkNode *&L,int i,ElemType &e)
{
	int j=0;
	LinkNode *p=L,*q;
	while (j<i-1 && p!=NULL)		//查找第i-1个结点
	{	j++;
		p=p->next;
	}
	if (p==NULL)					//未找到位序为i-1的结点
		return false;
	else							//找到位序为i-1的结点p
	{	q=p->next;					//q指向要删除的结点
		if (q==NULL) 
			return false;			//若不存在第i个结点,返回false
		e=q->data;
		p->next=q->next;			//从单链表中删除q结点
		free(q);					//释放q结点
		return true;
	}
}
