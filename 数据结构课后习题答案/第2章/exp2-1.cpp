//文件名:exp2-1.cpp
#include "sqlist.cpp"
int main()
{
	SqList *L;
	ElemType e;
	printf("顺序表的基本运算如下:\n");
	printf("  (1)初始化顺序表L\n");
	InitList(L);
	printf("  (2)依次插入a,b,c,d,e元素\n");
	ListInsert(L,1,'a');
	ListInsert(L,2,'b');
	ListInsert(L,3,'c');
	ListInsert(L,4,'d');
	ListInsert(L,5,'e');
	printf("  (3)输出顺序表L:");
	DispList(L);
	printf("  (4)顺序表L长度:%d\n",ListLength(L));
	printf("  (5)顺序表L为%s\n",(ListEmpty(L)?"空":"非空"));
	GetElem(L,3,e);
	printf("  (6)顺序表L的第3个元素:%c\n",e);
	printf("  (7)元素a的位置:%d\n",LocateElem(L,'a'));
	printf("  (8)在第4个元素位置上插入f元素\n");
	ListInsert(L,4,'f');
	printf("  (9)输出顺序表L:");
	DispList(L);
	printf("  (10)删除L的第3个元素\n");
    	ListDelete(L,3,e);
	printf("  (11)输出顺序表L:");
	DispList(L);
	printf("  (12)释放顺序表L\n");
	DestroyList(L);
	return 1;
}
