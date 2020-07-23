//文件名:exp9-10.cpp
#include "bst.cpp"   //二叉排序树基本运算算法

void Succlength(BSTNode *bt,int &sumlen,int &m,int level) //求查找成功总的比较次数sumlen和情况数m
{
	if (bt==NULL) return;	//空树直接返回
	m++;
	sumlen+=level;
	Succlength(bt->lchild,sumlen,m,level+1);
	Succlength(bt->rchild,sumlen,m,level+1);
}
double ASLsucc(BSTNode *bt)	//求查找成功情况下的平均查找长度
{
	int sumlen=0,m=0;
	Succlength(bt,sumlen,m,1);
	return sumlen*1.0/m;
}
void Unsucclength(BSTNode *bt,int &sumlen,int &m,int level) //求查找失败总的比较次数sumlen和情况数m
{
	if (bt==NULL)		//空指针对应外部节点
	{
		m++;
		sumlen+=level-1;
		return;
	}
	Unsucclength(bt->lchild,sumlen,m,level+1);
	Unsucclength(bt->rchild,sumlen,m,level+1);
}
double ASLunsucc(BSTNode *bt)	//求查找失败情况下的平均查找长度
{
	int sumlen=0,m=0;
	Unsucclength(bt,sumlen,m,1);
	return sumlen*1.0/m;
}
int main()
{
	BSTNode *bt;
	int n=12;
	KeyType a[]={25,18,46,2,53,39,32,4,74,67,60,11};
	printf("(1)创建BST\n");				//创建《教程》例9.3的一棵BST
	bt=CreateBST(a,n);
	printf("(2)BST:"); DispBST(bt); printf("\n");
	printf("(3)ASLsucc=%g\n",ASLsucc(bt));
	printf("(4)ASLunsucc=%g\n",ASLunsucc(bt));
	DestroyBST(bt);
	return 1;
}
