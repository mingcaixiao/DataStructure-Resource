//文件名:exp7-2.cpp
#include "btree.cpp"				//包含二叉树的基本运算算法
void PreOrder(BTNode *b)  			//先序遍历的递归算法
{
	if (b!=NULL)  
	{	
		printf("%c ",b->data);		//访问根结点
		PreOrder(b->lchild);		//递归访问左子树
		PreOrder(b->rchild);		//递归访问右子树
	}
}
void PreOrder1(BTNode *b)			//先序非递归遍历算法
{
	BTNode *St[MaxSize],*p;
    int top=-1;
    if (b!=NULL) 
    {
        top++;						//根结点进栈
        St[top]=b;
        while (top>-1)				//栈不为空时循环
        {
            p=St[top];				//退栈并访问该结点
            top--;
            printf("%c ",p->data);
            if (p->rchild!=NULL)	//有右孩子,将其进栈
			{
               top++;
               St[top]=p->rchild;
			}
            if (p->lchild!=NULL)	//有左孩子,将其进栈
			{
               top++;
               St[top]=p->lchild;
			}
		}
		printf("\n");
	}
}
void InOrder(BTNode *b)   		//中序遍历的递归算法
{
	if (b!=NULL)  
	{	
		InOrder(b->lchild);		//递归访问左子树
		printf("%c ",b->data);	//访问根结点
		InOrder(b->rchild);		//递归访问右子树
	}
}
void InOrder1(BTNode *b)		//中序非递归遍历算法
{
	BTNode *St[MaxSize],*p;
	int top=-1;
	if (b!=NULL)
	{
		p=b;
		while (top>-1 || p!=NULL)	
		{
			while (p!=NULL)		//扫描结点p的所有左下结点并进栈
			{
				top++;
				St[top]=p;
				p=p->lchild;
			}
			if (top>-1)
			{
				p=St[top];		//出栈结点p并访问
				top--;
				printf("%c ",p->data);
				p=p->rchild;
			}
		}
		printf("\n");
	}
}
void PostOrder(BTNode *b) 			//后序遍历的递归算法
{
	if (b!=NULL)  
	{	
		PostOrder(b->lchild);		//递归访问左子树
		PostOrder(b->rchild);		//递归访问右子树
		printf("%c ",b->data);		//访问根结点
	}
}
void PostOrder1(BTNode *b)			//后序非递归遍历算法
{
	BTNode *St[MaxSize];
	BTNode *p;
	int top=-1;								//栈指针置初值
	bool flag;
	if (b!=NULL)
	{
		do
		{
			while (b!=NULL)					//将b结点的所有左下结点进栈
			{
				top++;
				St[top]=b;
				b=b->lchild;
			}
			p=NULL;							//p指向当前结点的前一个已访问的结点
			flag=true;						//flag为真表示正在处理栈顶结点
			while (top!=-1 && flag)
			{
				b=St[top];					//取出当前的栈顶元素
				if (b->rchild==p)			//右子树不存在或已被访问,访问之
				{
					printf("%c ",b->data);	//访问b结点
					top--;
					p=b;					//p指向则被访问的结点
				}
				else
				{
					b=b->rchild;			//b指向右子树
					flag=false;				//表示当前不是处理栈顶结点	
				}
			}
		} while (top!=-1);
		printf("\n");
	} 
}
void TravLevel(BTNode *b)				//层次遍历
{
	BTNode *Qu[MaxSize];				//定义环形队列
	int front,rear;						//定义队首和队尾指针
	front=rear=0;						//置队列为空队
    if (b!=NULL) 
		printf("%c ",b->data);
    rear++;								//根结点进队
	Qu[rear]=b;
    while (rear!=front)					//队列不为空
    {
		front=(front+1)%MaxSize;
		b=Qu[front];					//出队结点b
		if (b->lchild!=NULL)			//输出左孩子,并进队
		{
			printf("%c ",b->lchild->data);
			rear=(rear+1)%MaxSize;
			Qu[rear]=b->lchild;
		}
		if (b->rchild!=NULL)			//输出右孩子,并进队
		{
			printf("%c ",b->rchild->data);
			rear=(rear+1)%MaxSize;
			Qu[rear]=b->rchild;
		}
	} 
	printf("\n");
}
int main()
{
	BTNode *b;
	CreateBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"); 
	printf("二叉树b:");DispBTree(b);printf("\n");
	printf("层次遍历序列:");
	TravLevel(b);
	printf("先序遍历序列:\n");
	printf("    递归算法:");PreOrder(b);printf("\n");
	printf("  非递归算法:");PreOrder1(b);
	printf("中序遍历序列:\n");
	printf("    递归算法:");InOrder(b);printf("\n");
	printf("  非递归算法:");InOrder1(b);
	printf("后序遍历序列:\n");
	printf("    递归算法:");PostOrder(b);printf("\n");
	printf("  非递归算法:");PostOrder1(b);
	DestroyBTree(b);
	return 1;
}
 