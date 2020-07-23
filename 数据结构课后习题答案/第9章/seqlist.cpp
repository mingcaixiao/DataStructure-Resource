//顺序表基本运算算法
#include <stdio.h>
#include <malloc.h>
#define MAXL 100		//最大长度
typedef int KeyType;	//定义关键字类型为int
typedef char InfoType;

typedef struct
{	KeyType key;		//关键字项
	InfoType data;		//其他数据项，类型为InfoType
} RecType;				//查找元素的类型

void CreateList(RecType R[],KeyType keys[],int n)	//创建顺序表
{
	for (int i=0;i<n;i++)			//R[0..n-1]存放排序记录
		R[i].key=keys[i];
}
void DispList(RecType R[],int n)	//输出顺序表
{
	for (int i=0;i<n;i++)
		printf("%d ",R[i].key);
	printf("\n");
}
