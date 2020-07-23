//【例2.16】的算法：高效删除有序单链表的值重复结点
#include "linklist.cpp"
void dels(LinkNode *&L)
{
	LinkNode *p=L->next,*q;
	while (p->next!=NULL) 
	{
		if (p->data==p->next->data)		//找到重复值的结点
		{
			q=p->next;					//q指向这个重复值的结点
			p->next=q->next;			//删除*q结点
			free(q);
		}
		else							//不是重复结点,p指针下移
			p=p->next;
	}
}
int main()
{
	LinkNode *L;
	ElemType a[]={1,2,2,2,3,3,3,3,3};
	CreateListR(L,a,9);
	printf("L:"); DispList(L);
	dels(L);
	printf("L:"); DispList(L);
	DestroyList(L);
	return 1;
}
