//折半插入排序算法
#include "seqlist.cpp"

void BinInsertSort(RecType R[],int n)
{	int i, j, low, high, mid;
	RecType tmp;
	for (i=1;i<n;i++) 
	{
		if (R[i].key<R[i-1].key)		//反序时 
		{
			tmp=R[i];		  			//将R[i]保存到tmp中
	     	low=0;  high=i-1;
			while (low<=high)	  		//在R[low..high]中查找插入的位置
			{
				mid=(low+high)/2;		//取中间位置
				if (tmp.key<R[mid].key)
					high=mid-1;			//插入点在左半区
				else 
					low=mid+1;			//插入点在右半区
			}                          	//找位置high
			for (j=i-1;j>=high+1;j--)	//集中进行元素后移
				R[j+1]=R[j];
			R[high+1]=tmp;				//插入tmp 
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
	BinInsertSort(R,n);
	printf("排序后:"); DispList(R,n);
	return 1;
}


