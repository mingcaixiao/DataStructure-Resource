//【例7.12】的算法：输出一棵给定二叉树的所有叶子节点
#include "btree.cpp"
void DispLeaf(BTNode *b)
{
	if (b!=NULL) 
	{
		if (b->lchild==NULL && b->rchild==NULL) 
			printf("%c ",b->data);	//访问叶子节点
		DispLeaf(b->lchild);		//输出左子树中的叶子节点
		DispLeaf(b->rchild);		//输出右子树中的叶子节点
	}
}
void DispLeaf1(BTNode *b)
{
	if (b!=NULL) 
	{
		if (b->lchild==NULL && b->rchild==NULL) 
			printf("%c ",b->data);	//访问叶子节点
		DispLeaf1(b->rchild);		//输出右子树中的叶子节点
		DispLeaf1(b->lchild);		//输出左子树中的叶子节点
	}
}
int main()
{
	BTNode *b;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTree(b);printf("\n");
	printf("从左到右输出所有叶子节点:");DispLeaf(b);printf("\n");
	printf("从右到左输出所有叶子节点:");DispLeaf1(b);printf("\n");
	DestroyBTree(b);
	return 1;
}
