//文件名:exp10-7.cpp
#include "seqlist.cpp"					//包含排序顺序表的基本运算算法

int count=1;							//全局变量
void DispHeap(RecType R[],int i,int n)	//以括号表示法输出建立的堆
{
	if (i<=n)
		printf("%d",R[i].key);			//输出根节点
	if (2*i<=n || 2*i+1<n)
	{
		printf("(");
		if (2*i<=n)
			DispHeap(R,2*i,n);			//递归调用输出左子树
		printf(",");
		if (2*i+1<=n)
			DispHeap(R,2*i+1,n);		//递归调用输出右子树
		printf(")");
	}
}
void Sift(RecType R[],int low,int high)		//R[loww..high}堆筛选算法
{
	int i=low,j=2*i;     					//R[j]是R[i]的左孩子
	RecType temp=R[i];
	while (j<=high) 
	{	
		if (j<high && R[j].key<R[j+1].key) 	//若右孩子较大,把j指向右孩子
			j++;    						//变为2i+1
	    if (temp.key<R[j].key) 
		{	
			R[i]=R[j];              		//将R[j]调整到双亲节点位置上
		    i=j;                    		//修改i和j值,以便继续向下筛选
		    j=2*i;
		}
	    else break;                 		//筛选结束
	}
    R[i]=temp;                      		//被筛选节点的值放入最终位置
}
void HeapSort(RecType R[],int n)	//对R[1]到R[n]元素实现堆排序
{
	int i,j;
	for (i=n/2;i>=1;i--)  		//循环建立初始堆
		Sift(R,i,n); 
	printf("初始堆:");DispHeap(R,1,n);printf("\n");	//输出初始堆
	for (i=n;i>=2;i--)   	//进行n-1次循环,完成推排序
	{  	
		printf("第%d趟排序:",count++);
		printf(" 交换%d与%d,输出%d ",R[i].key,R[1].key,R[1].key);
		swap(R[1],R[i]);        //将第一个元素同当前区间内R[1]对换
		printf(" 排序结果:");	//输出每一趟的排序结果
		for (j=1;j<=n;j++)
			printf("%2d",R[j].key);
		printf("\n");
        Sift(R,1,i-1);     		//筛选R[1]节点,得到i-1个节点的堆
		printf("筛选调整得到堆:");DispHeap(R,1,i-1);printf("\n");
	}
}
int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	CreateList1(R,a,n);
	printf("排序前:"); DispList1(R,n);
	HeapSort(R,n);
	printf("排序后:"); DispList1(R,n);
	return 1;
}
