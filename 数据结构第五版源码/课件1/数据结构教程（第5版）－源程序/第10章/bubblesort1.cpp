//改进的冒泡排序算法
#include "seqlist.cpp"

void BubbleSort1(RecType R[],int n)
{	int i,j;
	bool exchange;
	RecType tmp;
	for (i=0;i<n-1;i++) 
	{	exchange=false;					//一趟前exchange置为假
		for (j=n-1;j>i;j--)				//归位R[i],循环n-i-1次
			if (R[j].key<R[j-1].key)	//相邻两个元素反序时
			{	tmp=R[j];				//将这两个元素交换
				R[j]=R[j-1];
				R[j-1]=tmp;
				exchange=true;			//一旦有交换，exchange置为真
			}
		printf("  i=%d: ",i);
		DispList(R,n);
		if (!exchange)					//本趟没有发生交换，中途结束算法
			return;
	}
}

int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={0,1,7,2,5,4,3,6,8,9};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	BubbleSort1(R,n);  
	printf("排序后:"); DispList(R,n);
	return 1;
}


