//文件名:exp9-1.cpp
#include "seqlist.cpp"						//包含顺序表基本运算算法
int SeqSearch(RecType R[],int n,KeyType k)	//顺序查找算法
{
    int i=0;
    while (i<n && R[i].key!=k) 
	{
		printf("%d ",R[i].key);
		i++;					//从表头往后找
	}
    if (i>=n) 
		return 0;
    else 
	{
		printf("%d",R[i].key);
		return i+1;
	}
}
int main()
{
	RecType R[MAXL];
	int n=10,i;
	KeyType k=5;
	int a[]={3,6,2,10,1,8,5,7,4,9};
	CreateList(R,a,n);			//建立顺序表
	printf("关键字序列:"); DispList(R,n);
	printf("查找%d所比较的关键字:\n\t",k);
	if ((i=SeqSearch(R,n,k))!=0)
		printf("\n元素%d的位置是%d\n",k,i);
	else
		printf("\n元素%d不在表中\n",k);
	return 1;
}
