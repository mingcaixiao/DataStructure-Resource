//【例2.9】的算法:双链表所有结点逆置
#include "dlinklist.cpp"
void reverse(DLinkNode *&L)		//双链表结点逆置
{
	DLinkNode *p=L->next,*q;	//p指向开好结点
	L->next=NULL;				//构造只有头结点的双链表L
	while (p!=NULL)				//扫描L的数据结点
	{	q=p->next;				//因头插法会修改p结点的next域,用q保存其后继结点
		p->next=L->next;		//采用头插法将p结点插入到双链表中
		if (L->next!=NULL)		//若L中存在数据结点,修改其前驱指针
			L->next->prior=p;
		L->next=p;
		p->prior=L;
		p=q;					//让p重新指向其后继结点
	}
}
int main()
{
	ElemType a[]={1,8,0,4,9,7,5,2,3,6};
	DLinkNode *L;
	CreateListR(L,a,10);
	printf("L:");DispList(L);
	printf("逆置\n");
	reverse(L);
	printf("L:");DispList(L);
	DestroyList(L);
	return 1;
}
