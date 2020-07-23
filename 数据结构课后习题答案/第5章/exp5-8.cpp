//文件名:exp5-8.cpp
#include <stdio.h>
#define MAXN 20					//最多物品数
int maxv; 						//存放最优解的总价值
int maxw;						//存放最优解的总重量
int x[MAXN];					//存放最终解
int W=7;  						//限制的总重量
int	n=4;						//物品种数
int w[]={5,3,2,1};				//物品重量
int v[]={4,4,3,1};				//物品价值

void knap(int i,int tw,int tv,int op[]) //考虑第i个物品
{	int j;
	if (i>=n)					//递归出口：所有物品都考虑过
	{	if (tw<=W && tv>maxv)	//找到一个满足条件的更优解,保存它
		{	maxv=tv;
			maxw=tw;
			for (j=1;j<=n;j++)
				x[j]=op[j];
		}
	}
	else						//尚未找完所有物品
	{	op[i]=1;				//选取第i个物品
		knap(i+1,tw+w[i],tv+v[i],op);
		op[i]=0;				//不选取第i个物品,回溯
		knap(i+1,tw,tv,op);
	}
}
void dispasolution(int x[],int n)//输出一个解
{	int i;
	printf("最佳装填方案是:\n");
	for (i=1;i<=n;i++)
		if (x[i]==1)
			printf("  选取第%d个物品\n",i);
	printf("总重量=%d,总价值=%d\n",maxw,maxv);
}
int main()
{
	int op[MAXN];				//存放临时解
	knap(0,0,0,op);
	dispasolution(x,n);
	return 1;
}
