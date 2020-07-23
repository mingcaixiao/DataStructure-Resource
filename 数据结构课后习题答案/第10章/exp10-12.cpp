//文件名:exp10-12.cpp
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAXR 10
#define MaxSize 10
typedef struct node
{	char xm[10];	//姓名
	char xb;		//性别 m:男 f:女
	char bh[6];		//班号
	struct node *next;
} StudNode;
typedef struct 
{	char xm[10];	//姓名
	char xb;		//性别 m:男 f:女
	char bh[6];		//班号
} StudType;
void CreateLink(StudNode *&p,StudType A[],int n)	//创建单链表
{	int i;
	StudNode *s,*t;
	p=NULL;
	for (i=0;i<n;i++)
	{	s=(StudNode *)malloc(sizeof(StudNode));
		strcpy(s->xm,A[i].xm);
		s->xb=A[i].xb;
		strcpy(s->bh,A[i].bh);
		if (p==NULL)
		{	p=s;
			t=s;
		}
		else
		{	t->next=s;
			t=s;
		}
	}
	t->next=NULL;
}
void DispLink(StudNode *p)		//输出单链表
{	int i=0;
	while (p!=NULL)
	{	printf(" %s(%s,%c) ",p->xm,p->bh,p->xb);
		p=p->next;
		if ((i+1)%5==0) printf("\n");
		i++;
	}
	printf("\n");
}
void DestroyLink(StudNode *p)	//销毁单链表
{
	StudNode *pre=p,*q=pre->next;
	while (q!=NULL)
	{
		free(pre);
		pre=q;
		q=q->next;
	}
	free(pre);
}
void RadixSort1(StudNode *&p,int r,int d)
//对性别进行排序:只需进行一趟.p为待排序序列链表指针,r为基数,d为关键字位数
{	StudNode *head[MAXR],*tail[MAXR],*t;//定义各链队的首尾指针
	int j,k;
	printf("按性别进行排序\n");
	for (j=0;j<r;j++) 				//初始化各链队首、尾指针
		head[j]=tail[j]=NULL;
	while (p!=NULL)					//对于原链表中每个节点循环
	{	if (p->xb=='f')				//找第k个链队
			k=0;
		else 
			k=1;
		if (head[k]==NULL)			//进行分配,即采用尾插法建立单链表
		{	head[k]=p;
			tail[k]=p;
		}
		else
		{	tail[k]->next=p;
			tail[k]=p;
		}
		p=p->next;					//取下一个待排序的元素
	}
	p=NULL;
	for (j=0;j<r;j++)				//对于每一个链队循环
		if (head[j]!=NULL)			//进行收集
		{	if (p==NULL)
			{	p=head[j];
				t=tail[j];
			}
			else
			{	t->next=head[j];
				t=tail[j];
			}
		}
	t->next=NULL;					//最后一个节点的next域置NULL
	DispLink(p);
}
void RadixSort2(StudNode *&p,int r,int d)
//对班号进行排序:p为待排序序列链表指针,r为基数,d为关键字位数
{	StudNode *head[MAXR],*tail[MAXR],*t;//定义各链队的首尾指针
	int i,j,k;
	printf("按班号进行排序\n");
	for (i=3;i>=2;i--)				//从低位到高位做d趟排序
	{	for (j=0;j<r;j++)			//初始化各链队首、尾指针
			head[j]=tail[j]=NULL;
		while (p!=NULL)				//对于原链表中每个节点循环
		{	k=p->bh[i]-'0';			//找第k个链队
			if (head[k]==NULL)		//进行分配,即采用尾插法建立单链表
			{	head[k]=p;
				tail[k]=p;
			}
			else
			{	tail[k]->next=p;
				tail[k]=p;
			}
			p=p->next;				//取下一个待排序的元素
		}
		p=NULL;
		for (j=0;j<r;j++)			//对于每一个链队循环
			if (head[j]!=NULL)		//进行收集
			{	if (p==NULL)
				{	p=head[j];
					t=tail[j];
				}
				else
				{	t->next=head[j];
					t=tail[j];
				}
			}
		t->next=NULL;				//最后一个节点的next域置NULL
		printf(" 第%d趟:\n",d-i+2);DispLink(p);
	}
}
void Sort(StudType A[],int n)		//按班号和性别进行排序
{
	StudNode *p;
	CreateLink(p,A,n);
	printf("排序前:\n");DispLink(p);
	RadixSort1(p,2,1);				//对性别进行排序
	RadixSort2(p,10,2);				//对班号的后两位进行排序
	printf("排序后:\n");DispLink(p);
	DestroyLink(p);
}
int main()
{
	int n=10;
	StudType A[MaxSize]={{"王华",'m',"1003"},{"阵兵",'m',"1020"},
	{"许可",'f',"1022"},{"李英",'f',"1003"},
	{"张冠",'m',"1021"},{"陈强",'m',"1002"},
	{"李真",'f',"1002"},{"章华",'m',"1001"},
	{"刘丽",'f',"1021"},{"王强",'m',"1022"}};
	Sort(A,n);
	return 1;
}
