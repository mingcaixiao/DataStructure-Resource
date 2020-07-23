//文件名:exp10-6.cpp
#include "seqlist.cpp"				//包含排序顺序表的基本运算算法

void SelectSort(RecType R[],int n)	//简单选择排序算法
{
	int i,j,k;
	for (i=0;i<n-1;i++)    	 	//做第i趟排序
	{	
		k=i;
		for (j=i+1;j<n;j++)  	//在当前无序区R[i..n-1]中选key最小的R[k] 
			if (R[j].key<R[k].key)
				k=j;           	//k记下目前找到的最小关键字所在的位置
		if (k!=i)          		//交换R[i]和R[k] 
			swap(R[i],R[k]);
		printf(" i=%d,选择关键字:%d,排序结果为:",i,R[i].key);
		DispList(R,n);			//输出每一趟的排序结果
	}
}
int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	SelectSort(R,n);
	printf("排序后:"); DispList(R,n);
	return 1;
}

