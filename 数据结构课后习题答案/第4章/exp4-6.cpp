//文件名:exp4-6.cpp
#include "sqstring.cpp"				//包含顺序串的基本运算算法

void GetNext(SqString t,int next[])	//由模式串t求出next值
{	int j,k;
	j=0;k=-1;next[0]=-1;
	while (j<t.length-1)
	{	if (k==-1 || t.data[j]==t.data[k]) 	//k为-1或比较的字符相等时
		{	j++;k++;
			next[j]=k;
		}
		else  k=next[k];
	}
}
void display(SqString s,SqString t,int i,int j) //显示匹配状态
{
	int k;
	printf("  ");
	for (k=0;k<i;k++)
		printf("  ");
	printf("↓ i=%d,j=%d\n",i,j);
	printf("s:");
	for (k=0;k<s.length;k++)
		printf("%c ",s.data[k]);
	printf("\n");
	printf("t:");
	for (k=0;k<i-j;k++)
		printf("  ");
	for (k=0;k<t.length;k++)
		printf("%c ",t.data[k]);
	printf("\n");
	for (k=0;k<i-j;k++)
		printf("  ");
	for (k=0;k<=j;k++)
		printf("  ");
	printf("↑\n");

}
int Count(SqString s,SqString t)	//利用KMP算法求t在s中出现的次数
{
	int next[MaxSize],i=0,j=0,count=0;
	GetNext(t,next);
	display(s,t,i,j);
	while (i<s.length && j<t.length) 
	{
		if (j==-1 || s.data[i]==t.data[j])
		{
			i++;
			j++;				//i,j各增1
		}
		else
		{
			j=next[j]; 			//i不变,j后退
			display(s,t,i,j);
		}
		if (j==t.length)
		{
			display(s,t,i,j);
			printf("\t成功匹配1次\n");
			count++;
			j=0;
		}
	
	}
	return count;
}

int main()
{
	SqString s,t;
	StrAssign(s,"aaabbdaabbde");
	StrAssign(t,"aabbd");
	printf("t在s中出现次数:%d\n",Count(s,t));
	DestroyStr(s); DestroyStr(t); 
	return 1;
}
