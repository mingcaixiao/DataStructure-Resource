//文件名:exp9-6.cpp
#include <stdio.h>
#define MAXL 100					//定义表中最多记录个数
typedef int KeyType;				//定义关键字类型为int
typedef char InfoType;
typedef struct
{	KeyType key;					//关键字项
	InfoType data;					//其他数据项，类型为InfoType
} RecType;							//查找元素的类型
int lowerbound(RecType R[],int n,KeyType k)	//求关键字为k记录的下界
{
	int low=0, high=n-1, mid;
	while (low!=high)
	{
		mid=(low+high)/2;
		if (k>R[mid].key)
			low=mid+1;
		else
			high=mid;
	}
	return low;
}
int upperbound(RecType R[],int n,KeyType k)	//求关键字为k记录的上界
{
	int low=0, high=n-1, mid;
	while (low!=high)
	{
		mid=(low+high)/2;
		if (k>=R[mid].key)
			low=mid+1;
		else
			high=mid;
	}
	return low;
}
void SearchRange(RecType R[],int n,KeyType k)  //输出关键字为k的记录的区间
{
	int lower=lowerbound(R,n,k);
	int upper=upperbound(R,n,k);
	printf("lower=%d,upper=%d\n",lower,upper);
}
int main()
{
	RecType R[MAXL];
	KeyType k=9;
	int a[]={1,2,3,3,3,3,3,8,9,10},i,n=10;
	for (i=0;i<n;i++)				//建立顺序表
		R[i].key=a[i];
	printf("关键字序列:");
	for (i=0;i<n;i++)
		printf("%d ",R[i].key);
	printf("\n");
	printf("查找关键字-1:\t",R[i].key); SearchRange(R,n,-1);
	for (i=0;i<n;i++)
	{
		printf("查找关键字%d:\t",R[i].key); SearchRange(R,n,R[i].key);
	}
	printf("查找关键字20:\t",R[i].key); SearchRange(R,n,20);
	return 1;
}
