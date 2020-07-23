//文件名:exp5-2.cpp
#include <stdio.h>
#define MaxSize 100
int pathnum(int m,int n)		//求解从(m,n)到(1,1)的路径条数
{
	if (m<1 || n<1) return 0;
	if (m==1 && n==1) return 1;
	return pathnum(m-1,n)+pathnum(m,n-1);
}
typedef struct
{
	int i,j;
} PathType;							//路径元素类型
int count=0;						//路径编号
void disppath(int m,int n,PathType path[],int d) //输出从(m,n)到(1,1)的所有路径
{	
	if (m<1 || n<1) return;
	if (m==1 && n==1)				//找到目的地，输出一条路径
	{
		d++;						//将当前位置放入path中
		path[d].i=m; path[d].j=n;
		printf("路径%d: ",++count);
		for (int k=0;k<=d;k++)
			printf("(%d,%d) ",path[k].i,path[k].j);
		printf("\n");
	}
	else
	{
		d++;						//将当前位置放入path中
		path[d].i=m; path[d].j=n;
		disppath(m-1,n,path,d);		//向下走一步
		disppath(m,n-1,path,d);		//退回来，向右走一步
	}
}
int main()
{
	int m=2,n=5;
	printf("m=%d,n=%d的路径条数:%d\n",m,n,pathnum(m,n));
	PathType path[MaxSize];
	int d=-1;
	disppath(m,n,path,d);
	return 1;
}
