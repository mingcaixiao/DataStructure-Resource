//文件名:exp10-9.cpp
#include <stdio.h>
#include <malloc.h>
#define MAXE 20			//线性表中最多元素个数
#define MAXR 10			//基数的最大取值
typedef struct node
{
	int key;			//记录的关键字
    struct node *next;
} NodeType;

void CreateLink(NodeType *&p,int a[],int n)	//采用尾插法创建单链表
{
	NodeType *s,*t;
	for (int i=0;i<n;i++)
	{
		s=(NodeType *)malloc(sizeof(NodeType));
		s->key=a[i];
		if (i==0)
		{
			p=s;t=s;
		}
		else
		{
			t->next=s;t=s;
		}
	}
	t->next=NULL;
}
void DispLink(NodeType *p)	//输出单链表
{
	while (p!=NULL)
	{
		printf("%4d",p->key);
		p=p->next;
	}
	printf("\n");
}
void DestroyLink(NodeType *p)	//销毁单链表
{
	NodeType *pre=p,*q=pre->next;
	while (q!=NULL)
	{
		free(pre);
		pre=q;
		q=q->next;
	}
	free(pre);
}
int keyi(int s,int i)	//对于数值s，从低到高位，取第i位的数字
{
	for (int j=0;j<i;j++)
		s=s/10;
	return s%10;

}
void RadixSort(NodeType *&p,int r,int d) //实现基数排序:p指向单链表的首节点,r为基数,d为关键字位数
{
	NodeType *head[MAXR],*tail[MAXR],*t;	//定义各链队的首尾指针
	int i,j,k;
	for (i=0;i<d;i++)           		//从低位到高位循环
	{	
		for (j=0;j<r;j++) 				//初始化各链队首、尾指针
			head[j]=tail[j]=NULL;
		while (p!=NULL)          		//对于原链表中每个节点循环
		{	
			k=keyi(p->key,i);   		//找p节点关键字的第i位k
			if (head[k]==NULL)   		//将p节点分配到第k个链队
			{
				head[k]=p;
				tail[k]=p;
			}
          	else
			{
              	tail[k]->next=p;
				tail[k]=p;
			}
            p=p->next;             		//继续扫描下一个节点
		}
		p=NULL;
       	for (j=0;j<r;j++)        		//对于每一个链队循环
        	if (head[j]!=NULL)         	//进行收集
			{	
				if (p==NULL)
				{
					p=head[j];
					t=tail[j];
				}
				else
				{
					t->next=head[j];
					t=tail[j];
				}
			}
		t->next=NULL;					//最后一个节点的next域置NULL
		printf("按%d位排序:",i+1); DispLink(p);
	}
}

int main()
{
	int n=10;
	NodeType *p;
	int a[]={75,223,98,44,157,2,29,164,38,82};
	CreateLink(p,a,n);
	printf("   排序前:"); DispLink(p);
	RadixSort(p,10,3);
	printf("   排序后:"); DispLink(p);
	DestroyLink(p);
	return 1;
}
