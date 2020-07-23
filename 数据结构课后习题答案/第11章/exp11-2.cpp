//文件名:exp11-2.cpp
#include <stdio.h>
#define MaxSize 100
#define MAXKEY 32767		//最大关键字值∞
#define K 5					//内存工作区可容纳的记录个数
typedef int KeyType;		//关键字类型
typedef struct
{	KeyType recs[MaxSize];	//存放文件中的数据项
	int length;				//存放文件中实际记录个数
	int currec;				//存放当前位置
} FileType;					//文件类型
FileType Fi;				//定义输入文件,为全局变量
KeyType R[K+1];				//存放大根堆
void initial()				//输入文件初始化
{	int n=18,i;
	KeyType a[]={15,4,97,64,17,32,108,44,76,9,39,82,56,31,80,73,255,68};
	for (i=0;i<n;i++)		//将n个记录存放到输入文件中
		Fi.recs[i]=a[i];
	Fi.length=n; 			//输入文件中有n个记录
	Fi.currec=-1;			//输入文件中当前位置为-1
}
bool GetaRec(KeyType &r)	//从输入文件中取一个记录r	
{
	Fi.currec++;
	if (Fi.currec==Fi.length)
		return false;
	else
	{
		r=Fi.recs[Fi.currec];
		return true;
	}
}
void sift(int low,int high)			//筛选为大根堆算法
{
	int i=low,j=2*i;     			//R[j]是R[i]的左孩子
	KeyType tmp=R[i];
	while (j<=high) 
	{
		if (j<high && R[j]<R[j+1]) 	//若右孩子较大,把j指向右孩子
			j++;    				//变为2i+1
		if (tmp<R[j]) 
		{
			R[i]=R[j];              //将R[j]调整到双亲结点位置上
			i=j;                    //修改i和j值,以便继续向下筛选
			j=2*i;
		}
		else break;                 //筛选结束
	}
	R[i]=tmp;                      	//被筛选结点的值放入最终位置
}
void dispHeap()						//显示堆中所有记录
{
	for (int i=1;i<=K;i++)
		printf("%d ",R[i]);
	printf("\n");
}
void SelectK()				//从输入文件Fi中挑选K个最小的记录
{
	int i;
	KeyType r;
	for (i=0;i<K;i++)		//从输入文件Fi中取出K个记录放在R[1..K]中
	{
		GetaRec(r);
		R[i+1]=r;
	}
	for (i=K/2;i>=1;i--)	//建立初始堆
		sift(i,K);
	printf("开头%d个记录创建的大根堆:",K); dispHeap();
	while (GetaRec(r))		//从输入文件Fi中取出其余的记录
	{
		printf("  处理%d:",r);
		if (r<R[1])			//若r小于堆的根节点
		{
			R[1]=r;			//用r替代堆的根节点
			sift(1,K);		//继续筛选
			printf("\t需要筛选，结果:"); dispHeap();
		}
		else
			printf("\t不需要筛选\n");
	}
}
int main()
{
	initial();
	SelectK();
	printf("最终结果: "); dispHeap();
	return 1;
}
	
