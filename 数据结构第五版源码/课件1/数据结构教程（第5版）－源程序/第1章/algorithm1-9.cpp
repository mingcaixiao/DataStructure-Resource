//【例1.9】的算法:分析递归算法的时间复杂度
#include <stdio.h>
void fun(int a[],int n,int k)		//数组a共有n个元素,执行时间为T1(n,k)
{
	int i;
	if (k==n-1)
	{
		for (i=0;i<n;i++)
			printf("%d\n",a[i]);	//该语句执行次数为n
	}
	else
	{	
		for (i=k;i<n;i++)
			a[i]=a[i]+i*i;			//该语句执行次数为n-k
		fun(a,n,k+1);				//执行时间为T1(n,k+1)
	}
}
int main()
{
	int a[10]={0};
	fun(a,10,0);
	return 1;
}