//文件名:exp3-9.cpp
#include <stdio.h>
#include <malloc.h>
#define N 3					//停车场内最多的停车数
#define M 4					//候车场内最多的停车数
#define Price 2				//每单位停车费用
typedef struct 
{
	int CarNo[N];			//车牌号
	int CarTime[N];			//进场时间
	int top;				//栈指针
} SqStack;					//声明顺序栈类型
typedef struct 
{
	int CarNo[M];			//车牌号
	int front,rear;			//队首和队尾指针
} SqQueue;					//声明环形队列类型

//以下为栈的运算算法
void InitStack(SqStack *&s)	 //初始化栈
{
	s=(SqStack *)malloc(sizeof(SqStack));
	s->top=-1;
}
bool StackEmpty(SqStack *s)	//判断栈空
{
	return(s->top==-1);
}
bool StackFull(SqStack *s)	//判断栈满
{
	return(s->top==N-1);
}
bool Push(SqStack *&s,int e1,int e2)  //进栈
{
	if (s->top==N-1)
		return false;
	s->top++;
	s->CarNo[s->top]=e1;
	s->CarTime[s->top]=e2;
	return true;
}
bool Pop(SqStack *&s,int &e1,int &e2)  //出栈
{
	if (s->top==-1)
		return false;
	e1=s->CarNo[s->top];
	e2=s->CarTime[s->top];
	s->top--;
	return true;
}
void DispStack(SqStack *s)	 //显示栈中元素
{
	for (int i=s->top;i>=0;i--)
		printf("%d ",s->CarNo[i]);
	printf("\n");
}

//以下为队列的运算算法
void InitQueue(SqQueue *&q)		//初始化队
{
	q=(SqQueue *)malloc (sizeof(SqQueue));
	q->front=q->rear=0;
}
bool QueueEmpty(SqQueue *q)		//判断队空
{
	return(q->front==q->rear);
}
bool QueueFull(SqQueue *q)			//判断队满
{
	return ((q->rear+1)%M==q->front);
}
bool enQueue(SqQueue *&q,int e)		//进队
{
	if ((q->rear+1)%M==q->front)	//队满
		return false;
	q->rear=(q->rear+1)%M;
	q->CarNo[q->rear]=e;
	return true;
}
bool deQueue(SqQueue *&q,int &e)	//出队
{
	if (q->front==q->rear)			//队空的情况
		return false;
	q->front=(q->front+1)%M;
	e=q->CarNo[q->front];
	return true;
}
void DispQueue(SqQueue *q)	 //显示队中元素
{
	int i=(q->front+1)%M;
	printf("%d ",q->CarNo[i]);
	while ((q->rear-i+M)%M>0) 
	{
		i=(i+1)%M;
		printf("%d ",q->CarNo[i]);
	} 
	printf("\n");
}
int main()
{
	int comm,i,j;
	int no,e1,time,e2;
	SqStack *St,*St1;
	SqQueue *Qu;
	InitStack(St);
	InitStack(St1);
	InitQueue(Qu);
	do
	{
		printf(">输入指令(1:到达 2:离开 3:停车场 4:候车场 0:退出):");
		scanf("%d",&comm);
		switch(comm)
		{
		case 1:		//汽车到达
			printf("  车号 到达时间:");
			scanf("%d%d",&no,&time);
			if (!StackFull(St))			//停车场不满
			{
				Push(St,no,time);
				printf("  停车场位置:%d\n",St->top+1);
			}
			else						//停车场满
			{
				if (!QueueFull(Qu))		//候车场不满
				{
					enQueue(Qu,no);
					printf("  候车场位置:%d\n",Qu->rear);
				}
				else
					printf("  候车场已满,不能停车\n");
			}
			break;
		case 2:		//汽车离开
			printf("  车号 离开时间:");
			scanf("%d%d",&no,&time);
			for (i=0;i<=St->top && St->CarNo[i]!=no;i++);
			if (i>St->top)
				printf("  未找到该编号的汽车\n");
			else
			{
				for (j=i;j<=St->top;j++)
				{
					Pop(St,e1,e2);
					Push(St1,e1,e2);		//倒车到临时栈St1中
				}
				Pop(St,e1,e2);				//该汽车离开
				printf("  %d汽车停车费用:%d\n",no,(time-e2)*Price);
				while (!StackEmpty(St1))	//将临时栈St1重新回到St中
				{
					Pop(St1,e1,e2);
					Push(St,e1,e2);
				}
				if (!QueueEmpty(Qu))		//队不空时,将队头进栈St
				{
					deQueue(Qu,e1);
					Push(St,e1,time);		//以当前时间开始计费
				}
			}
			break;
		case 3:		//显示停车场情况
			if (!StackEmpty(St))
			{
				printf("  停车场中的车辆:");	//输出停车场中的车辆
				DispStack(St);
			}
			else
				printf("  停车场中无车辆\n");	
			break;
		case 4:		//显示候车场情况
			if (!QueueEmpty(Qu))
			{
				printf("  候车场中的车辆:");	//输出候车场中的车辆
				DispQueue(Qu);
			}
			else
				printf("  候车场中无车辆\n");	
			break;
		case 0:		//结束
			if (!StackEmpty(St))
			{
				printf("  停车场中的车辆:");	//输出停车场中的车辆
				DispStack(St);
			}
			if (!QueueEmpty(Qu))
			{
				printf("  候车场中的车辆:");	//输出候车场中的车辆
				DispQueue(Qu);
			}
			break;
		default:	//其他情况
			printf("  输入的命令错误\n");
			break;
		} 
	} while(comm!=0);
	return 1;
}
