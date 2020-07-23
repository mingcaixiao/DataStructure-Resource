//文件名：exp1-1.cpp
#include <stdio.h>
#include <time.h>		 	//clock_t, clock, CLOCKS_PER_SEC
#include <math.h>

//------方法1-----------------------------------------------
long add1(long n)			//方法1：求1+2+...+n
{
	long i,sum=0;
	for (i=1;i<=n;i++)
		sum+=i;
	return sum;
}

void AddTime1(long n)		//采用方法1的耗时统计
{
	clock_t t;
	long sum;
	t=clock();
	sum=add1(n);
	t=clock()-t;
	printf("方法1:\n");
	printf("  结果:1～%d之和:%ld\n",n,sum);
	printf("  用时:%lf秒\n" ,((float)t)/CLOCKS_PER_SEC);
}

//------方法2-----------------------------------------------
long add2(long n)			//方法2：求1+2+...+n
{
	return n*(n+1)/2;
}
void AddTime2(long n)		//采用方法2的耗时统计
{
	clock_t t;
	long sum;
	t=clock();
	sum=add2(n);
	t=clock()-t;
	printf("方法2:\n");
	printf("  结果:1～%d之和:%ld\n",n,sum);
	printf("  用时:%lf秒\n" ,((float)t)/CLOCKS_PER_SEC);
}
//------------------------------------------------------------
int main()
{
	int n;
	printf("n(大于1000000):");
	scanf("%d",&n);
	if (n<1000000) return 0;
	AddTime1(n);
	AddTime2(n);
	return 1;
}
