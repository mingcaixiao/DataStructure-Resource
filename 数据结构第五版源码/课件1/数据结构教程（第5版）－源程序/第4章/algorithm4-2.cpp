//【例4.2】的算法：求串s中第一个最长的连续相同字符构成的平台
#include "sqstring.cpp"
void LongestString(SqString s,int &index,int &maxlen)
{
	int length,i=1,start;		//length保存平台的长度
	index=0,maxlen=1;			//index保存最长平台在s中的开始位置,maxlen保存其长度
	while (i<s.length)
	{
		start=i-1;				//查找局部重复子串
		length=1;
		while (i<s.length && s.data[i]==s.data[i-1])
		{	
			i++;
			length++;
		}
		if (maxlen<length)		//当前平台长度大,则更新maxlen
		{	
			maxlen=length;
			index=start;
		}
		i++;
	}
}
int main()
{
	SqString s;
	int i,j,k;
	//StrAssign(s,"aabcsaaaabcdeab");
	StrAssign(s,"AAAABBBCCCC");
	printf("s:");DispStr(s);
	LongestString(s,i,j);
	printf("最长平台:");
	for (k=i;k<i+j;k++)
		printf("%c",s.data[k]);
	printf("\n");
	return 1;
}