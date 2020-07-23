//冒泡排序算法
#include "seqlist.cpp"

void BubbleSort(RecType R[],int n)
{
	int i,j,k;
	RecType tmp;
	for (i=0;i<n-1;i++) 
	{
		for (j=n-1;j>i;j--)	//比较,找出本趟最小关键字的记录
			if (R[j].key<R[j-1].key)   
			{
				tmp=R[j];  //R[j]与R[j-1]进行交换,将最小关键字记录前移
				R[j]=R[j-1];
				R[j-1]=tmp;
			}
		printf("  i=%d: ",i);
		DispList(R,n);
	}
} 
int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	BubbleSort(R,n); 
	printf("排序后:"); DispList(R,n);
	return 1;
}


