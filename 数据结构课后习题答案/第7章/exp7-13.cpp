//文件名:exp7-13.cpp
#include "preseq.cpp"				//包含序列化和反序列化算法
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
SqString PreOrderSeq1(BTNode *b)  	//由二叉链b产生先序序列化序列str
{
	SqString str,str1,leftstr,rightstr;
	if (b==NULL)
	{
		StrAssign(str,"#");
		return str;
	}
	str.data[0]='@'; str.length=1;	//构造只有特殊字符'@'的字符串str
	leftstr=PreOrderSeq1(b->lchild);
	str1=Concat(str,leftstr);
	rightstr=PreOrderSeq1(b->rchild);
	str=Concat(str1,rightstr);
	return str;
}
bool isSubtree1(BTNode *b1,BTNode *b2)	//判断b1中是否有与b2树形结构相同的子树
{
	SqString s1=PreOrderSeq1(b1);	//求b1的先序序列化序列s1
	SqString s2=PreOrderSeq1(b2);	//求b2的先序序列化序列s2
	if (KMPIndex(s1,s2)!=-1)		//若s2是s1的子串，返回真
		return true;
	else							//若s2不是s1的子串，返回假
		return false;
}
int main()
{
	BTNode *b1,*b2;
	CreateBTree(b1,"A(B(D,E(,G)),C(,F(H,I)))"); 
	printf("二叉树b1:");DispBTree(b1);printf("\n");
	CreateBTree(b2,"c(,f(h,i))"); 
	printf("二叉树b2:");DispBTree(b2);printf("\n");

	if (isSubtree1(b1,b2))
		printf("结果：b1中有与b2树形结构相同的子树\n");
	else
		printf("结果：b1中没有与b2树形结构相同的子树\n");
	DestroyBTree(b1); DestroyBTree(b2);
	return 1;
}
 