//文件名:exp9-11.cpp
#include "bst.cpp"   //二叉排序树基本运算算法
bool Findseq(BSTNode *bt,int a[],int n)	//判断a是否为bt中的一个合法查找序列
{	BSTNode *p=bt;
	int i=0;
	while (i<n && p!=NULL)
	{
		if (i==n-1 && a[i]==p->key)			//a查找完毕，返回true
			return true;
		if (p->key!=a[i])					//若不等，表示a不是查找序列
			return false;					//返回false
		i++;								//查找序列指向下一个关键字
		if (a[i]<p->key) p=p->lchild;		//在左子树中查找
		else if (a[i]>p->key) p=p->rchild;	//在右子树中查找
	}
	return false;
}


int main()
{
	BSTNode *bt;
	KeyType keys[]={5,2,3,4,1,6,8,7,9};
	int m=9;
	printf("(1)构造二叉排序树bt\n");
	bt=CreateBST(keys,m);		//创建二叉排序树
	printf("(2)输出BST:");DispBST(bt);printf("\n");
	int n=4;
	KeyType a[]={5,6,8,9};
	printf("(3)关键字序列:");
	for (int i=0;i<n;i++)
		printf("%d ",a[i]);
	if (Findseq(bt,a,n))
		printf("是一个查找序列\n");
	else
		printf("不是一个查找序列\n");
	printf("(4)销毁bt\n"); DestroyBST(bt);
	return 1;
}
