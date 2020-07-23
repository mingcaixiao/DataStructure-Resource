//【例2.17】的算法：求两个等长的有序顺序表的中位数。
#include "sqlist.cpp"
ElemType M_Search(SqList *A, SqList *B)	//A、B的长度相同
{	int i=0, j=0, k=0;
	while (i<A->length && j<B->length)	//两个序列均没有扫描完
	{	k++;							//当前归并的元素个数增1
		if (A->data[i]<B->data[j])		//归并较小的元素A->data[i]
		{	if (k==A->length)			//若当前归并的元素是第n个元素
				return A->data[i];		//返回A->data[i]
			i++;
		}
		else							//归并较小的元素B->data[j]
		{	if (k==B->length)			//若当前归并的元素是第n个元素
				return B->data[j];		//返回B->data[j]
			j++; 
		}
	}
}

int main()
{
	SqList *L1,*L2;
	int n=5;
	ElemType a[]={11,13,15,17,19};
	ElemType b[]={2,4,6,8,20};
	CreateList(L1,a,n);
	CreateList(L2,b,n);
	printf("L1:"); DispList(L1);
	printf("L2:"); DispList(L2);
	printf("L1,L2的中位数:%d\n",M_Search(L1,L2));
	DestroyList(L1);
	DestroyList(L2);
	return 1;
}
