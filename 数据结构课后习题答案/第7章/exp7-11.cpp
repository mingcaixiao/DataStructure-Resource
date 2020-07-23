//文件名:exp7-11.cpp
#include "preseq.cpp"				//包含序列化和反序列化算法
int main()
{
	BTNode *b,*b1;
	SqString str;
	printf("(1)创建二叉链b\n");
	CreateBTree(b,"A(B(D,E(,G)),C(,F(H,I)))"); 
	printf("(2)二叉树b:");DispBTree(b);printf("\n");
	printf("(3)对b进行先序遍历，产生先序序列化序列str\n");
	str=PreOrderSeq(b);
	printf("(4)str:"); DispStr(str);
	printf("(5)由str构建二叉链b1\n");
	b1=CreatePreSeq(str);
	printf("(6)二叉树b1:");DispBTree(b1);printf("\n");
	printf("(7)销毁b和b1\n");
	DestroyBTree(b);
	DestroyBTree(b1);
	return 1;
}
 