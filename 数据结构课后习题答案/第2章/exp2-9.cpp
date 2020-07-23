//文件名:exp2-9.cpp
#include <stdio.h>
#include <malloc.h>
#define MAX 100				//多项式最多项数
typedef struct
{
	double coef;			//系数
	int exp;				//指数
} PolyArray;				//存放多项式的数组类型
typedef struct pnode
{
	double coef;			//系数
	int exp;				//指数
	struct pnode *next;
}  PolyNode;				//声明多项式单链表结点类型
void DispPoly(PolyNode *L)	//输出多项式单链表
{
	bool first=true;		//first为true表示是第一项
	PolyNode *p=L->next;
	while (p!=NULL)
	{
		if (first)
			first=false;
		else if (p->coef>0)
			printf("+");
		if (p->exp==0)
			printf("%g",p->coef);
		else if (p->exp==1)
			printf("%gx",p->coef);
		else
			printf("%gx^%d",p->coef,p->exp);
		p=p->next;
	}
	printf("\n");
}
void DestroyPoly(PolyNode *&L)	//销毁多项式单链表
{
	PolyNode *pre=L,*p=pre->next;
	while (p!=NULL)
	{
		free(pre);
		pre=p;
		p=pre->next;
	}
	free(pre);
}
void CreatePolyR(PolyNode *&L,PolyArray a[],int n) //尾插法建表
{
	PolyNode *s,*r;int i;
	L=(PolyNode *)malloc(sizeof(PolyNode));	//创建头结点
	L->next=NULL;
	r=L;						//r始终指向尾结点,开始时指向头结点
	for (i=0;i<n;i++)
	{
		s=(PolyNode *)malloc(sizeof(PolyNode));//创建新结点
		s->coef=a[i].coef;
		s->exp=a[i].exp;
		r->next=s;				//将结点s插入结点r之后
		r=s;
	}
	r->next=NULL;				//尾结点next域置为NULL
}
void Sort(PolyNode *&L)				//将多项式单链表按指数递减排序
{
	PolyNode *p=L->next,*pre,*q;
	if (p!=NULL)					//L有一个或以上的数据结点
	{
		q=p->next;					//q保存p结点的后继结点
		p->next=NULL;				//构造只含一个数据结点的有序表
		p=q;
		while (p!=NULL)				//扫描原L中余下的数据结点
		{
			q=p->next;				//q保存p结点的后继结点
			pre=L;
			while (pre->next!=NULL && pre->next->exp>p->exp)
				pre=pre->next;     //在有序表中找插入结点p的前驱结点pre
			p->next=pre->next;		//将结点p插入到结点pre之后
			pre->next=p;
			p=q;					//扫描原单链表余下的结点
		}
	}
}
void Add(PolyNode *ha,PolyNode *hb,PolyNode *&hc)  //ha和bh相加得到hc
{
	PolyNode *pa=ha->next,*pb=hb->next,*s,*r;
	double c;
	hc=(PolyNode *)malloc(sizeof(PolyNode)); 
	r=hc;							//r指向尾结点，初始时指向头结点
	while (pa!=NULL && pb!=NULL)	//pa、pb均没有扫描完
	{
		if (pa->exp>pb->exp)		//将指数较大的pa结点复制到hc中
		{
			s=(PolyNode *)malloc(sizeof(PolyNode));   
			s->exp=pa->exp;s->coef=pa->coef;
			r->next=s; r=s;
			pa=pa->next;
		}
		else if (pa->exp<pb->exp)	//将指数较大的pb结点复制到hc中
		{
			s=(PolyNode *)malloc(sizeof(PolyNode));   
			s->exp=pb->exp;s->coef=pb->coef;
			r->next=s; r=s;
			pb=pb->next;
		}
		else						//pa、pb结点的指数相等时
		{
			c=pa->coef+pb->coef;	//求两个结点的系数和c
			if (c!=0)				//若系数和不为0时创建新结点
			{ 
				s=(PolyNode *)malloc(sizeof(PolyNode)); 
				s->exp=pa->exp;s->coef=c;	
				r->next=s; r=s;
			}
			pa=pa->next;			//pa、pb均后移一个结点
			pb=pb->next;
		}
	}
	if (pb!=NULL) pa=pb;			//复制余下的结点
	while (pa!=NULL)
	{
		s=(PolyNode *)malloc(sizeof(PolyNode));
		s->exp=pa->exp;
		s->coef=pa->coef;
		r->next=s; r=s;
		pa=pa->next;
	}
	r->next=NULL;					//尾结点next设置为空
}
int main()
{
	PolyNode *ha,*hb,*hc;
	PolyArray a[]={{1.2,0},{2.5,1},{3.2,3},{-2.5,5}};
	PolyArray b[]={{-1.2,0},{2.5,1},{3.2,3},{2.5,5},{5.4,10}};
	CreatePolyR(ha,a,4);
	CreatePolyR(hb,b,5);
	printf("原多项式A:   ");DispPoly(ha);
	printf("原多项式B:   ");DispPoly(hb);
	Sort(ha);
	Sort(hb);
	printf("有序多项式A: ");DispPoly(ha);
	printf("有序多项式B: ");DispPoly(hb);
	Add(ha,hb,hc);
	printf("多项式相加:  ");DispPoly(hc);
	DestroyPoly(ha);
	DestroyPoly(hb);
	DestroyPoly(hc);
	return 1;
}

