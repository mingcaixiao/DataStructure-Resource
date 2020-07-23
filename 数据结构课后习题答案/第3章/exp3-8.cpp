//文件名:exap3-8.cpp
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
typedef struct
{	int col[MaxSize];					//col[i]存放第i个皇后的列号
	int top;							//栈顶指针
} StackType;							//声明顺序栈类型
void dispasolution(StackType St)   		//输出一个解
{	static int count=0;					//静态变量用于统计解个数
	printf("  第%d个解:",++count);
	for (int i=1;i<=St.top;i++)
		printf("(%d,%d) ",i,St.col[i]);
	printf("\n");
}
bool place(StackType St,int k,int j)	//测试(k,j)是否与1～k-1的皇后有冲突
{	int i=1;
	if (k==1) return true;				//放第一个皇后时没有冲突
	while (i<=k-1)						//测试与前面已放置的皇后是否有冲突
	{	if ((St.col[i]==j) || (abs(j-St.col[i])==abs(i-k)))
			return false;				//有冲突时返回假
		i++;
	}
	return true;						//没有冲突时返回真
}
void queen(int n)						//求解n皇后问题
{
	int k;
	bool find;
	StackType St;						//定义栈st
	St.top=0;							//初始化栈顶指针,为了让皇后从第1行开始,不用下标0
	St.top++; St.col[St.top]=0;			//col[1]=0,表示从第1个皇后开始,初始列号为0
	while (St.top!=0)					//栈不空时循环
	{	k=St.top;						//试探栈顶的第k个皇后
		find=false;						//尚未找到第k个皇后的位置,find设置为假
		for (int j=St.col[k]+1;j<=n;j++)//为第k个皇后的找一个合适的列号
			if (place(St,k,j))			//在第k行找到一个放皇后的位置(k,j)
			{	St.col[St.top]=j;		//修改第k个皇后的位置(新列号)
				find=true;				//找到第k个皇后的位置,find设置为真
				break;					//找到后退出for循环
			}
		if (find)						//在第k行找到一个放皇后的位置(k,j)
		{	if (k==n)					//若所有皇后均放好,输出一个解
				dispasolution(St);
			else						//还有皇后未放时,将第k+1个皇后进栈
			{	St.top++;
				St.col[St.top]=0;		//新进栈的皇后从第0列开始试探起
			}
		}
		else							//若第k个皇后没有合适位置,回溯
			St.top--;					//即将第k个皇后退栈
	}
}
int main()
{	int n;								//n存放实际皇后个数
	printf("皇后问题(n<20) n=");
	scanf("%d",&n);
	if (n>20)
		printf("n值太大\n");
	else
	{	printf(" %d皇后问题求解如下：\n",n);
		queen(n);
	}
	return 1;
}
