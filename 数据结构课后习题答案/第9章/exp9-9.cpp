//文件名:exp9-9.cpp
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAXWORD 100
typedef struct tnode 
{
	char ch;      //字符
	int count;    //出现次数
	struct tnode *lchild,*rchild;
} BSTNode;
void CreateBST(BSTNode *&bt,char c) //采用递归方式构造一棵二叉排序树bt
{
	if (bt==NULL)				//bt为NULL,则建立一个新节点
	{
		bt=(BSTNode *)malloc(sizeof(BSTNode));
		bt->ch=c;
		bt->count=1;
		bt->lchild=bt->rchild=NULL;
	}
	else if (c==bt->ch) 
		bt->count++;
	else if (c<bt->ch) 
		CreateBST(bt->lchild,c);
	else 
		CreateBST(bt->rchild,c);
}
void InOrder(BSTNode *bt)		//中序遍历二叉排序树bt
{
	if (bt!=NULL) 
	{
		InOrder(bt->lchild);	//中序遍历左子树
		printf("  %c(%d)\n",bt->ch,bt->count);//访问根节点
		InOrder(bt->rchild);	//中序遍历右子树
	}
}
void DestroyBST(BSTNode *bt)	//销毁二叉排序树bt
{
	if (bt!=NULL)
	{
		DestroyBST(bt->lchild);
		DestroyBST(bt->rchild);
		free(bt);
	}
}
int main()
{
	BSTNode *bt=NULL;
	int i=0;
	char str[MAXWORD];
	printf("输入字符串:");
	gets(str);
	while (str[i]!='\0') 
	{
		CreateBST(bt,str[i]);
		i++;
	}
	printf("字符及出现次数:\n");
	InOrder(bt);
	DestroyBST(bt);
	return 1;
}
