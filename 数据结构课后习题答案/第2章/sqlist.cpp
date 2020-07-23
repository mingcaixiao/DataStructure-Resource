//顺序表运算算法
#include <stdio.h>
#include <malloc.h>
#define MaxSize 50
typedef char ElemType; 
typedef struct 
{	ElemType data[MaxSize];		//存放顺序表元素
   	int length;					//存放顺序表的长度
} SqList;						//声明顺序表的类型
void CreateList(SqList *&L,ElemType a[],int n) //整体建立顺序表
{
	L=(SqList *)malloc(sizeof(SqList));
	for (int i=0;i<n;i++)
		L->data[i]=a[i];
	L->length=n;
}
void InitList(SqList *&L)	//初始化线性表
{
	L=(SqList *)malloc(sizeof(SqList));	//分配存放线性表的空间
	L->length=0;
}
void DestroyList(SqList *&L)  //销毁线性表
{
	free(L);
}
bool ListEmpty(SqList *L)	//判线性表是否为空表
{
	return(L->length==0);
}
int ListLength(SqList *L)	//求线性表的长度
{
	return(L->length);
}
void DispList(SqList *L)	//输出线性表
{
	for (int i=0;i<L->length;i++)
		printf("%c ",L->data[i]);
	printf("\n");
}
bool GetElem(SqList *L,int i,ElemType &e)	//求线性表中第i个元素值
{
	if (i<1 || i>L->length)
		return false;
	e=L->data[i-1];
	return true;
}
int LocateElem(SqList *L, ElemType e)	//查找第一个值域为e的元素序号
{
	int i=0;
	while (i<L->length && L->data[i]!=e) i++;
	if (i>=L->length)
		return 0;
	else
		return i+1;
}
bool ListInsert(SqList *&L,int i,ElemType e)	//插入第i个元素
{
	int j;
	if (i<1 || i>L->length+1)
		return false;
	i--;						//将顺序表位序转化为elem下标
	for (j=L->length;j>i;j--) 	//将data[i]及后面元素后移一个位置
		L->data[j]=L->data[j-1];
	L->data[i]=e;
	L->length++;				//顺序表长度增1
	return true;
}
bool ListDelete(SqList *&L,int i,ElemType &e)	//删除第i个元素
{
	int j;
	if (i<1 || i>L->length)
		return false;
	i--;						//将顺序表位序转化为elem下标
	e=L->data[i];
	for (j=i;j<L->length-1;j++)	//将data[i]之后的元素前移一个位置
		L->data[j]=L->data[j+1];
	L->length--;				//顺序表长度减1
	return true;
}
