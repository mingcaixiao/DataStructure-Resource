//文件名:exp9-4.cpp
#include "bst.cpp"		//包含二叉排序树的运算算法
int main()
{
	BSTNode *bt;
	int path[MaxSize];
	KeyType k=6;
	int a[]={4,9,0,1,8,6,3,5,2,7},n=10;
	printf("(1)创建一棵BST树:");
	printf("\n");
	bt=CreateBST(a,n);
	printf("(2)BST:");DispBST(bt);printf("\n");
	printf("(3)bt%s\n",(JudgeBST(bt)?"是一棵BST":"不是一棵BST"));
	printf("(4)查找%d关键字(递归,顺序):",k);SearchBST1(bt,k,path,-1);
	printf("(5)查找%d关键字(非递归,逆序):",k);SearchBST2(bt,k);
	printf("\n(6)删除操作:\n");
	printf("   原BST:");DispBST(bt);printf("\n");
	printf("   删除节点4:");
	DeleteBST(bt,4); DispBST(bt); printf("\n");
	printf("   删除节点5:");
	DeleteBST(bt,5); DispBST(bt); printf("\n");
	printf("(7)销毁BST\n"); DestroyBST(bt);
	return 1;
}
