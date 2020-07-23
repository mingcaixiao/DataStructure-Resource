//【例2.11】的算法:统计循环单链表L中值为x的结点个数。
#include "clinklist.cpp"
int count(LinkNode *L,ElemType x)
{
	int n=0;
	LinkNode *p=L->next;	//指向第1个数据结点
	while (p!=L)
	{	
		if (p->data==x) n++;
		p=p->next;
	}
	return(n);
}
int main()
{
	ElemType a[]={1,2,2,4,2,3,5,2,1,4};
	ElemType x=2;
	LinkNode *L;
	CreateListR(L,a,10);
	printf("L:");DispList(L);
	printf("结点值为%d的结点个数:%d\n",x,count(L,x));
	DestroyList(L);
	return 1;
}
