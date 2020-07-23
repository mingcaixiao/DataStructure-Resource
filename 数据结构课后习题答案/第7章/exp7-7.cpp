//文件名:exp7-7.cpp
#include "btree.cpp"			//包含二叉树的基本运算算法
void AllPath1(BTNode *b,ElemType path[],int pathlen)
//采用先序遍历方法输出所有从叶子结点到根结点的逆路径
{
	if (b!=NULL)
	{
		if (b->lchild==NULL && b->rchild==NULL)	//b为叶子结点
		{
			printf("   %c到根结点逆路径: %c->",b->data,b->data);
			for (int i=pathlen-1;i>0;i--)
				printf("%c->",path[i]);
			printf("%c\n",path[0]);
		}
		else
		{
			path[pathlen]=b->data;				//将当前结点放入路径中
			pathlen++;							//路径长度增1
			AllPath1(b->lchild,path,pathlen);	//递归扫描左子树
			AllPath1(b->rchild,path,pathlen);	//递归扫描右子树
		}
	}
}
void LongPath1(BTNode *b,ElemType path[],int pathlen,ElemType longpath[],int &longpathlen)
//采用先序遍历方法输出第一条最长的逆路径
{
	if (b==NULL)
	{
		if (pathlen>longpathlen)	//若当前路径更长,将路径保存在longpath中
		{
			for (int i=pathlen-1;i>=0;i--)
				longpath[i]=path[i];
			longpathlen=pathlen;
		}
	}
	else	
	{
		path[pathlen]=b->data;					//将当前结点放入路径中
		pathlen++;								//路径长度增1
		LongPath1(b->lchild,path,pathlen,longpath,longpathlen);	//递归扫描左子树
		LongPath1(b->rchild,path,pathlen,longpath,longpathlen);	//递归扫描右子树
	}
}
void AllPath2(BTNode *b)	//采用后序非递归遍历方法输出所有从叶子结点到根结点的逆路径
{
	BTNode *st[MaxSize];			//定义一个顺序栈st
	int top=-1;						//栈顶指针初始化
	BTNode *p,*r;
	bool flag;
	p=b;
	do
	{
		while (p!=NULL)				//扫描结点p的所有左下结点并进栈
		{
			top++;
			st[top]=p;				//结点p进栈
			p=p->lchild;			//移动到左孩子
		}
		r=NULL;						//r指向刚刚访问的结点，初始时为空
		flag=true;					//flag为真表示正在处理栈顶结点
		while (top>-1 && flag)		//栈不空且flag为真时循环
		{
			p=st[top];				//取出当前的栈顶结点p
			if (p->rchild==r)		//若结点p的右孩子为空或者为刚刚访问过的结点
			{
				if (p->lchild==NULL && p->rchild==NULL)	//若为叶子结点
				{					//输出栈中所有结点值
					printf("   %c到根结点逆路径：",p->data);
					for (int i=top;i>0;i--)
						printf("%c->",st[i]->data);
					printf("%c\n",st[0]->data);
				}
				top--;				//退栈
				r=p;				//r指向刚访问过的结点
			}
			else
			{	p=p->rchild;		//转向处理其右子树
				flag=false;			//表示当前不是处理栈顶结点
			}
		}
	} while (top>-1);			//栈不空循环
}

void AllPath3(BTNode *b)
//采用层次遍历方法输出所有从叶子结点到根结点的逆路径
{
	struct snode
	{
	   BTNode *node;			//存放当前结点指针
	   int parent;				//存放双亲结点在队列中的位置
	} Qu[MaxSize];				//定义顺序队列
	int front,rear,p;			//定义队头和队尾指针
    front=rear=-1;				//置队列为空队列
	rear++;
    Qu[rear].node=b;			//根结点指针进入队列
	Qu[rear].parent=-1;			//根结点没有双亲结点
    while (front<rear)			//队列不为空
    {
		front++;
		b=Qu[front].node;		//队头出队列
		if (b->lchild==NULL && b->rchild==NULL)	//*b为叶子结点
		{
			printf("   %c到根结点逆路径：",b->data);
			p=front;
			while (Qu[p].parent!=-1)
			{
				printf("%c->",Qu[p].node->data);
				p=Qu[p].parent;
			}
			printf("%c\n",Qu[p].node->data);
		}
		if (b->lchild!=NULL)		//左孩子入队列
		{
			rear++;
			Qu[rear].node=b->lchild;
			Qu[rear].parent=front;
		}
		if (b->rchild!=NULL)		//右孩子入队列
		{
			rear++;
			Qu[rear].node=b->rchild;
			Qu[rear].parent=front;
		}
	} 
}

int main()
{
	BTNode *b;
	ElemType path[MaxSize],longpath[MaxSize];
	int i,longpathlen=0;
	CreateBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))"); 
	printf("二叉树b:");DispBTree(b);printf("\n");
	printf("先序遍历方法:\n");AllPath1(b,path,0);
	LongPath1(b,path,0,longpath,longpathlen);
	printf("   第一条最长逆路径长度:%d\n",longpathlen);
	printf("   第一条最长逆路径:");
	for (i=longpathlen-1;i>=0;i--)
		printf("%c ",longpath[i]);
	printf("\n");
	printf("后序非递归遍历方法:\n");AllPath2(b);
	printf("层次遍历方法:\n");AllPath3(b);
	DestroyBTree(b);
	return 1;
}
