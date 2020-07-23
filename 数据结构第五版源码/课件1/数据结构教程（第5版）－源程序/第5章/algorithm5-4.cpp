//【例5.4】的算法：释放一个不带头结点的单链表L中所有结点。
#include "linklist.cpp"
void release(LinkNode *&L)
{
	if (L!=NULL)
	{
		release(L->next);
		free(L);
	}
}
int main()
{
	LinkNode *h;
	int a[]={1,2,3,4};
	InitList(h);		//h为带头结点的单链表
	ListInsert(h,1,1);
	ListInsert(h,2,2);
	ListInsert(h,3,3);
	ListInsert(h,4,4);
	printf("单链表:");
	DispList(h);
	printf("释放单链表\n");
	release(h->next);
	free(h);			//释放头结点
	return 1;
}
