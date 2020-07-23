//拉链法构造的哈希表的运算算法
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100				//定义最大哈希表长度
typedef int KeyType;			//关键字类型
typedef struct node
{
	KeyType key;				//关键字域
	struct node *next;			//下一个结点指针
} NodeType;						//单链表结点类型
typedef struct
{
	NodeType *firstp;			//首结点指针
} HashTable;					//哈希表类型
void InsertHT(HashTable ha[],int &n,int p,KeyType k)  //将关键字k插入到哈希表中
{
	int adr;
	adr=k % p;					//计算哈希函数值
	NodeType *q;
	q=(NodeType *)malloc(sizeof(NodeType));
	q->key=k;					//创建一个结点q，存放关键字k
	q->next=NULL;
	if (ha[adr].firstp==NULL)	//若单链表adr为空
		ha[adr].firstp=q;
	else						//若单链表adr不空
	{
		q->next=ha[adr].firstp;	//采用头插法插入到ha[adr]的单链表中
		ha[adr].firstp=q;
	}
	n++;						//结点总个数增1
}
void CreateHT(HashTable ha[],int &n,int m,int p,KeyType keys[],int n1)  //创建哈希表
{
	for (int i=0;i<m;i++)			//哈希表置初值
		ha[i].firstp=NULL;
	n=0;
	for (i=0;i<n1;i++)
		InsertHT(ha,n,p,keys[i]);//插入n个关键字
}
void SearchHT(HashTable ha[],int p,KeyType k)	//在哈希表中查找关键字k
{
	int i=0,adr;
	adr=k % p;					//计算哈希函数值
	NodeType *q;
	q=ha[adr].firstp;			//q指向对应单链表的首结点
	while (q!=NULL)				//扫描单链表adr的所有结点
	{
		i++;
		if (q->key==k)			//查找成功
			break;				//退出循环
		q=q->next;
	}
	if (q!=NULL)				//查找成功
		printf("成功：关键字%d，比较%d次\n",k,i);
	else						//查找失败
		printf("失败：关键字%d，比较%d次\n",k,i);
}
bool DeleteHT(HashTable ha[],int &n,int m,int p,KeyType k)	//删除哈希表中关键字k
{
	int adr;
	adr=k % p;					//计算哈希函数值
	NodeType *q,*preq;
	q=ha[adr].firstp;			//q指向对应单链表的首结点
	if (q==NULL) 
		return false;			//对应单链表为空
	if (q->key==k)				//首结点为k
	{
		ha[adr].firstp=q->next;//删除结点q
		free(q);
		n--;					//结点总个数减1
		return true;			//返回真
	}
	preq=q; q=q->next;			//首结点不为k时
	while (q!=NULL)
	{
		if (q->key==k)			//查找成功
			break;				//退出循环
		q=q->next;
	}
	if (q!=NULL)				//查找成功
	{
		preq->next=q->next;		//删除结点q
		free(q);
		n--;					//结点总个数减1
		return true;			//返回真
	}
	else return false;			//未找到k,返回假
}
void ASL(HashTable ha[],int n,int m)	//求平均查找长度
{
	int succ=0,unsucc=0,s;
	NodeType *q;
	for (int i=0;i<m;i++)		//扫描所有哈希表地址空间
	{
		s=0;
		q=ha[i].firstp;			//q指向单链表i的首结点
		while (q!=NULL)			//扫描单链表i的所有结点
		{
			q=q->next;
			s++;				//s记录当前结点是对应单链表的第几个结点
			succ+=s;			//累计成功的总比较次数
		}
		unsucc+=s;				//累计不成功的总比较次数
	}
	printf(" 成功情况下ASL(%d)=%g\n",n,succ*1.0/n);
	printf(" 不成功情况下ASL(%d)=%g\n",n,unsucc*1.0/m);
}
void DispHT(HashTable ha[],int n,int m)  //输出哈希表
{
	int succ=0,unsucc=0,s;
	NodeType *q;
	for (int i=0;i<m;i++)		//扫描所有哈希表地址空间
	{
		s=0;
		printf(" %3d:\t",i);
		q=ha[i].firstp;			//q指向单链表i的首结点
		while (q!=NULL)			//扫描单链表i的所有结点
		{
			printf("%4d",q->key);
			q=q->next;
			s++;				//s记录当前结点是对应单链表的第几个结点
			succ+=s;			//累计成功的总比较次数
		}
		unsucc+=s;				//累计不成功的总比较次数
		printf("\n");
	}
	printf(" 成功情况下ASL(%d)=%g\n",n,succ*1.0/n);
	printf(" 不成功情况下ASL(%d)=%g\n",n,unsucc*1.0/m);
}
void DestroyHT(HashTable ha[],int m)	//销毁哈希表
{
	int i;
	NodeType *q,*preq;
	for (i=0;i<m;i++)
	{
		q=ha[i].firstp;			//q指向单链表i的首结点
		while (q!=NULL)			//扫描单链表i的所有结点
		{
			preq=q; q=q->next;
			free(preq);
		}
	}
}
int main()
{
	int keys[]={16,74,60,43,54,90,46,31,29,88,77};
	int n,m=13,p=13,k=29;
	HashTable ha[MaxSize];
	printf("(1)创建哈希表\n"); CreateHT(ha,n,m,p,keys,11);
	printf("(2)显示哈希表:\n"); DispHT(ha,n,m);
	printf("(3)查找"); SearchHT(ha,p,k);
	k=77;
	printf("(4)删除：关键字%d\n",k);
	DeleteHT(ha,n,m,p,k);
	printf("(5)显示哈希表:\n"); DispHT(ha,n,m);
	printf("(6)查找"); SearchHT(ha,p,k);
	printf("(7)插入：关键字%d\n",k);
	InsertHT(ha,n,p,k);
	printf("(8)显示哈希表:\n"); DispHT(ha,n,m);
	printf("\n");
	DestroyHT(ha, m);		//销毁哈希表
	return 1;
}