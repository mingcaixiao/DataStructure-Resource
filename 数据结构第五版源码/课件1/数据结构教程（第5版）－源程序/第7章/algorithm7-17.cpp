//【例7.17】的算法：采用后序遍历非递归算法输出从根节点到每个叶子节点的路径逆序列
#include "btree.cpp"

typedef struct 
{	BTNode *data[MaxSize];			//存放栈中的数据元素
	int top;						//存放栈顶指针，即栈顶元素在data数组中的下标
} SqStack;							//顺序栈类型

void InitStack(SqStack *&s)			//初始化栈
{	s=(SqStack *)malloc(sizeof(SqStack));//分配一个是顺序栈空间，首地址存放在s中
	s->top=-1;						//栈顶指针置为-1
}
void DestroyStack(SqStack *&s)		//销毁栈
{
	free(s);
}
bool StackEmpty(SqStack *s)			//判断栈是否为空
{
	return(s->top==-1);
}
bool Push(SqStack *&s,BTNode *e)	//进栈
{	if (s->top==MaxSize-1)			//栈满的情况，即栈上溢出
		return false;
	s->top++;						//栈顶指针增1
	s->data[s->top]=e;				//元素e放在栈顶指针处
	return true;
}
bool Pop(SqStack *&s,BTNode *&e)	//出栈
{	if (s->top==-1)					//栈为空的情况，即栈下溢出
		return false;
	e=s->data[s->top];				//取栈顶指针元素的元素
	s->top--;						//栈顶指针减1
	return true;
}
bool GetTop(SqStack *s,BTNode *&e)	//取栈顶元素
{	if (s->top==-1)					//栈为空的情况，即栈下溢出
		return false;
	e=s->data[s->top];				//取栈顶元素
	return true;
}
void AllPath1(BTNode *b)
{	BTNode *p,*r;
	bool flag;
	SqStack *st;					//定义一个顺序栈指针st
	InitStack(st);					//初始化栈st
	p=b;
	do
	{	while (p!=NULL)				//扫描节点p的所有左下节点并进栈
		{	Push(st,p);				//节点p进栈
			p=p->lchild;			//移动到左孩子
		}
		r=NULL;						//r指向刚刚访问的节点，初始时为空
		flag=true;					//flag为真表示正在处理栈顶节点
		while (!StackEmpty(st) && flag)
		{	GetTop(st,p);			//取出当前的栈顶节点p
			if (p->rchild==r)		//若节点p的右孩子为空或者为刚刚访问过的节点
			{	if (p->lchild==NULL && p->rchild==NULL)	//若为叶子节点
				{					//输出栈中所有节点值
					for (int i=st->top;i>0;i--)
						printf("%c->",st->data[i]->data);
					printf("%c\n",st->data[0]->data);
				}
				Pop(st,p);
				r=p;				//r指向刚访问过的节点
			}
			else
			{	p=p->rchild;		//转向处理其右子树
				flag=false;			//表示当前不是处理栈顶节点
			}
		}
	} while (!StackEmpty(st));		//栈不空循环
}

int main()
{
	BTNode *b;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTree(b);printf("\n");
	printf("输出所有从叶子节点到根节点的序列:\n");
	AllPath1(b);
	DestroyBTree(b);
	return 1;
}
