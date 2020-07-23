//堆排序算法
#include "seqlist.cpp"

void sift(RecType R[],int low,int high)
{
	int i=low,j=2*i;     					//R[j]是R[i]的左孩子
	RecType temp=R[i];
	while (j<=high) 
	{
		if (j<high && R[j].key<R[j+1].key) 	//若右孩子较大,把j指向右孩子
			j++;    						//变为2i+1
		if (temp.key<R[j].key) 
		{
			R[i]=R[j];              		//将R[j]调整到双亲结点位置上
			i=j;                    		//修改i和j值,以便继续向下筛选
			j=2*i;
		}
		else break;                 		//筛选结束
	}
	R[i]=temp;                      		//被筛选结点的值放入最终位置
}

void HeapSort(RecType R[],int n)
{
	int i;
	RecType tmp;
	for (i=n/2;i>=1;i--)	//循环建立初始堆,调用sift算法 n/2 次
		sift(R,i,n); 
	printf("初始堆:"); DispList1(R,n);
	for (i=n;i>=2;i--)		//进行n-1趟完成推排序,每一趟堆排序的元素个数减1
	{	tmp=R[1];			//将最后一个元素与根R[1]交换
		R[1]=R[i];
		R[i]=tmp;
		printf("第%d趟: ",n-i+1); DispList1(R,n);
		sift(R,1,i-1);		//对R[1..i-1]进行筛选,得到i-1个节点的堆
		printf("筛选为:"); DispList1(R,n);
	}
}


int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={15,18,29,12,35,32,27,23,10,20};
	CreateList1(R,a,n);
	printf("排序前:"); DispList1(R,n);
	HeapSort(R,n);
	printf("排序后:"); DispList1(R,n);
	return 1;
}

/*
int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={0,9,8,7,6,5,4,3,2,1,0};
	CreateList1(R,a,n);
	printf("排序前:"); DispList1(R,n);
	HeapSort(R,n);
	printf("排序后:"); DispList1(R,n);
	return 1;
}
*/

