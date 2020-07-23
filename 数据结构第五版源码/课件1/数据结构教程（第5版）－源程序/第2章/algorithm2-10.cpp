//【例2.10】的算法:双链表递增排序
#include "dlinklist.cpp"
void sort(DLinkNode *&L)	
{	
	DLinkNode *p,*pre,*q;
	p=L->next->next;		//p指向L的第2个数据结点
	L->next->next=NULL;		//构造只含一个数据结点的有序表
	while (p!=NULL)
	{	q=p->next;			//q保存p结点后继结点的指针
		pre=L;				//从有序表开头进行比较,pre指向p结点的前驱结点
		while (pre->next!=NULL && pre->next->data<p->data)
			pre=pre->next;	//在有序表中找插入p结点的前驱结点pre
		p->next=pre->next;	//在pre结点之后插入到p结点
		if (pre->next!=NULL)
			pre->next->prior=p;
		pre->next=p;
		p->prior=pre;
		p=q;				//扫描原双链表余下的结点
	}
}

int main()
{
	ElemType a[]={1,8,0,4,9,7,5,2,3,6};
	DLinkNode *L;
	CreateListR(L,a,10);
	printf("L:");DispList(L);
	printf("排序\n");
	sort(L);
	printf("L:");DispList(L);
	DestroyList(L);
	return 1;
}
