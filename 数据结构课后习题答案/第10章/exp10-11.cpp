//文件名:exp10-11.cpp
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MaxLen 9				//单词的最大长度
#define Radix  27				//基数rd为27,分别对应' ','a',…'z'
typedef char String[MaxLen+1];	//定义String为字符数组类型
typedef struct node
{	String word;
	struct node *next;
} LinkNode;						//单链表节点类型
void DispWord(String R[],int n)	//输出单词
{
	int i;
	printf("  ");
	for (i=0;i<n;i++)
		printf("[%s] ",R[i]);
	printf("\n");
}
void PreProcess(String R[],int n)	
//对单词进行预处理,用空格填充尾部至MaxLen长
{
	int i,j;
	for (i=0;i<n;i++)
	{	if (strlen(R[i])<MaxLen)
		{	for (j=strlen(R[i]);j<MaxLen;j++)
				R[i][j]=' ';
			R[i][j]='\0';
		}
	}
}
void EndProcess(String R[],int n)		
//恢复处理,删除预处理时填充的尾部空格
{
	int i,j;
	for (i=0;i<n;i++)
	{	for (j=MaxLen-1;R[i][j]==' ';j--);
		R[i][j+1]='\0';
	}
}
void Distribute(String R[],LinkNode *head[],LinkNode *tail[],int j,int n)  
//按关键字的第j个分量进行分配,进入此过程时各队列一定为空
{
	int i,k;
	LinkNode *p;
	for (i=0;i<n;i++)			//依次扫描R[i],将其入队
	{	if (R[i][j]==' ')		//空格时放入0号队列中,'a'时放入1号队列中,…
			k=0;
		else
			k=R[i][j]-'a'+1;
		p=(LinkNode *)malloc(sizeof(LinkNode));	//创建新节点
		strcpy(p->word,R[i]);
		p->next=NULL;
		if (head[k]==NULL)
		{	head[k]=p;
			tail[k]=p;
		}
		else
		{	tail[k]->next=p;
			tail[k]=p;
		}
	}
}
void Collect(String R[],LinkNode *head[])  
//依次将各非空队列中的节点收集起来，并释放各非空队列中的所有节点
{
	int k=0,i;
	LinkNode *pre,*p;
	for (i=0;i<Radix;i++)
	{
		if (head[i]!=NULL)
		{
			pre=head[i]; p=pre->next;
			while (p!=NULL)
			{
				strcpy(R[k++],pre->word);
				free(pre);
				pre=p;
				p=p->next;
			}
			strcpy(R[k++],pre->word);
			free(pre);
		}
	}
}
void RadixSort(String R[],int n)	//对R[0..n-1]进行基数排序
{
	LinkNode *head[Radix],*tail[Radix];	//定义Radix个队列
	int i,j;
	for (i=MaxLen-1;i>=0;i--)				//从低位到高位做d趟箱排序
	{	for (j=0;j<Radix;j++)
			head[j]=tail[j]=NULL;			//队列置空
		Distribute(R,head,tail,i,n);		//第i趟分配
		Collect(R,head);					//第i趟收集
	}
}
int main()
{
	int n=6;
	String R[]={"while","if","if else","do while","for","case"};
	printf("排序前:\n");DispWord(R,n);
	PreProcess(R,n);
	printf("预处理后:\n");DispWord(R,n);
	RadixSort(R,n);
	printf("排序结果:\n");DispWord(R,n);
	EndProcess(R,n);
	printf("最终结果:\n");DispWord(R,n);
	return 1;
}
