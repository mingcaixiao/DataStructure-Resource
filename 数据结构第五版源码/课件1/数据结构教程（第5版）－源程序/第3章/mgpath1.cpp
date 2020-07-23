//用队列求解迷宫问题
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
#define M 8
#define N 8
int mg[M+2][N+2]=
{	
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};
//----------------------------------------------------------
//-非环形队列的基本运算算法---------------------------------
//----------------------------------------------------------
typedef struct 
{	int i,j;						//方块的位置
	int pre;						//本路径中上一方块在队列中的下标
} Box;								//方块类型
typedef struct
{
	Box data[MaxSize];
	int front,rear;					//队头指针和队尾指针
} QuType;							//顺序队类型


void InitQueue(QuType *&q)			//初始化队列
{	q=(QuType *)malloc (sizeof(QuType));
	q->front=q->rear=-1;
}
void DestroyQueue(QuType *&q)		//销毁队列
{
	free(q);
}
bool QueueEmpty(QuType *q)			//判断队列是否为空
{
	return(q->front==q->rear);
}
bool enQueue(QuType *&q,Box e)		//进队列
{	if (q->rear==MaxSize-1)			//队满上溢出
		return false;				//返回假
	q->rear++;						//队尾增1
	q->data[q->rear]=e;				//rear位置插入元素e
	return true;					//返回真
}
bool deQueue(QuType *&q,Box &e)	//出队列
{	if (q->front==q->rear)			//队空下溢出
		return false;
	q->front++;
	e=q->data[q->front];
	return true;
}
//----------------------------------------------------------

void print(QuType *qu,int front)	//从队列qu中输出路径
{
	int k=front,j,ns=0;
	printf("\n");
	do				//反向找到最短路径,将该路径上的方块的pre成员设置成-1
	{	j=k;
		k=qu->data[k].pre;
		qu->data[j].pre=-1;
	} while (k!=0);
	printf("一条迷宫路径如下:\n");
	k=0;
	while (k<MaxSize)  //正向搜索到pre为-1的方块,即构成正向的路径
	{	if (qu->data[k].pre==-1)
		{	ns++;
			printf("\t(%d,%d)",qu->data[k].i,qu->data[k].j);
			if (ns%5==0) printf("\n");	//每输出每5个方块后换一行
		}
		k++;
	}
	printf("\n");
}
bool mgpath1(int xi,int yi,int xe,int ye)	//搜索路径为:(xi,yi)->(xe,ye)
{
	Box e;
	int i,j,di,i1,j1;
	QuType *qu;						//定义顺序队指针qu
	InitQueue(qu);					//初始化队列qu
	e.i=xi; e.j=yi; e.pre=-1;
	enQueue(qu,e);					//(xi,yi)进队
	mg[xi][yi]=-1;					//将其赋值-1,以避免回过来重复搜索
	while (!QueueEmpty(qu))			//队不空且循环
	{	
		deQueue(qu,e);				//出队方块e,由于不是环形队列，该出队元素仍在队列中
		i=e.i; j=e.j;
		if (i==xe && j==ye)			//找到了出口,输出路径
		{	
			print(qu,qu->front);	//调用print函数输出路径
			DestroyQueue(qu);		//销毁队列
			return true;			//找到一条路径时返回真
		}
		for (di=0;di<4;di++)		//循环扫描每个方位,把每个可走的方块插入队列中
		{	
			switch(di)
			{
			case 0:i1=i-1; j1=j;   break;
			case 1:i1=i;   j1=j+1; break;
			case 2:i1=i+1; j1=j;   break;
			case 3:i1=i;   j1=j-1; break;
			}
			if (mg[i1][j1]==0)
			{
				e.i=i1; e.j=j1; 
				e.pre=qu->front;	//指向路径中上一个方块的下标
				enQueue(qu,e);		//(i1,j1)方块进队
				mg[i1][j1]=-1;		//将其赋值-1,以避免回过来重复搜索
			}
		}
     }
	DestroyQueue(qu);			//销毁队列
	return false;				//未找到任何路径时返回假
}
int main()
{
	mgpath1(1,1,M,N);
	return 1;
}