//【例7.13】的算法：求二叉树中指定节点的层次
#include "btree.cpp"
int Level(BTNode *b,ElemType x,int h)	//h置初值1
{	int l;
	if (b==NULL)
		return(0);
	else if (b->data==x)
		return(h);
	else
	{	l=Level(b->lchild,x,h+1);	//在左子树中查找
		if (l!=0)
			return(l);
		else						//在左子树中未找到,再在右子树中查找
			return(Level(b->rchild,x,h+1));
	}
}
int main()
{	BTNode *b;
	int h;
	ElemType x;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTree(b);printf("\n");
	printf("节点值:");
	scanf("%c",&x);
	h=Level(b,x,1);
	if (h==0)
		printf("b中不存在%c节点\n",x);
	else
		printf("在b中%c节点的层次为%d\n",x,h);
	DestroyBTree(b);
	return 1;
}
