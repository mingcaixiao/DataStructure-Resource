//文件名:bst.cpp
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef int KeyType;					//定义关键字类型
typedef char InfoType;
typedef struct node               		//记录类型
{	
	KeyType key;                  		//关键字项
    InfoType data;               		//其他数据域
    struct node *lchild,*rchild;		//左右孩子指针
} BSTNode;
void DispBST(BSTNode *b);				//函数说明
bool InsertBST(BSTNode *&bt,KeyType k)	//在以bt为根节点的BST中插入一个关键字为k的节点
{
   	if (bt==NULL)						//原树为空, 新插入的记录为根节点
	{
		bt=(BSTNode *)malloc(sizeof(BSTNode));
		bt->key=k;
		bt->lchild=bt->rchild=NULL;
		return true;
	}
	else if (k==bt->key) 
		return false;
	else if (k<bt->key) 
		return InsertBST(bt->lchild,k);	//插入到bt节点的左子树中
	else  
		return InsertBST(bt->rchild,k);  //插入到bt节点的右子树中
}
BSTNode *CreateBST(KeyType A[],int n)				
//由数组A中的关键字建立一棵二叉排序树
{
  	BSTNode *bt=NULL;         			//初始时bt为空树
   	int i=0;
   	while (i<n) 
		if (InsertBST(bt,A[i])==1)		//将A[i]插入二叉排序树T中
		{
			printf("    第%d步,插入%d:",i+1,A[i]);
			DispBST(bt);printf("\n");
			i++;
		}
    return bt;               			//返回建立的二叉排序树的根指针
}
void Delete1(BSTNode *p,BSTNode *&r) //被删节点p有左、右子树，r指向其左孩子
{	BSTNode *q;
	if (r->rchild!=NULL)		//递归找节点r的最右下节点
		Delete1(p,r->rchild);
	else						//找到了最右下节点r（它没有右子树）
	{	p->key=r->key;			//将节点r的值存放到节点p中（节点值替代）
		p->data=r->data;
		q=r;					//删除节点r
		r=r->lchild;			//即用节点r的左孩子替代它
		free(q);				//释放节点r的空间
	}
}
void Delete(BSTNode *&p)		//从二叉排序树中删除p节点
{
	BSTNode *q;
	if (p->rchild==NULL)		//p节点没有右子树的情况
	{
		q=p;p=p->lchild;free(q);
	}
	else if (p->lchild==NULL)	//p节点没有左子树的情况
	{
		q=p;p=p->rchild;free(q);
	}
	else Delete1(p,p->lchild);	//p节点既有左子树又有右子树的情况
}
bool DeleteBST(BSTNode *&bt,KeyType k)	
//在bt中删除关键字为k的节点
{
	if (bt==NULL) return false;		//空树删除失败
	else 
	{
		if (k<bt->key) 
			return DeleteBST(bt->lchild,k);		//递归在左子树中删除关键字为k的节点
		else if (k>bt->key) 
			return DeleteBST(bt->rchild,k);		//递归在右子树中删除关键字为k的节点
		else									//k=bt->key的情况
		{
			Delete(bt);							//调用Delete(bt)函数删除bt节点
			return true;
		}
	}
}
void SearchBST1(BSTNode *bt,KeyType k,KeyType path[],int i)	
//以非递归方式输出从根节点到查找到的节点的路径
{ 
	int j;
	if (bt==NULL)
		return;
	else if (k==bt->key)	//找到了节点
	{
		path[i+1]=bt->key;	//输出其路径
		for (j=0;j<=i+1;j++)
			printf("%3d",path[j]);
		printf("\n");
	}
	else
	{
		path[i+1]=bt->key;
		if (k<bt->key)
			SearchBST1(bt->lchild,k,path,i+1);  //在左子树中递归查找
		else
			SearchBST1(bt->rchild,k,path,i+1);  //在右子树中递归查找
	}
}
int SearchBST2(BSTNode *bt,KeyType k)	
//以递归方式输出从根节点到查找到的节点的路径
{ 
	if (bt==NULL)
		return 0;
	else if (k==bt->key)
	{
		printf("%3d",bt->key);
		return 1;
	}
	else if (k<bt->key)
		SearchBST2(bt->lchild,k);  //在左子树中递归查找
	else
		SearchBST2(bt->rchild,k);  //在右子树中递归查找
	printf("%3d",bt->key);
}

void DispBST(BSTNode *bt)	
//以括号表示法输出二叉排序树bt
{
	if (bt!=NULL)
	{
		printf("%d",bt->key);
		if (bt->lchild!=NULL || bt->rchild!=NULL)
		{
			printf("(");
			DispBST(bt->lchild);
			if (bt->rchild!=NULL) printf(",");
			DispBST(bt->rchild);
			printf(")");
		}
	}
}
KeyType predt=-32767;		//predt为全局变量,保存当前节点中序前驱的值,初值为-∞
bool JudgeBST(BSTNode *bt)	//判断bt是否为BST
{
	bool b1,b2;
	if (bt==NULL)
		return true;
	else 
	{
		b1=JudgeBST(bt->lchild);
		if (b1==false || predt>=bt->key)
			return false;
		predt=bt->key;
		b2=JudgeBST(bt->rchild);
		return b2;
	}
}
void DestroyBST(BSTNode *bt)	//销毁一颗BST
{
	if (bt!=NULL)
	{
		DestroyBST(bt->lchild);
		DestroyBST(bt->rchild);
		free(bt);
	}
}
