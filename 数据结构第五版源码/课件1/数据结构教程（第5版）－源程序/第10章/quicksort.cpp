//快速排序算法
#include "seqlist.cpp"
int count=0;
int partition(RecType R[],int s,int t)	//一趟划分
{
	int i=s,j=t;
	RecType tmp=R[i];			//以R[i]为基准
	while (i<j)  				//从两端交替向中间扫描,直至i=j为止
	{	while (j>i && R[j].key>=tmp.key)
			j--;				//从右向左扫描,找一个小于tmp.key的R[j]
		R[i]=R[j];				//找到这样的R[j],放入R[i]处
		while (i<j && R[i].key<=tmp.key)
			i++;				//从左向右扫描,找一个大于tmp.key的R[i]
		R[j]=R[i];				//找到这样的R[i],放入R[j]处
	}
	R[i]=tmp;
	return i;
}
void QuickSort(RecType R[],int s,int t) //对R[s..t]的元素进行快速排序
{	int i;
	RecType tmp;
	if (s<t) 					//区间内至少存在两个元素的情况
	{	count++;
		i=partition(R,s,t);
		DispList(R,10);			//调试用
		QuickSort(R,s,i-1);		//对左区间递归排序
		QuickSort(R,i+1,t);		//对右区间递归排序
	}
}
/*
int main()
{
	int i,n=10;
	RecType R[MAXL];
	KeyType a[]={15,18,29,12,35,32,27,23,10,20};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	QuickSort(R,0,n-1);
	printf("排序后:"); DispList(R,n);
	return 1;
}
*/

int main()
{
	int i,n=10;
	RecType R[MAXL];
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	QuickSort(R,0,n-1);
	printf("排序后:"); DispList(R,n);
	printf("count=%d\n",count);
	return 1;
}



