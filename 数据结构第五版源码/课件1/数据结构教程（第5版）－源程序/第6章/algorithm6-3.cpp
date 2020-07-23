//【例6.3】的算法：求广义表g的原子个数
#include "glist.cpp"

//解法1的方法
int Count1(GLNode *g)					//求广义表g的原子个数
{	int n=0;
	GLNode *g1=g->val.sublist;
	while (g1!=NULL)					//对每个元素进行循环处理
	{	if (g1->tag==0)					//为原子时
			n++;						//原子个数增1
		else							//为子表时
			n+=Count1(g1);				//累加元素的原子个数
		g1=g1->link;					//累加兄弟的原子个数
	}
	return n;							//返回总原子个数
}
//解法2的方法
int Count2(GLNode *g)					//求广义表g的原子个数
{	int n=0;
	if (g!=NULL)						//对每个元素进行循环处理
	{	if (g->tag==0)					//为原子时
			n++;						//原子个数增1
		else							//为子表时
			n+=Count2(g->val.sublist);	//累加元素的原子个数
		n+=Count2(g->link);				//累加兄弟的原子个数
	}
	return n;							//返回总原子个数
}

int main()
{
	GLNode *g;
	char *str="((a),b,(c,d))";
	g=CreateGL(str);
	DispGL(g);
	printf("\n");
	printf("解法1原子个数：%d\n",Count1(g));
	printf("解法2原子个数：%d\n",Count2(g));
	DestroyGL(g);
	return 1;
}
