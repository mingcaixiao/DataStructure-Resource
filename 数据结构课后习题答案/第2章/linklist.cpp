//单链表运算算法
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct LNode 
{
	ElemType data;
	struct LNode *next;		//指向后继结点
} LinkNode;		 			//单链表结点类型
void CreateListF(LinkNode *&L,ElemType a[],int n)
//头插法建立单链表
{
	LinkNode *s;
	L=(LinkNode *)malloc(sizeof(LinkNode));  //创建头结点
	L->next=NULL;
	for (int i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点s
		s->data=a[i];
		s->next=L->next;			//将结点s插在原开始结点之前,头结点之后
		L->next=s;
	}
}
void CreateListR(LinkNode *&L,ElemType a[],int n)
//尾插法建立单链表
{
	LinkNode *s,*r;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	r=L;						//r始终指向尾结点,开始时指向头结点
	for (int i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点s
		s->data=a[i];
		r->next=s;				//将结点s插入r结点之后
		r=s;
	}
	r->next=NULL;				//尾结点next域置为NULL
}
void InitList(LinkNode *&L)		//初始化线性表
{
	L=(LinkNode *)malloc(sizeof(LinkNode));  //创建头结点
	L->next=NULL;				//单链表置为空表
}
void DestroyList(LinkNode *&L)	//销毁线性表
{
	LinkNode *pre=L,*p=pre->next;
	while (p!=NULL)
	{	free(pre);
		pre=p;					//pre、p同步后移一个结点					
		p=pre->next;
	}
	free(pre);					//此时p为NULL,pre指向尾结点,释放它
}
bool ListEmpty(LinkNode *L)		//判线性表是否为空表
{
	return(L->next==NULL);
}
int ListLength(LinkNode *L)		//求线性表的长度
{	int i=0;
	LinkNode *p=L;				//p指向头结点,n置为0(即头结点的序号为0)
	while (p->next!=NULL)
	{	i++;
		p=p->next;
	}
	return(i);					//循环结束,p指向尾结点,其序号i为结点个数
}

void DispList(LinkNode *L)	//输出线性表
{	LinkNode *p=L->next;	//p指向首结点
	while (p!=NULL)			//p不为NULL,输出p结点的data域
	{	printf("%c ",p->data);
		p=p->next;			//p移向下一个结点
	}
	printf("\n");
}

bool GetElem(LinkNode *L,int i,ElemType &e)	//求线性表中第i个元素值
{	int j=0;
	if (i<=0) return false;		//i错误返回假
	LinkNode *p=L;				//p指向头结点,j置为0(即头结点的序号为0)
	while (j<i && p!=NULL)		//找第i个结点p
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//不存在第i个数据结点,返回false
		return false;
	else						//存在第i个数据结点,返回true
	{	e=p->data;
		return true;
	}
}

int LocateElem(LinkNode *L,ElemType e)	//查找第一个值域为e的元素序号
{	int i=1;
	LinkNode *p=L->next;			//p指向首结点,i置为1(即首结点的序号为1)
	while (p!=NULL && p->data!=e)	//查找data值为e的结点,其序号为i
	{	p=p->next;
		i++;
	}
	if (p==NULL)					//不存在值为e的结点,返回0
		return(0);
	else							//存在值为e的结点,返回其逻辑序号i
		return(i);
}

bool ListInsert(LinkNode *&L,int i,ElemType e)	//插入第i个元素
{	int j=0;
	if (i<=0) return false;		//i错误返回假
	LinkNode *p=L,*s;			//p指向头结点,j置为0(即头结点的序号为0)
	while (j<i-1 && p!=NULL)	//查找第i-1个结点p
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//未找到第i-1个结点,返回false
		return false;
	else						//找到第i-1个结点p,插入新结点并返回true
	{	s=(LinkNode *)malloc(sizeof(LinkNode));
		s->data=e;				//创建新结点s,其data域置为e
		s->next=p->next;		//将结点s插入到结点p之后
		p->next=s;
		return true;
	}
}

bool ListDelete(LinkNode *&L,int i,ElemType &e)	//删除第i个元素
{	int j=0;
	if (i<=0) return false;		//i错误返回假
	LinkNode *p=L,*q;			//p指向头结点,j置为0(即头结点的序号为0)
	while (j<i-1 && p!=NULL)	//查找第i-1个结点
	{	j++;
		p=p->next;
	}
	if (p==NULL)				//未找到第i-1个结点,返回false
		return false;
	else						//找到第i-1个结点p
	{	q=p->next;				//q指向第i个结点
		if (q==NULL)			//若不存在第i个结点,返回false
			return false;
		e=q->data;
		p->next=q->next;		//从单链表中删除q结点
		free(q);				//释放q结点
		return true;			//返回true表示成功删除第i个结点
	}
}
