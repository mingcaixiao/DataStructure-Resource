//【例5.2】的算法：求实数数组A[0..n-1]中的最小值
#include <stdio.h>
double Min(double A[],int i)
{	double min;
	if (i==0) return A[0];
	else
	{	min=Min(A,i-1);
		if (min>A[i]) return(A[i]);
		else return(min);
	}
}
int main()
{
	double a[]={9.2,5.5,3.8,7.1,6.5};
	int n=5;
	printf("Min=%lf\n",Min(a,4));
	return 1;
}