//文件名:exp10-3.cpp
#include "seqlist.cpp"				//包含排序顺序表的基本运算算法

void ShellSort(RecType R[],int n)	//对R[0..n-1]按递增有序进行希尔排序
{	int i,j,d;
	RecType tmp;
	d=n/2;					//增量置初值
	while (d>0)
	{	for (i=d;i<n;i++) 		//对所有组采用直接插入排序
		{	tmp=R[i];			//对相隔d个位置一组采用直接插入排序
			j=i-d;
			while (j>=0 && tmp.key<R[j].key)
			{	R[j+d]=R[j];
				j=j-d;
			}
			R[j+d]=tmp;
		}
		printf("  d=%d: ",d); DispList(R,n);
		d=d/2;				//减小增量
	}
}
int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	ShellSort(R,n);
	printf("排序后:"); DispList(R,n);
	return 1;
}