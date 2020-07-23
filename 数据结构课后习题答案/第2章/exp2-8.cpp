//文件名:exp2-8.cpp
#include "linklist.cpp"
void sort(LinkNode *&L)		//单链表元素递增排序
{
	LinkNode *p,*pre,*q;
	p=L->next->next;		//p指向L的第2个数据结点
	L->next->next=NULL;		//构造只含一个数据结点的有序表
	while (p!=NULL)
	{	q=p->next;			//q保存p结点的后继结点
		pre=L;				//从有序表开头进行比较,pre指向插入结点p的前驱结点
		while (pre->next!=NULL && pre->next->data<p->data)
			pre=pre->next;	//在有序表中找pre结点
		p->next=pre->next;	//将结点pre之后插入p结点
		pre->next=p;
		p=q;				//扫描原单链表余下的结点
	}
}

void Union(LinkNode *ha,LinkNode *hb,LinkNode *&hc)  //求两有序集合的并
{
	LinkNode *pa=ha->next,*pb=hb->next,*s,*tc;
	hc=(LinkNode *)malloc(sizeof(LinkNode));	//创建头结点
	tc=hc;
	while (pa!=NULL && pb!=NULL)
	{
		if (pa->data<pb->data)
		{
			s=(LinkNode *)malloc(sizeof(LinkNode));	//复制结点
			s->data=pa->data;
			tc->next=s;tc=s;
			pa=pa->next;
		}
		else if (pa->data>pb->data)
		{
			s=(LinkNode *)malloc(sizeof(LinkNode));	//复制结点
			s->data=pb->data;
			tc->next=s;tc=s;
			pb=pb->next;
		}
		else
		{
			s=(LinkNode *)malloc(sizeof(LinkNode));	//复制结点
			s->data=pa->data;
			tc->next=s;tc=s;
			pa=pa->next;	//重复的元素只复制一个
			pb=pb->next;
		}
	}
	if (pb!=NULL) pa=pb;	//复制余下的结点
	while (pa!=NULL)
	{
		s=(LinkNode *)malloc(sizeof(LinkNode));	//复制结点
		s->data=pa->data;
		tc->next=s;tc=s;
		pa=pa->next;
	}
	tc->next=NULL;
}
void InterSect(LinkNode *ha,LinkNode *hb,LinkNode *&hc)	//求两有序集合的交
{
   LinkNode *pa=ha->next,*pb,*s,*tc;
   hc=(LinkNode *)malloc(sizeof(LinkNode));
   tc=hc;
   while (pa!=NULL)
   {
	   pb=hb->next;
	   while (pb!=NULL && pb->data<pa->data)  
		   pb=pb->next; 
	   if (pb!=NULL && pb->data==pa->data)			//若pa结点值在B中
	   {
		   s=(LinkNode *)malloc(sizeof(LinkNode));	//复制结点
		   s->data=pa->data;
		   tc->next=s;tc=s;
	   }
	   pa=pa->next;
   }
   tc->next=NULL;
}
void Subs(LinkNode *ha,LinkNode *hb,LinkNode *&hc)	//求两有序集合的差
{
   LinkNode *pa=ha->next,*pb,*s,*tc;
   hc=(LinkNode *)malloc(sizeof(LinkNode));
   tc=hc;
   while (pa!=NULL)
   {
	   pb=hb->next;
	   while (pb!=NULL && pb->data<pa->data)  
		   pb=pb->next; 
	   if (!(pb!=NULL && pb->data==pa->data))		//若pa结点值不在B中
	   {
		   s=(LinkNode *)malloc(sizeof(LinkNode));	//复制结点
		   s->data=pa->data;
		   tc->next=s;tc=s;
	   }
	   pa=pa->next;
   }
   tc->next=NULL;
}
int main()
{
	LinkNode *ha,*hb,*hc;
	ElemType a[]={'c','a','e','h'};
	ElemType b[]={'f','h','b','g','d','a'};
	printf("集合的运算如下:\n");
	CreateListR(ha,a,4);
	CreateListR(hb,b,6);
	printf("  原 集 合A: ");DispList(ha);
	printf("  原 集 合B: ");DispList(hb);
	sort(ha);
	sort(hb);
	printf("  有序集合A: ");DispList(ha);
	printf("  有序集合B: ");DispList(hb);
	Union(ha,hb,hc);
	printf("  集合的并C: ");DispList(hc);
	InterSect(ha,hb,hc);
	printf("  集合的交C: ");DispList(hc);
	Subs(ha,hb,hc);
	printf("  集合的差C: ");DispList(hc);
	DestroyList(ha);
	DestroyList(hb);
	DestroyList(hc);
	return 1;
}

