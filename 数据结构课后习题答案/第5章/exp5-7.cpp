//文件名:exp5-7.cpp
#include <stdio.h>
#include <stdlib.h>
const int N=20;      	//最多皇后个数
int q[N];            	//存放各皇后所在的列号
int count=0;          	//存放解个数
void print(int n)    	//输出一个解
{
	count++;
	int i;
	printf("  第%d个解：",count);
	for (i=1;i<=n;i++)
		printf("(%d,%d) ",i,q[i]);
	printf("\n");
}
bool place(int k,int j)			//测试(k,j)位置能否摆放皇后
{
	int i=1;
	while (i<k)       			//i=1～k-1是已放置了皇后的行
	{
	    if ((q[i]==j) || (abs(q[i]-j)==abs(i-k)))
		    return false;		//有冲突时返回假
	    i++;
	}
	return true;				//没有冲突时返回真
}
void queen(int k,int n)			//放置1～k的皇后
{
	int j;
	if (k>n) 
		print(n);         		//所有皇后放置结束
	else
		for (j=1;j<=n;j++) 		//在第k行上穷举每一个位置
		    if (place(k,j))		//在第k行上找到一个合适位置(k,j)
			{
				q[k]=j;
				queen(k+1,n);
     		}
}
int main()
{
	int n;     					//n存放实际皇后个数
	printf(" 皇后问题(n<20) n:");
	scanf("%d",&n);
	if (n>20)
		printf("n值太大,不能求解\n");
	else
	{
		printf(" %d皇后问题求解如下：\n",n);
		queen(1,n);
		printf("\n");
    }
	return 1;
}
