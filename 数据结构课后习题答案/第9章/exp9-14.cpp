//文件名:exp9-14.cpp
#include <stdio.h>
#include <malloc.h>
#include <math.h>
typedef struct node
{
	long index;						//当前节点对应的记录下标
	int level;						//当前节点的层次
	struct node *lchild,*rchild;	//左右孩子指针
} DecNode;							//判定树节点类型
void CreateDectree1(DecNode *&b,long low,long high,int h) //由CreateDectree调用以建立判定树
{
	int mid;
	if (low<=high)
	{
		mid=(low+high)/2;
		b=(DecNode *)malloc(sizeof(DecNode));
		b->index=mid;
		b->level=h; 
		CreateDectree1(b->lchild,low,mid-1,h+1);
		CreateDectree1(b->rchild,mid+1,high,h+1);
	}
	else
		b=NULL;
}
void CreateDectree(DecNode *&b,long n)	//建立判定树b
{
	CreateDectree1(b,0,n-1,1);
}
	
void DispDectree(DecNode *b)	//以括号表示法输出二叉树b
{
	if (b!=NULL)
	{
		printf("%d[%d]",b->index,b->level);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{
			printf("(");
			DispDectree(b->lchild);
			if (b->rchild!=NULL) printf(",");
			DispDectree(b->rchild);
			printf(")");
		}
	}
}
void DestroyDectree(DecNode *&b)		//销毁判定树b
{
	if (b!=NULL)
	{
		DestroyDectree(b->lchild);
		DestroyDectree(b->rchild);
		free(b);
	}
}
int Sum(DecNode *b)		//求判定树b中比较的总次数
{
	if (b!=NULL)
	{
		if (b->lchild==NULL && b->rchild==NULL)
			return b->level;
		else
			return Sum(b->lchild)+Sum(b->rchild)+b->level;
	}
	else
		return 0;
}
double ASLsucc(DecNode *b,long n)	//求成功情况下的平均查找长度
{
	return 1.0*Sum(b)/n;
}
int main()
{
	DecNode *b;
	long n=11;
	double d,asl1,asl2;
	CreateDectree(b,n);
	printf("R[0..%d]判定树:\n\t",n-1);
	DispDectree(b);
	printf("\n\tASL=%g\n",ASLsucc(b,n));
	DestroyDectree(b);
	printf("成功平均查找长度分析:\n");
	printf("\tn\t\tASL1\t\tASL2\t\t差值\n");  
	for (n=10;n<=1000000;n*=10)
	{
		CreateDectree(b,n);
		asl1=ASLsucc(b,n);
		asl2=log(n+1)-1;
		d=asl1-asl2;
		printf("  %10d\t\t%g\t\t%g\t\t%g\n",n,asl1,asl2,d);
		DestroyDectree(b);
	}
	return 1;
}
