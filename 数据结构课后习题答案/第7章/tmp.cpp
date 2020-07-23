//文件名:algo7-1.cpp
#include "btree.cpp"   //包含二叉树的基本运算算法
void levelnodes(BTNode *b,int h,int a[])
{
	if (b==NULL)
		return;
	else
	{
		a[h]++;
		levelnodes(b->lchild,h+1,a);
		levelnodes(b->lchild,h+1,a);
	}
}
int BTWidth1(BTNode *b)
{
	int width=0,i;
	int a[MaxSize];
	for (i=1;i<MaxSize;i++)
		a[i]=0;				//a设置所有元素初始化为0
	levelnodes(b,1,a);
	i=1;
	while (a[i]!=0)			//求a中最大元素即宽度
	{
		if (a[i]>width)
			width=a[i];
		i++;
	}
	return width;
}

int BTWidth2(BTNode *b)					//求二叉树b的宽度
{
	struct 
	{
		int lno;						//结点的层次
		BTNode *p;						//结点指针
	} Qu[MaxSize];						//定义非环形队列
	int front,rear;						//定义队头和队尾指针
	int lnum,width,i,n;
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
		width=0;lnum=1;i=1;				//width存放宽度
		while (i<=rear)
		{
			n=0;
			while (i<=rear && Qu[i].lno==lnum) //i扫描队列中所有结点
			{
				n++;					//n累计一层中的结点个数
				i++;
			}
			lnum=Qu[i].lno;
			if (n>width) width=n;
		}
		return width;
	}
	else return 0;
}
int main()
{
	ElemType x='K';
	BTNode *b,*p,*lp,*rp;;
	CreateBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("输出二叉树b:");DispBTree(b);printf("\n");
	printf("二叉树b的宽度:%d\n",BTWidth2(b));
	DestroyBTree(b);
	return 1;
}

