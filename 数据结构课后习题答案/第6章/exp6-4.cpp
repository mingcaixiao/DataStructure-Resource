//文件名:exp6-4.cpp
#include <stdio.h>
#define M 4
#define N 4
void MinMax(int A[M][N])
{	int i,j;
	bool have=false;
	int min[M],max[N];
	for (i=0;i<M;i++)		//计算出每行的最小值元素,放入min[0..M-1]之中
	{
		min[i]=A[i][0];
		for (j=1;j<N;j++)
			if (A[i][j]<min[i])
				min[i]=A[i][j];
	}
	for (j=0;j<N;j++)		//计算出每列的最大值元素,放入max[0..N-1]之中
	{	max[j]=A[0][j];
		for (i=1;i<M;i++)
			if (A[i][j]>max[j]) 
				max[j]=A[i][j];
	}
	for (i=0;i<M;i++)		//判定是否为马鞍点
		for (j=0;j<N;j++)
			if (min[i]==max[j])
			{	printf("  A[%d][%d]=%d\n",i,j,A[i][j]);	//显示马鞍点
				have=true;
			}
	if (!have)
		printf("没有鞍点\n");
}
int main()
{	int i,j;
	int A[M][N]={{9, 7, 6, 8},{20,26,22,25},{28,36,25,30},{12,4, 2, 6}};
	printf("A矩阵:\n");
	for (i=0;i<M;i++)
	{	for (j=0;j<N;j++)
			printf("%4d",A[i][j]);
		printf("\n");
	}
	printf("A矩阵中的马鞍点:\n");
	MinMax(A);			//调用MinMax()找马鞍点
	return 1;
}
