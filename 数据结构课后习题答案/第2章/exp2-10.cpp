//文件名:exp2-8.cpp
#include <stdio.h>
#include <malloc.h>
#define MAX 20
typedef struct node
{  
	double coef;		//系数
	int exp;			//指数
	struct node *next;
} PolyNode;				//声明多项式单链表结点类型
void CreatePolyR(PolyNode *&L,double a[],int b[],int n) //尾插法创建多项式单链表
{
	PolyNode *s,*r;int i;
	L=(PolyNode *)malloc(sizeof(PolyNode));
	L->next=NULL;
	r=L;						//r始终指向终端结点,开始时指向头结点
	for (i=0;i<n;i++)
	{
		s=(PolyNode *)malloc(sizeof(PolyNode));         
		s->coef=a[i];
		s->exp=b[i];
		r->next=s;				//将结点s插入结点r之后
		r=s;
	}
	r->next=NULL;				//尾结点next域置为NULL
}
void DestroyPoly(PolyNode *&L)	//销毁单链表
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
void Mult1(PolyNode *ha,PolyNode *hb,PolyNode *&hc)	 //ha和bh简单相乘得到hc
{
	PolyNode *pa=ha->next,*pb,*s,*tc;
	hc=(PolyNode *)malloc(sizeof(PolyNode)); 
	tc=hc;
	while (pa!=NULL)
	{
		pb=hb->next;
		while (pb!=NULL)
		{
			s=(PolyNode *)malloc(sizeof(PolyNode));
			s->coef=pa->coef*pb->coef;
			s->exp=pa->exp+pb->exp;
			tc->next=s;
			tc=s;
			pb=pb->next;
		}
		pa=pa->next;
	}
	tc->next=NULL;
}
void Comb(PolyNode *&L)		//合并指数相同的项
{
	PolyNode *pre=L->next,*p;
	if (pre==NULL) return;
	p=pre->next;
	while (p!=NULL)
	{
		while (p->exp==pre->exp)
		{
			pre->coef+=p->coef;
			pre->next=p->next;
			free(p);
			p=pre->next;
		}
		pre=p;
		p=p->next;
	}
}
void DelZero(PolyNode *&L)		//删除系数为0的项
{
	PolyNode *pre=L,*p=pre->next;
	while (p!=NULL)
	{
		if (p->coef==0.0)
		{
			pre->next=p->next;
			free(p);
		}
		pre=p;
		p=p->next;
	}
}
void Mult(PolyNode *ha,PolyNode *hb,PolyNode *&hc)	//ha和bh相乘得到最终的hc
{
	Mult1(ha,hb,hc);
	printf("相乘结果:      ");DispPoly(hc);
	Sort(hc);
	printf("按指数排序后:  ");DispPoly(hc);
	Comb(hc);
	printf("合并重复指数项:");DispPoly(hc);
	DelZero(hc);
	printf("删除序数为0项: ");DispPoly(hc);
}
int main()
{
	PolyNode *Poly1,*Poly2,*Poly3;
	double a[MAX];
	int b[MAX],n;
	//----创建第1个多项单链表并排序-----
	a[0]=2;b[0]=3;	a[1]=1;b[1]=0;	a[2]=3;b[2]=1;
	n=3;
	printf("第1个多项式:\n");
	CreatePolyR(Poly1,a,b,n);
	printf("  排序前多项式1:");DispPoly(Poly1);
	Sort(Poly1);
	printf("  排序后多项式1:");DispPoly(Poly1);
	//----创建第2个多项单链表并排序-----
	printf("第2个多项式:\n");
	a[0]=2; b[0]=3;	a[1]=-3;b[1]=2;	
	a[2]=5; b[2]=4;	a[3]=-3;b[3]=0;
	n=4;
	CreatePolyR(Poly2,a,b,n);
	printf("  排序前多项式2:");DispPoly(Poly2);
	Sort(Poly2);
	printf("  排序后多项式2:");DispPoly(Poly2);
	Mult(Poly1,Poly2,Poly3);
	printf("相乘后多项式3: ");DispPoly(Poly3);
	DestroyPoly(Poly1);
	DestroyPoly(Poly2);
	DestroyPoly(Poly3);
	return 1;
}
