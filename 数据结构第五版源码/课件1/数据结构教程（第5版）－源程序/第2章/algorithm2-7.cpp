//【例2.7】的算法:删除单链表L中最大元素的结点
#include "linklist.cpp"
void delmaxnode(LinkNode *&L)
{
	LinkNode *p=L->next,*pre=L,*maxp=p,*maxpre=pre;
	while (p!=NULL)					//用p扫描整个单链表,pre始终指向其前驱结点
	{
		if (maxp->data<p->data)		//若找到一个更大的结点
		{	maxp=p;					//更改maxp
			maxpre=pre;				//更改maxpre
		}
		pre=p;						//p、pre同步后移一个结点
		p=p->next;
	}
	maxpre->next=maxp->next;		//删除maxp结点
	free(maxp);						//释放maxp结点
}
int main()
{
	LinkNode *L;
	int n=10;
	ElemType a[]={1,3,2,9,0,4,7,6,5,8};
	CreateListR(L,a,n);
	printf("L:");DispList(L);
	printf("删除最大值结点\n");
	delmaxnode(L);
	printf("L:");DispList(L);
	DestroyList(L);
	return 1;
}