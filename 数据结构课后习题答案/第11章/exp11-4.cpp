//文件名:exp11-4.cpp
#include <stdio.h>
#define MaxSize 20			//每个文件中最多记录
#define K 5					//5路平衡归并
#define MAXKEY 32767		//最大关键字值∞
#define MINKEY -32768		//最小关键字值-∞
typedef int InfoType;
typedef int KeyType;
typedef struct				//记录类型
{
	KeyType key;			//关键字项
	InfoType otherinfo;		//其他数据项,具体类型在主程中定义
} RecType;
typedef struct
{
	RecType recs[MaxSize];
	int currec;
} FileType;					//文件类型
typedef int LoserTree;		//败者树为LoserTree[K]
RecType b[K];				//b中存放各段中取出的当前记录
FileType F[K];				//存放文件记录的数组
void initial()				//初始化存放文件记录的数组F
{
	int i;					//5个初始文件,当前读记录号为-1
	F[0].recs[0].key=17;
	F[0].recs[1].key=21;
	F[0].recs[2].key=MAXKEY;
	F[1].recs[0].key=5;
	F[1].recs[1].key=44;
	F[1].recs[2].key=MAXKEY;
	F[2].recs[0].key=10;
	F[2].recs[1].key=12;
	F[2].recs[2].key=MAXKEY;
	F[3].recs[0].key=29;
	F[3].recs[1].key=32;
	F[3].recs[2].key=MAXKEY;
	F[4].recs[0].key=15;
	F[4].recs[1].key=56;
	F[4].recs[2].key=MAXKEY;
	for (i=0;i<K;i++)
		F[i].currec=-1;
}
void input(int i,int &key)	//从F[i]文件中读一个记录到b[i]中
{
	F[i].currec++;
	key=F[i].recs[F[i].currec].key;
}
void output(int q)		//输出F[q]中的当前记录
{
	printf("输出F[%d]的关键字%d\n",q,F[q].recs[F[q].currec].key);   
}
void Adjust(LoserTree ls[K],int s)
//沿从叶子节点b[s]到根节点ls[0]的路径调整败者树
{
	int i,t;
	t=(s+K)/2;			//ls[t]是b[s]的双亲节点
	while(t>0)
	{
		if(b[s].key>b[ls[t]].key)
		{
			i=s;
			s=ls[t];	//s指示新的胜者
			ls[t]=i;
		}
		t=t/2;
	}
	ls[0]=s;
}
void display(LoserTree ls[K])	//输出败者树ls
{
	int i;
	printf("败者树:");
	for (i=0;i<K;i++)
		if (b[ls[i]].key==MAXKEY)
			printf("%d(∞) ",ls[i]);
		else if (b[ls[i]].key==MINKEY)
			printf("%d(-∞) ",ls[i]);
		else
			printf("%d(%d) ",ls[i],b[ls[i]].key);
	printf("\n");
}
void CreateLoserTree(LoserTree ls[K])	//建立败者树ls
{
	int i;
	b[K].key=MINKEY;		//b[K]置为最小关键字
	for (i=0;i<K;i++)
		ls[i]=K;			//设置ls中“败者”的初值,全部为最小关键字段号
	for(i=K-1;i>=0;--i)		//依次从b[K-1]，b[K-2]，…，b[0]出发调整败者
		Adjust(ls,i);
}
void K_Merge(LoserTree ls[K])	//利用败者树ls将进行K路归并到输出
{
	int i,q;
	for(i=0;i<K;++i)		//分别从k个输入归并段读入该段当前第一个记录的关键字到b
		input(i,b[i].key);
	CreateLoserTree(ls);	//建败者树ls,选得最小关键字为b[ls[0]].key
	display(ls);
	while(b[ls[0]].key!=MAXKEY)
	{
		q=ls[0];			//q指示当前最小关键字所在归并段
		output(q);			//将编号为q的归并段中当前（关键字为b[q].key）的记录输出
		input(q,b[q].key);	//从编号为q的输入归并段中读人下一个记录的关键字
		if (b[q].key==MAXKEY)
			printf("从F[%d]中添加关键字∞并调整\n",q);
		else
			printf("从F[%d]中添加关键字%d并调整\n",q,b[q].key);
		Adjust(ls,q);		//调整败者树，选择新的最小关键字
		display(ls);
	}
}
int main()
{
	LoserTree ls[K];
	printf("F0:{17,21,∞}  F1:{5,44,∞}  F2:{10,12,∞}  F3:{29,32,∞}  F4:{15,56,∞}\n");
	initial();
	K_Merge(ls);
	return 1;
}
