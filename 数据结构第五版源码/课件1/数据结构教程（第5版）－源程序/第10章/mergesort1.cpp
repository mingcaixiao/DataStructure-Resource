//自顶向下的二路归并排序算法
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
void MergeSortDC(RecType R[],int low,int high)
//对R[low..high]进行二路归并排序
{
	int mid;
	if (low<high)
	{	mid=(low+high)/2;
		MergeSortDC(R,low,mid);
		MergeSortDC(R,mid+1,high);
		Merge(R,low,mid,high);		
	}
}
void MergeSort1(RecType R[],int n)	//自顶向下的二路归并算法
{
	MergeSortDC(R,0,n-1);
}

int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={9,8,7,6,5,4,3,2,1,0};
	CreateList(R,a,n);
	printf("排序前:"); DispList(R,n);
	MergeSort1(R,n);
	printf("排序后:"); DispList(R,n);
	return 1;

}


