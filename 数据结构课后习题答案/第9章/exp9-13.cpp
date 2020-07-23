//文件名:exp9-13.cpp
#include <stdio.h>
#define MAXL 100					//定义表中最多记录个数
typedef int KeyType;				//定义关键字类型为int
typedef char InfoType;
typedef struct
{	KeyType key;					//关键字项
	InfoType data;					//其他数据项，类型为InfoType
} RecType;							//查找元素的类型
int FindElem(RecType R[],int n,KeyType k)	//(1)小题对应的算法
{
	int i=4,j;
	if (k<R[1].key || k>R[4*n].key) 
		return 0;				//不在范围内返回0
	while(i<=4*n)
	{
		if (R[i].key==k)
			return i;			//查找成功返回
		else if (R[i].key<k)
			i+=4;
		else					//找到大于k的位置i
			break;
	}
	j=i-3;
	while (j<i && R[j].key!=k)
		j++;					//在R[i-3..i-1]中查找
	if (j<i)					//查找成功返回
		return j;
	else
		return 0;
}

int ImproveFindElem(RecType R[],int n,KeyType k)	//(2)小题对应的算法
{
	int low,high,mid;
	int i,j;
	if (k<R[1].key || k>R[4*n].key) 
		return 0;				//不在范围内返回0
	low=4; high=4*n;
	while (low<=high)			//二分查找
	{		
		mid=(low+high)/2;
		if (k<R[mid].key)
			high=mid-4;
		else if (k>R[mid].key)
			low=mid+4;
		else 
			return mid;
	}							//查找失败时刚好有k>R[high].key并且k<=R[high+4].key
	i=high+4;
	j=high+1;
	while (j<i && R[j].key!=k)
		j++;					//在R[high+1..high+4]中查找
	if (j<i)					//查找成功返回j
		return j;
	else						//查找不成功返回0
		return 0;
}

int main()
{
	int i,m=13,n=3;
	KeyType keys[]={0,1,2,3,4,5,6,7,8,9,10,11,12};
	RecType R[MAXL];
	for (i=0;i<m;i++) R[i].key=keys[i];
	printf("R:");
	for (i=0;i<m;i++)
		printf("%3d",R[i].key);
	printf("\n");
	KeyType k=8;
	printf("用算法(1)查找关键字%d:\n",k);
	i=FindElem(R,n,k);
	if (i>=1)
		printf("  结果:R[%d]=%d\n",i,k);
	else
		printf("  未找到%d\n",k);
	k=20;
	printf("用算法(2)查找关键字%d:\n",k);
	i=ImproveFindElem(R,n,k);
	if (i>=1)
		printf("  结果:R[%d]=%d\n",i,k);
	else
		printf("  未找到%d\n",k);
	return 1;
}
