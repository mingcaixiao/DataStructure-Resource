//文件名:exp7-8.cpp
#include "btree.cpp"   //包含二叉树的基本运算算法
#include <stdlib.h>
#include <string.h>
typedef char ElemType;
BTNode *CRTree(char s[],int i,int j) //建立简单算术表达式s[i..j]对应的二叉树
{
	BTNode *p;
	int k,plus=0,posi;			//plus记录运算符的个数
	if (i==j)					//处理i=j的情况，说明只有一个字符
	{
		p=(BTNode *)malloc(sizeof(BTNode));
		p->data=s[i];
		p->lchild=NULL;
		p->rchild=NULL;
		return p;
	}
	//以下为i!=j的情况
	for (k=i;k<=j;k++)			//首先查找+和-运算符
		if (s[k]=='+' || s[k]=='-')
		{
			plus++;				//plus记录+或者-的个数
			posi=k;             //posi记录最后一个+或-的位置
		}
	if (plus==0)                //没有+或-的情况
		for (k=i;k<=j;k++)
			if (s[k]=='*' || s[k]=='/')
			{
				plus++;			//plus记录*或者/的个数
				posi=k;			//posi记录最后一个*或/的位置
			}
   if (plus!=0)					//有运算符的情况,创建一个存放它的结点
   {
		p=(BTNode *)malloc(sizeof(BTNode));
		p->data=s[posi];
		p->lchild=CRTree(s,i,posi-1);	//递归处理s[i..posi-1]构造左子树
		p->rchild=CRTree(s,posi+1,j);	//递归处理s[posi+1..j]构造右子树
		return p;
	}
   else       //若没有任何运算符，返回NULL
	   return NULL;
}
double Comp(BTNode *b)	//计算二叉树对应表达式的值
{
	double v1,v2;
	if (b==NULL) return 0;
	if (b->lchild==NULL && b->rchild==NULL)
		return b->data-'0';		//叶子结点直接返回结点值
	v1=Comp(b->lchild);			//递归求出左子树的值v1
	v2=Comp(b->rchild);			//递归求出右子树的值v2
	switch(b->data)				//根据b结点做相应运算
	{
	case '+':
		return v1+v2;
	case '-':
		return v1-v2;
	case '*':
		return v1*v2;
	case '/':
		if (v2!=0)
			return v1/v2;
		else
			abort();		//除0异常退出

	}
}
int main()
{
	BTNode *b;
	char s[MaxSize]="1+2*3-4/5";
    printf("算术表达式%s\n",s);
	b=CRTree(s,0,strlen(s)-1);
	printf("对应二叉树:");
	DispBTree(b);
	printf("\n算术表达式的值:%g\n",Comp(b));
	DestroyBTree(b);
	return 1;
}
