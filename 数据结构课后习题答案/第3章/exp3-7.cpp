//文件名:exp3-7.cpp
#include "sqstack.cpp"			//包含顺序栈的基本运算算法
void StackSort(SqStack *&st)	//对栈st中元素排序
{
	SqStack *tmpst;
	InitStack(tmpst);
	ElemType e,e1;
	while (!StackEmpty(st))		//st栈不空循环
	{
		Pop(st,e);				//出栈元素e
		printf("    st:出栈%c=> ",e);
		while(!StackEmpty(tmpst))
		{
			GetTop(tmpst,e1);
			printf("tmpst:取栈顶元素%c ",e1);
			if (e1>e)
			{
				printf("因%c>%c ",e1,e);
				printf("tmpst:退栈%c ",e1);
				Pop(tmpst,e1);
				printf("s:进栈%c ",e1);
				Push(st,e1);
			}
			else
			{
				printf("因%c<%c,退出循环 ",e1,e);
				break;
			}
		}
		Push(tmpst,e);
		printf("tmpst:进栈%c\n",e);
	}
	while (!StackEmpty(tmpst))
	{
		Pop(tmpst,e);
		Push(st,e);
	}

	DestroyStack(tmpst);
}

int main()
{
	ElemType e;
	SqStack *s;
	InitStack(s);
	printf("(1)依次进栈元素1,3,4,2\n");
	Push(s,'1');
	Push(s,'3');
	Push(s,'4');
	Push(s,'2');
	printf("(2)栈s排序过程:\n");
	StackSort(s);
	printf("(3)栈s排序完毕\n");
	printf("(4)s的出栈序列:");
	while (!StackEmpty(s))
	{
		Pop(s,e);
		printf("%c ",e);
	}
	printf("\n");
	DestroyStack(s);
	return 1;
}
