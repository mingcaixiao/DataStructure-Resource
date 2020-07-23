//文件名:exp9-3.cpp
#include "seqlist.cpp"				//包含顺序表基本运算算法
#define MAXI 20						//定义索引表的最大长度
typedef struct 
{	
	KeyType key;					//KeyType为关键字的类型
	int link;						//指向分块的起始下标
} IdxType;							//索引表元素类型

int IdxSearch(IdxType I[],int b,RecType R[],int n,KeyType k) //分块查找
{
	int s=(n+b-1)/b;			//s为每块的元素个数，应为n/b取上界
	int count1=0,count2=0;
	int low=0,high=b-1,mid,i;
	printf("(1)在索引表中折半查找\n");
	while (low<=high)			//在索引表中进行折半查找，找到的位置为high+1
	{
		mid=(low+high)/2;
		printf("  第%d次比较:在[%d,%d]中比较元素R[%d]:%d\n",count1+1,low,high,mid,R[mid].key);
		if (I[mid].key>=k)
			high=mid-1;
		else 
			low=mid+1;
		count1++;				//count1累计在索引表中的比较次数
	}
	printf("比较%d次,在第%d块中查找元素%d\n",count1,low,k);
	//应在索引表的high+1块中，再在主数据表中进行顺序查找
	i=I[high+1].link;			//找到对应的块
	printf("(2)在对应块中顺序查找:\n    ");
	while (i<=I[high+1].link+s-1)
	{	printf("%d ",R[i].key);
		count2++;				//count2累计在顺序表对应块中的比较次数
		if (R[i].key==k) break;
		i++;
	}
	printf("比较%d次,在顺序表中查找元素%d\n",count2,k);
	if (i<=I[high+1].link+s-1)
		return i+1;			//查找成功，返回该元素的逻辑序号
	else
		return 0;			//查找失败，返回0
}

int main()
{
	RecType R[MAXL];
	IdxType I[MAXI];
	int n=25, i;
	int a[]={8,14,6,9,10,22,34,18,19,31,40,38,54,66,46,71,78,68,80,85,100,94,88,96,87};
	CreateList(R,a,n);				//建立顺序表
	I[0].key=14;I[0].link=0;		//建立索引表
	I[1].key=34;I[1].link=4;
	I[2].key=66;I[2].link=10;
	I[3].key=85;I[3].link=15;
	I[4].key=100;I[4].link=20;
	printf("关键字序列:");
	for (i=0;i<n;i++)
	{
		printf("%4d",R[i].key);
		if (((i+1)%5)==0) printf("   ");
		if (((i+1)%10)==0) printf("\n\t   ");
	}
	printf("\n");
	KeyType k=46;
	printf("查找%d的比较过程如下:\n",k);

	if ((i=IdxSearch(I,5,R,25,k))!=-1)
		printf("元素%d的位置是%d\n",k,i);
	else
		printf("元素%d不在表中\n",k);
	return 1;
}
