//【例1.5】的算法:求一元二次方程的根
#include <stdio.h>
#include <math.h>
int solution(double a,double b,double c,double &x1,double &x2) 
{	
	double d;
	d=b*b-4*a*c;
	if (d>0)
	{	x1=(-b+sqrt(d))/(2*a);
		x2=(-b-sqrt(d))/(2*a);
		return 2;			//2个实根 
	}
	else if (d==0)
	{	x1=(-b)/(2*a);
		return 1;	 		//1个实根 
	} 
	else					//d<0的情况
		return 0;			//不存在实根
}
int main()
{
	double a=2,b=-6,c=3;
	double x1,x2;
	int s=solution(a,b,c,x1,x2);
	if (s==1)
		printf("一个根：x=%lf\n",x1);
	else if (s==2)
		printf("两个根：x1=%lf,x2=%lf\n",x1,x2);
	else
	printf("没有根\n");
	return 1;
}
