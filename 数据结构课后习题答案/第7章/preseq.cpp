//文件名:exp7-11.cpp
#include "btree.cpp"				//包含二叉树的基本运算算法
#include "sqstring.cpp"				//包含顺序串的基本运算算法
int i=0;							//全局变量
SqString PreOrderSeq(BTNode *b)  	//由二叉链b产生先序序列化序列str
{
	SqString str,str1,leftstr,rightstr;
	if (b==NULL)
	{
		StrAssign(str,"#");
		return str;
	}
	str.data[0]=b->data; str.length=1;	//构造只有b->data字符的字符串str
	leftstr=PreOrderSeq(b->lchild);
	str1=Concat(str,leftstr);
	rightstr=PreOrderSeq(b->rchild);
	str=Concat(str1,rightstr);
	return str;
}
BTNode *CreatePreSeq(SqString str)		//由先序序列化序列str创建二叉链并返回根结点
{
	BTNode *b;
	char value;
	if (i>=str.length)					//i超界返回空
		return NULL;
	value=str.data[i]; i++;				//从str中取出一个字符value
	if (value=='#')						//若value为'#'，返回空
		return NULL;
	b=(BTNode *)malloc(sizeof(BTNode));	//创建根结点
	b->data=value;
	b->lchild=CreatePreSeq(str);		//递归构造左子树
	b->rchild=CreatePreSeq(str);		//递归构造右子树
	return b;							//返回根结点
}
