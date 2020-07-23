//循环单链表运算算法
#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct LNode		//定义单链表结点类型
{
	ElemType data;
    struct LNode *next;
} LinkNode;
void CreateListF(LinkNode *&L,ElemType a[],int n) //头插法建立循环单链表
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
	s=L->next;	
	while (s->next!=NULL)			//查找尾结点,由s指向它
		s=s->next;
	s->next=L;						//尾结点next域指向头结点

}
void CreateListR(LinkNode *&L,ElemType a[],int n) //尾插法建立循环单链表
{
	LinkNode *s,*r;int i;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	r=L;					//r始终指向终端结点,开始时指向头结点
	for (i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点
		s->data=a[i];
		r->next=s;			//将结点s插入结点r之后
		r=s;
	}
	r->next=L;				//尾结点next域指向头结点
}
void InitList(LinkNode *&L)	//初始化线性表
{
	L=(LinkNode *)malloc(sizeof(LinkNode));	//创建头结点
	L->next=L;
}
void DestroyList(LinkNode *&L)	//销毁线性表
{
	LinkNode *pre=L,*p=pre->next;
	while (p!=L)
	{
		free(pre);
		pre=p;					//pre、p同步后移一个结点
		p=pre->next;
	}
	free(pre);					//此时p=L,pre指向尾结点,释放它
}
bool ListEmpty(LinkNode *L)		//判线性表是否为空表
{
	return(L->next==L);
}
int ListLength(LinkNode *L)		//求线性表的长度
{
	LinkNode *p=L;int i=0;		//p指向头结点,n置为0(即头结点的序号为0)
	while (p->next!=L)
	{
		i++;
		p=p->next;
	}
	return(i);					//循环结束,p指向尾结点,其序号n为结点个数
}
void DispList(LinkNode *L)		//输出线性表
{
	LinkNode *p=L->next;
	while (p!=L)				//p不为L,输出p结点的data域
	{
		printf("%c ",p->data);
		p=p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode *L,int i,ElemType &e)	//求线性表中第i个元素值
{	int j=1;
	LinkNode *p=L->next;
	if (i<=0 || L->next==L)		//i错误或者空表返回假
		return false;
	if (i==1)					//求第1个结点值，作为特殊情况处理
	{
		e=L->next->data;
		return true;
	}
	else						//i不为1时
	{
		while (j<=i-1 && p!=L)	//找第i个结点p
		{
			j++;
			p=p->next;
		}
		if (p==L)				//没有找到返回假
			return false;
		else					//找到了提取它的值并返回整
		{				
			e=p->data;
			return true;
		}
	}
}

int LocateElem(LinkNode *L,ElemType e)  //查找第一个值域为e的元素序号
{
	LinkNode *p=L->next;
	int i=1;
	while (p!=L && p->data!=e)	//查找第一个值域为e的结点p
	{
		p=p->next;
		i++;					//i对应结点p的序号
	}
	if (p==L)
		return(0);				//没有找到返回0
	else
		return(i);				//找到了返回其序号
}
bool ListInsert(LinkNode *&L,int i,ElemType e)	//插入第i个元素
{
	int j=1;
	LinkNode *p=L,*s;
	if (i<=0) return false;		//i错误返回假
	if (p->next==L || i==1)		//原单链表为空表或i=1作为特殊情况处理
	{
		s=(LinkNode *)malloc(sizeof(LinkNode));	//创建新结点s
		s->data=e;								
		s->next=p->next;		//将结点s插入到结点p之后
		p->next=s;
		return true;
	}
	else
	{
		p=L->next;
		while (j<=i-2 && p!=L)	//找第i-1个结点p
		{
			j++;
			p=p->next;
		}
		if (p==L)				//未找到第i-1个结点
			return false;
		else					//找到第i-1个结点p
		{
			s=(LinkNode *)malloc(sizeof(LinkNode));	//创建新结点s
			s->data=e;								
			s->next=p->next;						//将结点s插入到结点p之后
			p->next=s;
			return true;
		}
	}
}
bool ListDelete(LinkNode *&L,int i,ElemType &e)	//删除第i个元素
{
	int j=1;
	LinkNode *p=L,*q;
	if (i<=0 || L->next==L) 
		return false;			//i错误或者空表返回假
	if (i==1)					//i=1作为特殊情况处理
	{
		q=L->next;				//删除第1个结点
		e=q->data;
		L->next=q->next;
		free(q);
		return true;
	}
	else						//i不为1时
	{
		p=L->next;
		while (j<=i-2 && p!=L)	//找第i-1个结点p
		{
			j++;
			p=p->next;
		}
		if (p==L)				//未找到第i-1个结点
			return false;
		else					//找到第i-1个结点p
		{
			q=p->next;			//q指向要删除的结点
			e=q->data;
			p->next=q->next;	//从单链表中删除q结点
			free(q);			//释放q结点
			return true;
		}
	}
}
