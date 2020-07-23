//简单选择排序算法
#include "seqlist.cpp"

void SelectSort(RecType R[],int n)
{
	int i,j,k;
	RecType temp;
	for (i=0;i<n-1;i++)    	 	//做第i趟排序
	{
		k=i;
		for (j=i+1;j<n;j++)  	//在当前无序区R[i..n-1]中选key最小的R[k]
			if (R[j].key<R[k].key)
				k=j;           	//k记下目前找到的最小关键字所在的位置
			if (k!=i)          		//交换R[i]和R[k]
			{
				temp=R[i];
				R[i]=R[k];
				R[k]=temp;  
			}
		printf("  i=%d: ",i); DispList(R,n);
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


