//【例2.5】的算法:将整数顺序表L中所有奇数移动到偶数的前面
#include "sqlist.cpp"  
void swap(int &x,int &y)				//交换x和y
{	int tmp=x;
	x=y; y=tmp;
}
void move1(SqList *&L)
{
	int i=0,j=L->length-1;
	while (i<j)
	{
		while (i<j && L->data[j]%2==0)
			j--;					//从右向左扫描,找一个奇数元素
		while (i<j && L->data[i]%2==1)
			i++;					//从左向右扫描,找一个偶数元素
		if (i<j)					//若i<j，将L->data[i]和L->data[j]交换
			swap(L->data[i],L->data[j]);
	}
}
void move2(SqList *&L)
{	int i=-1,j;
	for (j=0;j<=L->length-1;j++)
		if (L->data[j]%2==1)		//j指向奇数时
		{
			i++;					//奇数区间个数增1
			if (i!=j)				//若i、j不相等
				swap(L->data[i],L->data[j]);//L->data[i]和L->data[j]交换
		}
}

int main()
{
	SqList *L;
	ElemType a[]={8,2,7,1,5,10,4,6,3,9};
	CreateList(L,a,10);
	printf("L:");DispList(L);
	printf("执行移动运算\n");
	move1(L);
	printf("L:");DispList(L);
	DestroyList(L);
	return 1;
}
