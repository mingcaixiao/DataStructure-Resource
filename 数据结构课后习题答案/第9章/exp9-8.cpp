//文件名:exp9-8.cpp
#include "bst.cpp"   //二叉排序树基本运算算法

BSTNode *CreateBST1(KeyType a[],int start,int end) //创建一棵二叉排序树
{
	int mid;
	BSTNode * bt;
	if (end<start)
		return NULL;		//返回空树
	mid=(start+end)/2;
	bt=(BSTNode *)malloc(sizeof(BSTNode));
	bt->key=a[mid];
	bt->lchild=CreateBST1(a,start,mid-1);
	bt->rchild=CreateBST1(a,mid+1,end);
	return bt;
}
int main()
{
	BSTNode *bt;
	int n=9;
	KeyType a[]={1,2,3,4,5,6,7,8,9};
	bt=CreateBST1(a,0,n-1);
	printf("BST:"); DispBST(bt); printf("\n");
	DestroyBST(bt);
	return 1;
}
