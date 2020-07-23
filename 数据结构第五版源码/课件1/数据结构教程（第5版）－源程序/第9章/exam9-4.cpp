//【例9.4】的算法：求二叉排序树中p结点的左子树中的最大结点和右子树中的最小结点。
#include <stdio.h>
#include <malloc.h>
typedef int KeyType;
typedef char InfoType[10];
typedef struct node
{
	KeyType key;              		//关键字项
	InfoType data;             		//其他数据域
	struct node *lchild,*rchild;	//左右孩子指针
} BSTNode;           				//二叉排序树结点类型
bool InsertBST(BSTNode *&p,KeyType k)	//插入算法
{
   	if (p==NULL)						//原树为空, 新插入的记录为根结点
	{
		p=(BSTNode *)malloc(sizeof(BSTNode));
		p->key=k;
		p->lchild=p->rchild=NULL;
		return true;
	}
	else if (k==p->key) 				//树中存在相同关键字的结点,返回0
		return false;
	else if (k<p->key) 
		return InsertBST(p->lchild,k);	//插入到*p的左子树中
	else  
		return InsertBST(p->rchild,k);  //插入到*p的右子树中
}
BSTNode *CreateBST(KeyType A[],int n)	//创建二叉排序树，返回其根结点指针
{
	BSTNode *bt=NULL;         			//初始时bt为空树
	int i=0;
	while (i<n) 
	{
		InsertBST(bt,A[i]);  			//将关键字A[i]插入二叉排序树T中
		i++;
    }
    return bt;               			//返回建立的二叉排序树的根指针
}
void DispBST(BSTNode *bt)				//输出一棵排序二叉树
{
	if (bt!=NULL)
	{	printf("%d",bt->key);
		if (bt->lchild!=NULL || bt->rchild!=NULL)
		{	printf("(");						//有孩子结点时才输出(
			DispBST(bt->lchild);				//递归处理左子树
			if (bt->rchild!=NULL) printf(",");	//有右孩子结点时才输出,
			DispBST(bt->rchild);				//递归处理右子树
			printf(")");						//有孩子结点时才输出)
		}
	}
}
KeyType maxnode(BSTNode *p) //返回一棵二叉排序树中的最大结点
{
	while (p->rchild!=NULL)
		p=p->rchild;
	return(p->key);
}
KeyType minnode(BSTNode *p)	  //返回一棵二叉排序树中的最小结点
{
	while (p->lchild!=NULL)
		p=p->lchild;
	return(p->key);
}
void maxminnode(BSTNode *p)
{
	if (p!=NULL)
	{	
		if (p->lchild!=NULL)
			printf("%d结点的左子树中最大结点为:%d\n",p->key,maxnode(p->lchild));
		if (p->rchild!=NULL)
			printf("%d结点的右子树中最小结点为:%d\n",p->key,minnode(p->rchild));
	}
}
int main()
{
	BSTNode *bt;
	int n=12,x=46;
	KeyType a[]={25,18,46,2,53,39,32,4,74,67,60,11};
	bt=CreateBST(a,n);
	printf("BST:");DispBST(bt);printf("\n");
	maxminnode(bt);
	return 1;
}