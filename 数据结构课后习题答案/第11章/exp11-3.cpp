//文件名:exp11-3.cpp
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 50			//每个文件最多记录数
#define MAXKEY 32767		//最大关键字值∞
#define W 5					//内存工作区可容纳的记录个数
typedef int LoserTree;		//败者树节点类型，它是完全二叉树且不含叶子,可采用顺序存储结构
typedef int InfoType;		//定义其他数据项的类型
typedef int KeyType;		//定义关键字类型为整型
typedef struct 
{	KeyType key;			//关键字项
	InfoType otherinfo;		//其他数据项,具体类型在主程中定义
} RecType;					//排序文件的记录类型
typedef struct
{	RecType recs[MaxSize];	//存放文件中的数据项
	int length;				//存放文件中实际记录个数
	int currec;				//存放当前位置
} FileType;					//文件类型
typedef struct
{	RecType rec;			//存放记录
	int rnum;				//所属归并段的段号
} WorkArea;					//内存工作区元素类型,其容量为W
FileType Fi;				//定义输入文件,为全局变量
FileType Fo;				//定义输出文件,为全局变量
void initial()				//输入输出文件初始化
{	int n=19,i;
	KeyType a[]={15,4,97,64,17,32,108,44,76,9,39,82,56,31,80,73,255,68,MAXKEY};
	for (i=0;i<n;i++)		//将n个记录存放到输入文件中
		Fi.recs[i].key=a[i];
	Fi.length=n; 			//输入文件中有n个记录
	Fi.currec=-1;			//输入文件中当前位置为-1
	Fo.currec=-1;			//输出文件中当前位置为-1
	Fo.length=0; 			//输出文件中没有任何记录
}

void Select_MiniMax(LoserTree ls[W],WorkArea wa[W],int q) 
//从wa[q]起到败者树的根比较选择最小记录,并由q指示它所在的归并段
{
	int p,s,t;
	for (t=(W+q)/2,p=ls[t];t>0;t=t/2,p=ls[t])
		if (wa[p].rnum<wa[q].rnum || wa[p].rnum==wa[q].rnum && wa[p].rec.key<wa[q].rec.key)
		{
			s=q;
			q=ls[t];		//q指示新的胜者
			ls[t]=s;
		}
		ls[0]=q;
}
void Construct_Loser(LoserTree ls[W],WorkArea wa[W])
//输入W个记录到内存工作区wa,建败者树ls,选最小的记录并由s指示其在wa中的位置
{
	int i;
	for(i=0;i<W;i++)
		wa[i].rnum=wa[i].rec.key=ls[i]=0;	//工作区初始化
	for(i=W-1;i>=0;i--)
	{
		Fi.currec++;						//从输入文件读入一个记录
		wa[i].rec=Fi.recs[Fi.currec];		
		wa[i].rnum=1;						//其段号为1
		Select_MiniMax(ls,wa,i);			//调整败者
	}
}
void get_run(LoserTree ls[W],WorkArea wa[W],int rc,int &rmax)
//求得一个初始归并段
{
	int q;
	KeyType minimax;				//当前最小关键字
	while (wa[ls[0]].rnum==rc)		//选得的当前最小记录属当前段时
	{
		q=ls[0];					//q指示当前最小记录在wa中的位置
		minimax=wa[q].rec.key;
		Fo.currec++;				//将刚选得的当前最小记录写入输出文件
		Fo.length++; 
		Fo.recs[Fo.currec]=wa[q].rec;
		Fi.currec++;				//从输入文件读入下一记录
		wa[q].rec=Fi.recs[Fi.currec];
		if (Fi.currec>=Fi.length-1)	//输入文件结束,虚设记录(属rmax+1段)
		{	
			wa[q].rnum=rmax+1;	
			wa[q].rec.key=MAXKEY;
		}
		else						//输入文件非空时
		{	
			if(wa[q].rec.key<minimax)
			{ 
				rmax=rc+1;			//新读入的记录属下一段
				wa[q].rnum=rmax;
			}
			else					//新读入的记录属当前段
				wa[q].rnum=rc;
		}
		Select_MiniMax(ls,wa,q);	//选择新的当前最小记录
    }
}
void Replace_Selection(LoserTree ls[W],WorkArea wa[W])
//在败者树ls和内存工作区wa上用置换－选择排序求初始归并段
{
	int rc,rmax;
	RecType j;							//j作为一个关键字最大记录,作为一个输出段结束标志
	j.key=MAXKEY;
	Construct_Loser(ls,wa);				//初建败者树
	rc=1;								//rc指示当前生成的初始归并段的段号
	rmax=1;								//rmax指示wa中关键字所属初始归并段的最大段号
	while(rc<=rmax)						//rc=rmax+1标志输入文件的置换－选择排序已完成
	{
		get_run(ls,wa,rc,rmax);			//求得一个初始归并段
		Fo.currec++;					//将段结束标志写入输出文件
		Fo.recs[Fo.currec]=j;
		Fo.length++; 
		rc=wa[ls[0]].rnum;				//设置下一段的段号
	}
}
int main()
{
	int i=0,rno=1;
	initial();
	LoserTree ls[W];
	WorkArea wa[W];
	printf("大文件的记录为:\n  ");
	while (Fi.recs[i].key!=MAXKEY)
	{
		printf("%d ",Fi.recs[i].key);
		i++;
	}
	printf("\n");
	Replace_Selection(ls,wa);		//用置换-选择排序求初始归并段
	printf("产生的归并段文件的记录如下:\n");
	printf("  归并段%d:",rno);		//输出所有的归并段
	for (i=0;i<Fo.length;i++)
		if (Fo.recs[i].key==MAXKEY)
		{
			printf("∞");
			if (i<Fo.length-1)
			{
				rno++;
				printf("\n  归并段%d:",rno);
			}
		}
		else
			printf("%d ",Fo.recs[i].key);
	printf("\n  共产生%d个归并段文件\n",rno);
	return 1;
}
	
