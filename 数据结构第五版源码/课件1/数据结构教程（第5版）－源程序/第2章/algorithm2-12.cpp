//【例2.12】的算法:在循环双链表L中删除第一个值为x的结点。
#include "cdlinklist.cpp"
bool delelem(DLinkNode *&L,ElemType x)
{
	DLinkNode *p=L->next; 
	while (p!=L && p->data!=x)
		p=p->next;
	if (p!=L)						//找到第一个元素值为x的结点
	{
		p->next->prior=p->prior;	//删除结点*p
		p->prior->next=p->next;
		free(p);
		return true;
	}
	else 
		return false;
}
int main()
{
	ElemType a[]={1,2,2,4,2,3,5,2,1,4};
	ElemType x=1;
	DLinkNode *L;
	CreateListR(L,a,10);
	printf("L:");DispList(L);
	printf("删除第一个结点值为%d的结点\n",x);
	if (delelem(L,x))
	{
		printf("L:");DispList(L);
	}
	else
		printf("循环双链表L中不存在元素值为%d的结点\n",x);
	DestroyList(L);
	return 1;
}
