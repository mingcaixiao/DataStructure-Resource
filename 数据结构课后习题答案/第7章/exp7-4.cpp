//文件名:exp7-4.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node
{	ElemType data;
	int ltag,rtag;			//增加的线索标记
	struct node *lchild;	//左孩子指针
	struct node *rchild;	//右孩子指针
} TBTNode;
void CreateTBTree(TBTNode * &b,char *str)	//由str串建立含空线索域的二叉链b
{	TBTNode *St[MaxSize],*p=NULL;
	int top=-1,k,j=0;  
	char ch;
	b=NULL;				//建立的二叉树初始时为空
	ch=str[j];
	while (ch!='\0')	//str未扫描完时循环
	{	switch(ch) 
		{
		case '(':top++;St[top]=p;k=1; break;		//为左结点
		case ')':top--;break;
		case ',':k=2; break;					//为右结点
		default:p=(TBTNode *)malloc(sizeof(TBTNode));
				p->data=ch;p->lchild=p->rchild=NULL;
				if (b==NULL)					//p为二叉树的根结点
					b=p;
				else							//已建立二叉树根结点
				{	switch(k) 
					{
					case 1:St[top]->lchild=p;break;
					case 2:St[top]->rchild=p;break;
					}
				}
		}
		j++;
		ch=str[j];
	}
}
void DispTBTree(TBTNode *b)			//输出含空线索域的二叉树b
{	if (b!=NULL)
	{	printf("%c",b->data);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{	printf("(");
			DispTBTree(b->lchild);
			if (b->rchild!=NULL) printf(",");
			DispTBTree(b->rchild);
			printf(")");
		}
	}
}
TBTNode *pre;						//全局变量
void Thread(TBTNode *&p)			//中序线索化二叉树，被CreateThread调用
{	if (p!=NULL)
	{	Thread(p->lchild);			//左子树线索化
		if (p->lchild==NULL)		//若p结点的左指针为空
		{	p->lchild=pre;			//建立当前结点的前驱线索
			p->ltag=1;
		}
		else p->ltag=0;
		if (pre->rchild==NULL)		//若p结点的右指针为空
		{	pre->rchild=p;			//建立前驱结点的后继线索
			pre->rtag=1;
		}
		else pre->rtag=0;
		pre=p;
		Thread(p->rchild);			//右子树线索化
	}
}
TBTNode *CreateThread(TBTNode *b)	//创建中序线索化二叉树
{	TBTNode *root;
	root=(TBTNode *)malloc(sizeof(TBTNode));	//创建根结点
	root->ltag=0;root->rtag=1;
	root->rchild=b;
	if (b==NULL)				//空二叉树
		root->lchild=root;
	else
	{	root->lchild=b;
		pre=root;				//pre结点是p结点的前驱结点,供加线索用
		Thread(b);				//中序遍历线索二叉树
		pre->rchild=root;		//最后处理,加入指向根结点的线索
		pre->rtag=1;
		root->rchild=pre;		//根结点右线索化
	}
	return root;
}
void InOrder(TBTNode *tb)			//被ThInOrder算法调用
{
	if (tb->lchild!=NULL && tb->ltag==0)	//有左孩子
		InOrder(tb->lchild);
	printf("%c ",tb->data);
	if (tb->rchild!=NULL && tb->rtag==0)	//有右孩子
		InOrder(tb->rchild);
}
void ThInOrder(TBTNode *tb)		//中序线索二叉树的中序遍历递归算法
{
	InOrder(tb->lchild);
}
void ThInOrder1(TBTNode *tb)	//中序线索二叉树的中序非递归算法
{	TBTNode *p=tb->lchild;		//指向根结点
	while (p!=tb)
	{	while (p->ltag==0) p=p->lchild;		//找中序开始结点
		printf("%c ",p->data);
		while (p->rtag==1 && p->rchild!=tb)	//有右线索的情况
		{	p=p->rchild;
			printf("%c ",p->data);
		}
		p=p->rchild;						//转向结点p的右子树
	}
}
void DestroyTBTree1(TBTNode *tb)	//被DestroyTBTree算法调用
{
	if (tb!=NULL)
	{
		if (tb->lchild!=NULL && tb->ltag==0)  //有左孩子  
			DestroyTBTree1(tb->lchild);
		if (tb->rchild!=NULL && tb->rtag==0)  //有右孩子  
			DestroyTBTree1(tb->rchild);
		free(tb);
	}
}
void DestroyTBTree(TBTNode *tb)	//释放中序线索二叉树的所有结点
{
	DestroyTBTree1(tb->lchild);
	free(tb);
}
int main()
{	TBTNode *b,*tb;
	CreateTBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"); 	
	printf("二叉树:");DispTBTree(b);printf("\n");
	tb=CreateThread(b);
	printf("线索中序序列:\n");
	printf("    递归算法:");ThInOrder(tb);printf("\n");
	printf("  非递归算法:");ThInOrder1(tb);printf("\n");
	DestroyTBTree(tb);
	return 1;
}
