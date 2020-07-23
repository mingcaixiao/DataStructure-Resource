//文件名:exp11-1.cpp
#include <stdio.h>
#define K 5					//5路平衡归并
#define MINKEY -32768		//最小关键字值-∞
typedef int KeyType;
typedef KeyType LoserTree;	//败者树为LoserTree[K]
KeyType b[K];				//b中存放所有的记录(关键字)
int count=1;				//全局变量
void Adjust(LoserTree ls[K],int s)
//沿从叶子节点b[s]到根节点ls[0]的路径调整败者树
{	int i,t;
	t=(s+K)/2;				//ls[t]是b[s]的双亲节点
	while (t>0)
	{
		if(b[s]>b[ls[t]])	//若双亲节点ls[t]比较小(胜者)
		{
			i=s;			//i指向败者(大者)
			s=ls[t];		//s指示新的胜者
			ls[t]=i;		//将败者(大者)放在双亲节点中
		}
		t=t/2;				//继续向上调整
	}
	ls[0]=s;				//冠军节点存放最小者
}
void display(LoserTree ls[K])	//输出败者树ls
{	int i;
	printf("败者树:");
	for (i=0;i<K;i++)
		if (b[ls[i]]==MINKEY)
			printf("%d(-∞) ",ls[i]);
		else
			printf("%d(%d) ",ls[i],b[ls[i]]);
	printf("\n");
}
void CreateLoserTree(LoserTree ls[K]) //建立败者树ls
{
	int i;
	b[K]=MINKEY;			//b[K]置为最小关键字
	for (i=0;i<K;i++)
		ls[i]=K;			//设置ls中"败者"的初值,全部为最小关键字段号
	for(i=K-1;i>=0;--i)		//依次从b[K-1]，b[K-2]，…，b[0]出发调整败者
	{
		printf("(%d)从b[%d](%d)进行调整→",count++,i,b[i]);
		Adjust(ls,i);
		display(ls);
	}
}

int main()
{
	LoserTree ls[K];
	int n=5;
	KeyType a[]={17,5,10,29,15};
	printf("%d路归并的关键字序列:",K);
	for (int i=0;i<n;i++)
	{
		b[i]=a[i];
		printf("%d ",b[i]);
	}
	printf("\n");
	CreateLoserTree(ls);
	printf("最终结果  "); display(ls);
	return 1;
}
	
