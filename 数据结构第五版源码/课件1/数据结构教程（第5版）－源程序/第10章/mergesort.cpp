//自底向上的二路归并排序算法
#include <malloc.h>
#include "seqlist.cpp"

void Merge(RecType R[],int low,int mid,int high) 
{
	RecType *R1;
	int i=low,j=mid+1,k=0; //k是R1的下标,i、j分别为第1、2段的下标
	R1=(RecType *)malloc((high-low+1)*sizeof(RecType));  //动态分配空间
	while (i<=mid && j<=high)     	//在第1段和第2段均未扫描完时循环
		if (R[i].key<=R[j].key)    	//将第1段中的记录放入R1中
		{
			R1[k]=R[i];
			i++;k++; 
		}
		else                       		//将第2段中的记录放入R1中
		{
			R1[k]=R[j];
			j++;k++; 
		}
	while (i<=mid)          	       	//将第1段余下部分复制到R1
	{ 
		R1[k]=R[i];
		i++;k++; 
	}
    while (j<=high)                	//将第2段余下部分复制到R1
	{
		R1[k]=R[j];
		j++;k++;  
	}
    for (k=0,i=low;i<=high;k++,i++) //将R1复制回R中
	    R[i]=R1[k];
} 
void MergePass(RecType R[],int length,int n)	//对整个数序进行一趟归并
{
	int i;
	for (i=0;i+2*length-1<n;i=i+2*length) 	//归并length长的两相邻子表
		Merge(R,i,i+length-1,i+2*length-1);
	if (i+length-1<n-1)                		//余下两个子表,后者长度小于length
		Merge(R,i,i+length-1,n-1);  		//归并这两个子表
	printf("length=%d: ",length);
	DispList(R,n);
}
void MergeSort(RecType R[],int n)			//自底向上的二路归并算法
{
	int length;
	for (length=1;length<n;length=2*length)//进行log2n趟归并
		MergePass(R,length,n);
}
int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	CreateList(R,a,n);
	printf("   排序前:"); DispList(R,n);
	MergeSort(R,n);
	printf("   排序后:"); DispList(R,n);
	return 1;
}


