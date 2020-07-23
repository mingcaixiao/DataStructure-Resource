//文件名:exp10-1.cpp
#include "seqlist.cpp"				//包含排序顺序表的基本运算算法
void InsertSort(RecType R[],int n)	//对R[0..n-1]按递增有序进行直接插入排序
{	int i, j; RecType tmp;
	for (i=1;i<n;i++) 
	{
		printf("  i=%d，插入%d，插入结果: ",i,R[i].key); 
		if (R[i].key<R[i-1].key)	//反序时 
		{	tmp=R[i];
			j=i-1; 
			do						//找R[i]的插入位置 
			{	R[j+1]=R[j];   		//将关键字大于R[i].key的记录后移
				j--;
			}  while  (j>=0 && R[j].key>tmp.key);
			R[j+1]=tmp;      		//在j+1处插入R[i]
		}
		DispList(R,n);
	}
}
int main()
{	int n=10;
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	RecType R[MAXL];
	CreateList(R,a,n);
	printf("排序前: ");	DispList(R,n);
	InsertSort(R,n);
	printf("排序后: "); DispList(R,n);
	return 1;
}
