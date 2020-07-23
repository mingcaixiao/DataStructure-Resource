//ÎÄ¼şÃû£ºexp1-4.cpp
#include <stdio.h>
long Sum(int n)
{
	long sum=0,fact=1;
	for (int i=1;i<=n;i++)
	{
		fact*=i;
		sum+=fact;
	}
	return sum;
}
//------------------------------------------------------------
int main()
{
	int n;
	printf("n(3-20):");
	scanf("%d",&n);
	if (n<3 || n>20) return 0;
	printf("1!+2!+¡­+%d!=%ld\n",n,Sum(n));
	return 1;
}
