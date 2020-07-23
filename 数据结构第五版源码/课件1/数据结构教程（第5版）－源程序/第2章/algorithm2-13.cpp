//【例2.13】的算法:判断循环双链表L中的数据结点是否对称。
#include "cdlinklist.cpp"
bool Symm(DLinkNode *L)
{	bool same=true;			//same表示L是否对称，初始时为真
	DLinkNode *p=L->next;	//p指向首结点
	DLinkNode *q=L->prior;	//q指向尾结点
	while (same)
	{	if (p->data!=q->data) //对应结点值不相同，退出循环
			same=false;
		else
		{	if (p==q || p==q->prior) break;
			q=q->prior;		//q前移一个结点 
			p=p->next;		//p后移一个结点
		}
	} 
	return same;
}

int main()
{
	ElemType a[]={1,2,3,2,1};
	int n=5;
	DLinkNode *L;
	CreateListR(L,a,n);
	printf("L:");DispList(L);
	if (Symm(L))
		printf("L是对称的\n");
	else
		printf("L是不对称的\n");
	DestroyList(L);
	return 1;
}
