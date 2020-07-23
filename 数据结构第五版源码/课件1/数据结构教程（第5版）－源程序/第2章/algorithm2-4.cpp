//【例2.4】的算法:将整数顺序表L以第一个元素为分界线（基准）进行划分
#include "sqlist.cpp"  
void swap(int &x,int &y)				//交换x和y
{	int tmp=x;
	x=y; y=tmp;
}
void move1(SqList *&L)
{	int i=0,j=L->length-1;
	ElemType pivot=L->data[0];			//以data[0]为基准
	while (i<j)						//从区间两端交替向中间扫描,直至i=j为止
	{	while (i<j && L->data[j]>pivot)
			j--;						//从右向左扫描,找一个小于等于pivot的元素
		while (i<j && L->data[i]<=pivot)
			i++;						//从左向右扫描,找一个大于pivot的元素
		if (i<j)
			swap(L->data[i],L->data[j]);//将L->data[i]和L->data[j]进行交换
	}
	swap(L->data[0],L->data[i]);		//将L->data[0]和L->data[i]进行交换
}

void move2(SqList *&L)
{	int i=0,j=L->length-1;
	ElemType pivot=L->data[0];	//以data[0]为基准
	while (i<j)  				//从顺序表两端交替向中间扫描,直至i=j为止
	{	while (j>i && L->data[j]>pivot)
			j--;				//从右向左扫描,找一个小于等于pivot的data[j]
		L->data[i]=L->data[j];	//找到这样的data[j],放入data[i]处
		while (i<j && L->data[i]<=pivot)
			i++;				//从左向右扫描,找一个大于pivot的记录data[i]
		L->data[j]=L->data[i];	//找到这样的data[i],放入data[j]处
	}
	L->data[i]=pivot;
	printf("i=%d\n",i);
}

int main()
{
	SqList *L;
	ElemType a[]={1,9,8,7,6};
	CreateList(L,a,5);
	printf("L:");DispList(L);
	printf("执行移动运算\n");
	move1(L);
	printf("L:");DispList(L);
	DestroyList(L);
	return 1;
}
