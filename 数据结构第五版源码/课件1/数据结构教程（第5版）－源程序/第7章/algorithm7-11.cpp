//【例7.11】的算法：计算一棵给定二叉树的所有节点个数
#include "btree.cpp"
int Nodes(BTNode *b)
{	int num1,num2;
	if (b==NULL) 
		return 0;
	else
		return Nodes(b->lchild)+Nodes(b->rchild)+1;
}

int main()
{
	BTNode *b;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTree(b);printf("\n");
	printf("节点个数:%d\n",Nodes(b));
	DestroyBTree(b);
	return 1;
}
