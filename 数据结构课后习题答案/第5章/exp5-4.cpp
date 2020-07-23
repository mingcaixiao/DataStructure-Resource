//文件名:exp5-4.cpp
#include <stdio.h>
double expx(double x,int n)
{
	if (n==1)
		return x;
	else if (n%2==0)		//当n为大于1的偶数时
		return expx(x,n/2)*expx(x,n/2);
	else					//当n为大于1的奇数时
		return x*expx(x,(n-1)/2)*expx(x,(n-1)/2);
}
int main()
{
	double x;
	int n;
	printf("x:"); scanf("%lf",&x);
	printf("n:"); scanf("%d",&n);
	printf("%g的%d次方:%g\n",x,n,expx(x,n));
	return 1;
}
