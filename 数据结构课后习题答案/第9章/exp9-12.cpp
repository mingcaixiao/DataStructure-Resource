//文件名:exp9-12.cpp
#include "bst.cpp"   //二叉排序树基本运算算法

BSTNode *LCA(BSTNode *bt,KeyType x,KeyType y) //在二叉排序树bt中求x和y节点的LCA，并返回该节点的指针
{
	if (bt==NULL) return NULL;
	if (x<bt->key && y<bt->key)
		return LCA(bt->lchild,x,y);
	else if (x>bt->key && y>bt->key)
		return LCA(bt->rchild,x,y);
	else
		return bt;
}


int main()
{
	BSTNode *bt,*p;
	KeyType x=1,y=4;
	KeyType a[]={5,2,1,6,7,4,8,3,9},n=9;
	printf("(1)构造二叉排序树bt\n");
	bt=CreateBST(a,n);		//创建一棵二叉排序树
	printf("(2)输出BST:");DispBST(bt);printf("\n");
	printf("(3)查找%d和%d节点的LCA\n",x,y);
	if (p=LCA(bt,x,y))
		printf("  LCA是:%d\n",p->key);
	else
		printf("  指定的关键字不存在\n");
	printf("(4)销毁bt"); DestroyBST(bt); printf("\n");
	return 1;
}
