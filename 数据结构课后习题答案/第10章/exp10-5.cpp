//文件名:exp10-5.cpp
#include "seqlist.cpp"					//包含排序顺序表的基本运算算法
void disppart(RecType R[],int s,int t)	//显示一趟划分后的结果
{
	static int i=1;
	int j;
	printf("第%d次划分:",i);
	for (j=0;j<s;j++)
		printf("   ");
	for (j=s;j<=t;j++)
		printf("%3d",R[j].key);
	printf("\n");
	i++;
}
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
	disppart(R,s,t);
	return i;
}
void QuickSort(RecType R[],int s,int t) //对R[s..t]的元素进行递增快速排序
{
	int i;
	if (s<t) 					//区间内至少存在两个元素的情况
	{	i=partition(R,s,t);
		QuickSort(R,s,i-1);		//对左区间递归排序
		QuickSort(R,i+1,t);		//对右区间递归排序
	}
}

int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	QuickSort(R,0,n-1);
	printf("排序后:"); DispList(R,n);
	return 1;
}
