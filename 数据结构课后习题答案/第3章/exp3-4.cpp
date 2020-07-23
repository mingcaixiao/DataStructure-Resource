//文件名:exp3-4.cpp
#include "liqueue.cpp"		//包含链队的基本运算算法

int main()
{
	ElemType e;
	LinkQuNode *q;
	printf("链队的基本运算如下:\n");
	printf("  (1)初始化链队q\n");
	InitQueue(q);
	printf("  (2)依次进链队元素a,b,c\n");
	enQueue(q,'a');
	enQueue(q,'b');
	enQueue(q,'c');
	printf("  (3)链队为%s\n",(QueueEmpty(q)?"空":"非空"));
	if (deQueue(q,e)==0) 
		printf("\t提示:队空,不能出队\n");
	else
		printf("  (4)出队一个元素%c\n",e);
	printf("  (5)依次进链队元素d,e,f\n");
	enQueue(q,'d');
	enQueue(q,'e');
	enQueue(q,'f');
	printf("  (6)出链队序列:");
	while (!QueueEmpty(q))
	{	deQueue(q,e);
		printf("%c ",e);
	}
	printf("\n");
	printf("  (7)释放链队\n");
	DestroyQueue(q);
	return 1;
}
