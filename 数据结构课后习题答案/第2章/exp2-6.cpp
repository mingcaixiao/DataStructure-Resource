//文件名:exp2-6.cpp
#include "linklist.cpp"				//包含单链表的基本运算算法
void Split(LinkNode *&L,ElemType x)	//将L中所有数据结点按x进行划分
{
	LinkNode *p=L->next,*q,*r;
	L->next=NULL;				//L变为空链表
	r=L;
	while (p!=NULL)
	{
		if (p->data<x)			//若p结点值小于x，将其插入在开头
		{
			q=p->next;
			p->next=L->next;
			L->next=p;
			if (p->next==NULL)	//若p结点是第一个在开头插入的结点
				r=p;			//则它是尾结点
			p=q;
		}
		else					//若p结点值大于或等于x，将其插入到末尾
		{
			r->next=p;
			r=p;
			p=p->next;
		}
	}
	r->next=NULL;
}
int main()
{
	LinkNode *L;
	ElemType a[]="abcdefgh";
	int n=8;
	CreateListR(L,a,n);
	printf("L:"); DispList(L);
	ElemType x='d';
	printf("以%c进行划分\n",x);
	Split(L,x);
	printf("L:"); DispList(L);
	DestroyList(L);
	return 1;
}
