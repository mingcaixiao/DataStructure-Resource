//文件名:exp4-3.cpp
#include "sqstring.cpp"				//包含顺序串的基本运算算法
int Index(SqString s,SqString t)	//简单匹配算法
{
	int i=0,j=0;
	while (i<s.length && j<t.length) 
	{	if (s.data[i]==t.data[j])	//继续匹配下一个字符
		{	i++;					//主串和子串依次匹配下一个字符
			j++;
		}
		else						//主串、子串指针回溯重新开始下一次匹配
		{	i=i-j+1;				//主串从下一个位置开始匹配
			j=0; 					//子串从头开始匹配
		}
	}
	if (j>=t.length)
		return(i-t.length);			//返回匹配的第一个字符的下标
	else
		return(-1);					//模式匹配不成功
}
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
int KMPIndex(SqString s,SqString t)	//KMP算法
{
	int next[MaxSize],i=0,j=0;
	GetNext(t,next);
	while (i<s.length && j<t.length) 
	{	if (j==-1 || s.data[i]==t.data[j]) 
		{	i++;
			j++;				//i,j各增1
		}
		else j=next[j]; 		//i不变,j后退
	}
	if (j>=t.length)
		return(i-t.length);		//返回匹配模式串的首字符下标
	else
		return(-1);				//返回不匹配标志
}
void GetNextval(SqString t,int nextval[])  //由模式串t求出nextval值
{
	int j=0,k=-1;
	nextval[0]=-1;
	while (j<t.length)
	{	if (k==-1 || t.data[j]==t.data[k])
		{	j++;k++;
			if (t.data[j]!=t.data[k])
				nextval[j]=k;
			else
				nextval[j]=nextval[k];
		}
		else
			k=nextval[k];
	}
}
int KMPIndex1(SqString s,SqString t)	//修正的KMP算法
{
	int nextval[MaxSize],i=0,j=0;
	GetNextval(t,nextval);
	while (i<s.length && j<t.length) 
	{	if (j==-1 || s.data[i]==t.data[j]) 
		{	i++;
			j++;
		}
		else
			j=nextval[j];
	}
	if (j>=t.length)
		return(i-t.length);
	else
		return(-1);
}

int main()
{
	int j;
	int next[MaxSize],nextval[MaxSize];
	SqString s,t;
	StrAssign(s,"abcabcdabcdeabcdefabcdefg");
	StrAssign(t,"abcdeabcdefab");
	printf("串s:");DispStr(s);
	printf("串t:");DispStr(t);
	printf("简单匹配算法:\n");
	printf("  t在s中的位置=%d\n",Index(s,t));
	GetNext(t,next);			//由模式串t求出next值
	GetNextval(t,nextval);		//由模式串t求出nextval值
	printf("    j   ");
	for (j=0;j<t.length;j++)
		printf("%4d",j);
	printf("\n");
	printf(" t[j]   ");
	for (j=0;j<t.length;j++)
		printf("%4c",t.data[j]);
	printf("\n");
	printf(" next   ");
	for (j=0;j<t.length;j++)
		printf("%4d",next[j]);
	printf("\n");
	printf(" nextval");
	for (j=0;j<t.length;j++)
		printf("%4d",nextval[j]);
	printf("\n");
	printf("KMP算法:\n");
	printf("  t在s中的位置=%d\n",KMPIndex(s,t));
	printf("改进的KMP算法:\n");
	printf("  t在s中的位置=%d\n",KMPIndex1(s,t));
	DestroyStr(s); DestroyStr(t);
	return 1;
}