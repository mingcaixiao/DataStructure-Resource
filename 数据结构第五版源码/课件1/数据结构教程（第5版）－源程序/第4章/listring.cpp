//链串基本运算的算法
#include <stdio.h>
#include <malloc.h>
typedef struct snode 
{	
	char data;
	struct snode *next;
} LinkStrNode;
void StrAssign(LinkStrNode *&s,char cstr[])	//字符串常量cstr赋给串s
{
	int i;
	LinkStrNode *r,*p;
	s=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=s;						//r始终指向尾结点
	for (i=0;cstr[i]!='\0';i++) 
	{	p=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		p->data=cstr[i];
		r->next=p;r=p;
	}
	r->next=NULL;
}
void DestroyStr(LinkStrNode *&s)
{	LinkStrNode *pre=s,*p=s->next;	//pre指向结点p的前驱结点
	while (p!=NULL)					//扫描链串s
	{	free(pre);					//释放pre结点
		pre=p;						//pre、p同步后移一个结点
		p=pre->next;
	}
	free(pre);						//循环结束时,p为NULL,pre指向尾结点,释放它
}
void StrCopy(LinkStrNode *&s,LinkStrNode *t)	//串t复制给串s
{
	LinkStrNode *p=t->next,*q,*r;
	s=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=s;						//r始终指向尾结点
	while (p!=NULL)				//将t的所有结点复制到s
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
}
bool StrEqual(LinkStrNode *s,LinkStrNode *t)	//判串相等
{
	LinkStrNode *p=s->next,*q=t->next;
	while (p!=NULL && q!=NULL && p->data==q->data) 
	{	p=p->next;
		q=q->next;
	}
	if (p==NULL && q==NULL)
		return true;
	else
		return false;
}
int StrLength(LinkStrNode *s)	//求串长
{
	int i=0;
	LinkStrNode *p=s->next;
	while (p!=NULL) 
	{	i++;
		p=p->next;
	}
	return i;
}
LinkStrNode *Concat(LinkStrNode *s,LinkStrNode *t)	//串连接
{
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=str;
	while (p!=NULL)				//将s的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	p=t->next;
	while (p!=NULL)				//将t的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}
LinkStrNode *SubStr(LinkStrNode *s,int i,int j)	//求子串
{
	int k;
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;						//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
		return str;				//参数不正确时返回空串
	for (k=0;k<i-1;k++)
		p=p->next;
	for (k=1;k<=j;k++) 			//将s的第i个结点开始的j个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}
LinkStrNode *InsStr(LinkStrNode *s,int i,LinkStrNode *t)		//串插入
{
	int k;
	LinkStrNode *str,*p=s->next,*p1=t->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;								//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s)+1)		//参数不正确时返回空串
		return str;
	for (k=1;k<i;k++)					//将s的前i个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	while (p1!=NULL)					//将t的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p1->data;
		r->next=q;r=q;
		p1=p1->next;
	}
	while (p!=NULL)						//将结点p及其后的结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}
LinkStrNode *DelStr(LinkStrNode *s,int i,int j)	//串删去
{
	int k;
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;						//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
		return str;				//参数不正确时返回空串
	for (k=0;k<i-1;k++)			//将s的前i-1个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	for (k=0;k<j;k++)				//让p沿next跳j个结点
		p=p->next;
	while (p!=NULL)					//将结点p及其后的结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}
LinkStrNode *RepStr(LinkStrNode *s,int i,int j,LinkStrNode *t)	//串替换
{
	int k;
	LinkStrNode *str,*p=s->next,*p1=t->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;							//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
		return str;		 			//参数不正确时返回空串
	for (k=0;k<i-1;k++)  			//将s的前i-1个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;q->next=NULL;
		r->next=q;r=q;
		p=p->next;
	}
	for (k=0;k<j;k++)				//让p沿next跳j个结点
		p=p->next;
	while (p1!=NULL)				//将t的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p1->data;q->next=NULL;
		r->next=q;r=q;
		p1=p1->next;
	}
	while (p!=NULL)					//将结点p及其后的结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;q->next=NULL;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}
void DispStr(LinkStrNode *s)	//输出串
{
	LinkStrNode *p=s->next;
	while (p!=NULL)
	{	printf("%c",p->data);
		p=p->next;
	}
	printf("\n");
}
