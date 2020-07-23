//顺序查找算法
#include "seqlist.cpp"

int SeqSearch(RecType R[],int n,KeyType k)
{
    int i=0;
    while (i<n && R[i].key!=k)	//从表头往后找
		i++;
    if (i>=n) 
		return 0;
    else 
		return i+1;
}

int SeqSearch1(RecType R[],int n,KeyType k)
{
	int i=0;
	R[n].key=k;
	while (R[i].key!=k)	//从表头往后找
		i++;
	if (i==n)				//未找到返回0
		return 0;
	else 
		return i+1;			//找到返回逻辑序号i+1
}

int main()
{
	int n=10;
	RecType R[MAXL];
	KeyType a[]={2,3,1,8,5,4,9,0,7,6},k=9;
	CreateList(R,a,n);
	printf("查找表："); DispList(R,n);
	printf("R[%d]=%d\n",SeqSearch(R,n,k),k);
	return 1;
}
