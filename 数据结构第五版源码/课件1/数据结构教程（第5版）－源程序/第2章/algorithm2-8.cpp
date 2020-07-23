//【例2.8】的算法:单链表L递增排序
#include "linklist.cpp"
void sort(LinkNode *&L)
{	LinkNode *p,*pre,*q;
	p=L->next->next;		//p指向L的第2个数据结点
	L->next->next=NULL;		//构造只含一个数据结点的有序表
	while (p!=NULL)
	{	q=p->next;			//q保存p结点后继结点的指针
		pre=L;				//从有序表开头进行比较,pre指向p结点的前驱结点
		while (pre->next!=NULL && pre->next->data<p->data)
			pre=pre->next;	//在有序表中找插入p结点的前驱结点pre
		p->next=pre->next;	//在pre结点之后插入p结点
		pre->next=p;
		p=q;				//扫描原单链表余下的结点
	}
}
int main()
{
	LinkNode *L;
	int n=10;
	ElemType a[]={1,3,2,9,0,4,7,6,5,8};
	CreateListR(L,a,n);
	printf("L:");DispList(L);
	printf("排序\n");
	sort(L);
	printf("L:");DispList(L);
	DestroyList(L);
	return 1;
}

