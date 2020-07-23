//文件名:algo7-1.cpp
#include "btree.cpp"   //包含二叉树的基本运算算法
int Nodes(BTNode *b)	//求二叉树b的结点个数
{
	int num1,num2;
    if (b==NULL) 
		return 0;
    else if (b->lchild==NULL && b->rchild==NULL) 
		return 1;
    else
    {
        num1=Nodes(b->lchild);
        num2=Nodes(b->rchild);
        return (num1+num2+1);
	}
}
int LeafNodes(BTNode *b)	//求二叉树b的叶子结点个数
{
	int num1,num2;
    if (b==NULL) 
		return 0;
    else if (b->lchild==NULL && b->rchild==NULL) 
		return 1;
    else
    {
        num1=LeafNodes(b->lchild);
        num2=LeafNodes(b->rchild);
        return (num1+num2);
	}
}
int Level(BTNode *b,ElemType x,int h)	//求二叉树b中结点值为x的结点的层次
{	int l;
	if (b==NULL)
		return(0);
	else if (b->data==x)
		return(h);
	else
	{	l=Level(b->lchild,x,h+1);	//在左子树中查找
		if (l!=0)
			return(l);
		else						//在左子树中未找到,再在右子树中查找
			return(Level(b->rchild,x,h+1));
	}
}

int BTWidth(BTNode *b)					//求二叉树b的宽度
{
	struct 
	{
		int lno;						//结点的层次
		BTNode *p;						//结点指针
	} Qu[MaxSize];						//定义非环形队列
	int front,rear;						//定义队首和队尾指针
	int lnum,max,i,n;
	front=rear=0;						//置队列为空队
    if (b!=NULL) 
	{
		rear++;	
		Qu[rear].p=b;					//根结点进队
		Qu[rear].lno=1;					//根结点的层次为1
		while (rear!=front)				//队不空时循环
		{
			front++;
			b=Qu[front].p;				//出队结点p
			lnum=Qu[front].lno;
			if (b->lchild!=NULL)		//有左孩子，将其进队
			{
				rear++;
				Qu[rear].p=b->lchild;
				Qu[rear].lno=lnum+1;
			}
			if (b->rchild!=NULL)		//有右孩子，将其进队
			{
				rear++;
				Qu[rear].p=b->rchild;
				Qu[rear].lno=lnum+1;
			}
		}
		max=0;lnum=1;i=1;				//max存放宽度
		while (i<=rear)
		{
			n=0;
			while (i<=rear && Qu[i].lno==lnum) //i扫描队列中所有结点
			{
				n++;					//n累计一层中的结点个数
				i++;
			}
			lnum=Qu[i].lno;
			if (n>max) max=n;
		}
		return max;
	}
	else return 0;
}
int main()
{
	ElemType x='K';
	BTNode *b,*p,*lp,*rp;;
	CreateBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("输出二叉树b:");DispBTree(b);printf("\n");
	printf("二叉树b的结点个数:%d\n",Nodes(b));
	printf("二叉树b的叶子结点个数:%d\n",LeafNodes(b));
	printf("二叉树b中值为%c结点的层次:%d\n",x,Level(b,x,1));
	printf("二叉树b的宽度:%d\n",BTWidth(b));
	DestroyBTree(b);
	return 1;
}

