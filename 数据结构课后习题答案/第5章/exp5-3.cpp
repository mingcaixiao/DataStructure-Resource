//文件名:exp5-3.cpp
#include <stdio.h>
#define MaxSize 100
typedef struct
{	char data[MaxSize];
	int length;
} IP;
void addch(IP &ip,char ch)	//ip的末尾添加一个字符ch
{	ip.data[ip.length]=ch;
	ip.length++;
}
IP adddot(IP ip)			//ip的末尾添加一个'.'，并返回结果
{	addch(ip,'.');
	return ip;
}
void solveip(char s[],int n,int start,int step,IP ip)	//恢复IP地址串
{
	if (start<=n)
	{
		if (start==n && step==4)			//找到一个合法解
		{
			for (int i=0;i<ip.length-1;i++)	//输出其结果,不含最后的一个'.'
				printf("%c",ip.data[i]);
			printf("\n");
		}
	}
	int num=0;
	for (int i=start;i<n && i<start+3;i++)
	{
		num=10*num+(s[i]-'0');			//将start开始的i个数字符转换为数值		
		if (num<=255)					//为合法点，继续递归
		{
			addch(ip,s[i]);
			solveip(s,n,i+1,step+1,adddot(ip));
		}
		if (num==0) break;				//不允许前缀0，单允许单个0
	}
}
int main()
{
	char s[MaxSize]="25525511135";
	int n=11;
	IP ip;
	ip.length=0;
	solveip(s,n,0,0,ip);
	return 1;
}
