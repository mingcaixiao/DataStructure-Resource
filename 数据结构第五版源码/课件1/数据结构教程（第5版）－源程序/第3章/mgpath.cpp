//用栈求解迷宫问题
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
//---------------------------------------------------------
//--迷宫栈基本运算---------------------------------------
//---------------------------------------------------------
typedef struct
{
	int i;				//当前方块的行号
	int j;				//当前方块的列号
	int di;				//di是下一可走相邻方位的方位号
} Box;
typedef struct
{
	Box data[MaxSize];	//存放方块
    int top;			//栈顶指针
} StType;				//定义栈类型

void InitStack(StType *&s)		//初始化栈
{	s=(StType *)malloc(sizeof(StType));
	s->top=-1;
}
void DestroyStack(StType *&s)	//销毁栈
{
	free(s);
}
bool StackEmpty(StType *s)		//判断栈是否为空
{
	return(s->top==-1);
}
bool Push(StType *&s,Box e)	//进栈元素e
{
	if (s->top==MaxSize-1)
		return false;
	s->top++;
	s->data[s->top]=e;
	return true;
}
bool Pop(StType *&s,Box &e)	//出栈元素e
{
	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	s->top--;
	return true;
}
bool GetTop(StType *s,Box &e)	//取栈顶元素e
{
	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	return true;
}
//---------------------------------------------------------
bool mgpath(int xi,int yi,int xe,int ye)	//求解路径为:(xi,yi)->(xe,ye)
{
	Box path[MaxSize], e;
	int i,j,di,i1,j1,k;
	bool find;
	StType *st;								//定义栈st
	InitStack(st);							//初始化栈顶指针
	e.i=xi; e.j=yi;	e.di=-1;				//设置e为入口
	Push(st,e);								//方块e进栈
	mg[xi][yi]=-1;							//入口的迷宫值置为-1避免重复走到该方块
	while (!StackEmpty(st))					//栈不空时循环
	{
		GetTop(st,e);						//取栈顶方块e
		i=e.i; j=e.j; di=e.di;
		if (i==xe && j==ye)					//找到了出口,输出该路径
		{ 
			printf("一条迷宫路径如下:\n");
			k=0;
			while (!StackEmpty(st))
			{
				Pop(st,e);					//出栈方块e
				path[k++]=e;				//将e添加到path数组中
			}
			while (k>=1)
			{
				k--;
				printf("\t(%d,%d)",path[k].i,path[k].j);
				if ((k+2)%5==0)				//每输出每5个方块后换一行
					printf("\n");  
			}
			printf("\n");
			DestroyStack(st);				//销毁栈
			return true;					//输出一条迷宫路径后返回true
		}
		find=false;
		while (di<4 && !find)				//找相邻可走方块(i1,j1)
		{	
			di++;
			switch(di)
			{
			case 0:i1=i-1; j1=j;   break;
			case 1:i1=i;   j1=j+1; break;
			case 2:i1=i+1; j1=j;   break;
			case 3:i1=i;   j1=j-1; break;
			}
			if (mg[i1][j1]==0) find=true;	//找到一个相邻可走方块，设置find我真
		}
		if (find)							//找到了一个相邻可走方块(i1,j1)
		{	

			st->data[st->top].di=di;		//修改原栈顶元素的di值
			e.i=i1; e.j=j1; e.di=-1;
			Push(st,e);						//相邻可走方块e进栈
			mg[i1][j1]=-1;					//(i1,j1)的迷宫值置为-1避免重复走到该方块
		}
		else								//没有路径可走,则退栈
		{	
			Pop(st,e);						//将栈顶方块退栈
			mg[e.i][e.j]=0;					//让退栈方块的位置变为其他路径可走方块
		}
	}
	DestroyStack(st);						//销毁栈
	return false;							//表示没有可走路径,返回false
}
int main()
{
	mgpath(1,1,M,N);
	return 1;
}