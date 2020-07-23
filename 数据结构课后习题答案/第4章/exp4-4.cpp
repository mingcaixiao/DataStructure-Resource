//文件名:exp4-4.cpp
#include "sqstring.cpp"				//包含顺序串的基本运算算法
SqString A,B;						//全局串
SqString EnCrypt(SqString p)		//返回加密串
{
	int i=0,j;
	SqString q;
	while (i<p.length) 
	{
		for (j=0;p.data[i]!=A.data[j];j++);	
		if (j>=p.length)			//在A串中未找到p.data[i]字母
			q.data[i]=p.data[i];
		else						//在A串中找到p.data[i]字母
			q.data[i]=B.data[j];
		i++;
	}
	q.length=p.length;
	return q;
}
SqString UnEncrypt(SqString q)		//返回解密串
{
	int i=0,j;
	SqString p;
	while (i<q.length) 
	{	
		for (j=0;q.data[i]!=B.data[j];j++);
		if (j>=q.length)			//在B串中未找到q.data[i]字母
			p.data[i]=q.data[i];
		else						//在B串中找到q.data[i]字母
			p.data[i]=A.data[j];
		i++;
	}
	p.length=q.length;
	return p;
}
int main()
{
	SqString p,q;
	int ok=1;
	StrAssign(A,"abcdefghijklmnopqrstuvwxyz");	//建立A串
	StrAssign(B,"ngzqtcobmuhelkpdawxfyivrsj");	//建立B串
	char str[MaxSize];
	printf("\n");
	printf("输入原文串:");
	gets(str);									//获取用户输入的原文串
	StrAssign(p,str);							//建立p串
	printf("加密解密如下:\n");
	printf("  原文串:");DispStr(p);
	q=EnCrypt(p);								//p串加密产生q串
	printf("  加密串:");DispStr(q);
    	p=UnEncrypt(q);							//q串解密产生p串
	printf("  解密串:");DispStr(p);
	printf("\n");
	DestroyStr(p); DestroyStr(q);
	return 1;
}
