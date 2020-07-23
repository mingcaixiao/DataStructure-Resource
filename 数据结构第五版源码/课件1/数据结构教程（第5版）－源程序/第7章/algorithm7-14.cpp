//【例7.14】的算法：求二叉树中指定层次的节点个数
#include "btree.cpp"
void Lnodenum(BTNode *b,int h,int k,int &n)
{	if (b==NULL)			//空树直接返回
		return;
	else					//处理非空树
	{	if (h==k) n++;		//当前访问的节点在第k层时，n增1
		else if (h<k)		//若当前节点层次小于k，递归处理左、右子树
		{	Lnodenum(b->lchild,h+1,k,n);
			Lnodenum(b->rchild,h+1,k,n);
		}
	}
}
int main()
{	BTNode *b;
	int k,n=0;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTree(b);printf("\n");
	printf("层次:");
	scanf("%d",&k);
	Lnodenum(b,1,k,n);
	if (n==0)
		printf("b中不存在第%d层\n",k);
	else
		printf("在b中第%d层有%d个节点\n",k,n);
	DestroyBTree(b);
	return 1;
}
