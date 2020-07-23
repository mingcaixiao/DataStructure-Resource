//文件名:exp9-7.cpp
#include <stdio.h>
#define MAXL 100					//定义表中最多记录个数
typedef int KeyType;				//定义关键字类型为int
typedef char InfoType;
typedef struct
{	KeyType key;					//关键字项
	InfoType data;					//其他数据项，类型为InfoType
} RecType;							//查找元素的类型

KeyType M_Search(RecType A[],RecType B[],int n)	//求A、B的中位数
{
	int start1,end1,mid1,start2,end2,mid2;
	start1=0; end1=n-1;
	start2=0; end2=n-1;
	while(start1!=end1 || start2!=end2)
	{
		mid1=(start1+end1)/2;
		mid2 = (start2+end2)/2;
		if(A[mid1].key==B[mid2].key)
			return A[mid1].key;
		if(A[mid1].key<B[mid2].key)
		{				//分别考虑奇数和偶数，保持两个子序列元素个数相等
			if((start1+end1)%2==0) //若元素为奇数个
			{	
				start1=mid1;		//舍弃A中间点以前的部分且保留中间点
				end2=mid2;			//舍弃B中间点以后的部分且保留中间点
			}
			else					//若元素为偶数个
			{	
				start1=mid1+1;		//舍弃A的前半部分
				end2=mid2;			//舍弃B的后半部分
			}
		}
		else
		{	if((start1+end1)%2==0)	//若元素为奇数个
			{
				end1 = mid1;		//舍弃A中间点以后的部分且保留中间点
				start2 = mid2;		//舍弃B中间点以前的部分且保留中间点
			}
			else					//若元素为偶数个
			{
				end1=mid1;			//舍弃A的后半部分
				start2=mid2+1;		//舍弃B的前半部分
			}
		}
	}
	return A[start1].key<B[start2].key?A[start1].key:B[start2].key;
}


int main()
{
	KeyType keys1[]={11,13,15,17,19};
	KeyType keys2[]={2,4,6,8,20};
	int n=5,i;
	RecType A[MAXL],B[MAXL];
	for (i=0;i<n;i++)
		A[i].key=keys1[i];
	for (i=0;i<n;i++)
		B[i].key=keys2[i];
	printf("A:"); 
	for (i=0;i<n;i++) printf("%3d",A[i].key);
	printf("\n");
	printf("B:"); 
	for (i=0;i<n;i++) printf("%3d",B[i].key);
	printf("\n");
	printf("A和B的中位数:%d\n",M_Search(A,B,n));

	return 1;
}