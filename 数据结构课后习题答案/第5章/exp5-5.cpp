//文件名:exp5-5.cpp
#include "linklist.cpp"		//包含单链表的基本运算算法
void Reverse(LinkNode *p,LinkNode *&L)  
{  
    if(p->next==NULL)		//以p为首节点指针的单链表只有一个节点时
    {  
        L->next=p;			//p节点变为尾节点
        return;
    }  
    Reverse(p->next,L);		//逆置后的尾节点是p->next  
    p->next->next=p;		//将节点链接在尾节点之后  
    p->next=NULL;			//尾节点next域置为NULL  
}  

int main()
{
	LinkNode *L;
	char a[]="12345678";
	int n=8;
	CreateListR(L,a,n);
	printf("L:"); DispList(L);
	printf("逆置L\n");
	Reverse(L->next,L);
	printf("L:"); DispList(L);
	DestroyList(L);
	return 1;
}
