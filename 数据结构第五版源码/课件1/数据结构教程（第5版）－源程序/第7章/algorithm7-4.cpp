//【例7.4】的算法：孩子兄弟链存储结构下树的基本运算算法和求树t的高度
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef struct tnode 
{	char data;						//节点的值
	struct tnode *hp;				//指向兄弟
	struct tnode *vp;				//指向孩子节点
} TSBNode;							//孩子兄弟链存储结构类型

TSBNode *CreateTree(char *str)		//由str建立孩子兄弟链存储结构
{	struct
	{	TSBNode *nodep;				//节点指针
		int num;					//孩子个数
	} St[MaxSize];					//顺序栈
	int top=-1;						//栈顶指针
	int i=0,j; char ch=str[i];
	TSBNode *t=NULL,*p,*q;
	while (ch!='\0')
	{	switch(ch)
		{
		case '(': top++; St[top].nodep=p;
			St[top].num=0;				//当前节点p进栈
			break;
		case ')':top--;	break;			//退栈
		case ',':St[top].num++; break;	//栈顶节点增加一个孩子
		default:
			p=(TSBNode *)malloc(sizeof(TSBNode));
			p->data=ch;					//建立一个节点p存放ch
			p->hp=p->vp=NULL;
			if (t==NULL)				//原为空树
				t=p;
			else						//将其作为栈顶节点的一个孩子
			{	if (St[top].num==0)		//第一个孩子用vp指向它
					St[top].nodep->vp=p;
				else					//其他孩子用栈顶节点的孩子节点的hp指向它
				{	q=St[top].nodep->vp;
					for (j=1;j<St[top].num;j++)
						q=q->hp;	
					q->hp=p;
				}
			}
			break;
		}
		i++;
		ch=str[i];
	}
	return t;
}
void DispTree(TSBNode *t)		//输出孩子兄弟链存储结构
{	TSBNode *p;
	if (t!=NULL)
	{	printf("%c",t->data);
		if (t->vp!=NULL)		//有孩子时输出一个'('
		{	printf("(");
			p=t->vp;			//p指向节点t的第一个孩子
			while (p!=NULL)
			{	DispTree(p);
				p=p->hp;
				if (p!=NULL)
					printf(",");
			}
			printf(")");		//输出一个')'
		}
	}
}
void DestroryTree(TSBNode *&t)	//销毁树t
{	if (t!=NULL)
	{	DestroryTree(t->vp);
		DestroryTree(t->hp);
		free(t);				//释放根节点
	}
}
int TreeHeight2(TSBNode *t)
{	TSBNode *p;
	int h,maxh=0;
	if (t==NULL) return 0;		//空树返回0
	else
	{	p=t->vp;				//指向第1个孩子节点
		while (p!=NULL)			//扫描t的所有子树
		{	h=TreeHeight2(p);	//求出p子树的高度
			if (maxh<h) maxh=h;	//求所有子树的最大高度
			p=p->hp;			//继续处理t的其他子树
		}
		return(maxh+1);			//返回maxh+1
	}
}

int main()
{
	TSBNode *t;
	t=CreateTree("A(B,C(E,F,G),D)");
	printf("t:"); DispTree(t);
	printf("\n树t的高度:%d\n",TreeHeight2(t));
	DestroryTree(t);
	return 1;
}
