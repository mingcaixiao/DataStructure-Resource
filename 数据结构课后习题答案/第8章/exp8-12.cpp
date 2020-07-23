//文件名:exp8-12.cpp
#include<stdio.h>
#include<malloc.h>
#define MAXV 201
//------图的邻接表定义---------
typedef struct ANode
{	int no;					//动物编号
	struct ANode *nextarc;	//指向下一个可通信动物节点
} ArcNode;
typedef struct Vnode
{
	ArcNode *firstarc;		//指向第一个可通信动物节点
} VNode;
typedef struct
{	int n;					//动物个数，即顶点数
	int m;					//可通信动物对数,即边数
	VNode adjlist[MAXV];	//表头节点数组
} ALGraph;

int BFS(ALGraph *G,int s,int e)			//采用广度优先遍历查找s到e的最短路径长度
{
	int visited[MAXV];
	struct
	{	int no;							//动物顶点编号
		int level;						//层次
	} qu[MAXV];							//环形队列
	int front=0,rear=0,i,w,l;
	ArcNode *p;
	if (s==e) return 0;
	for (i=0;i<G->n;i++) visited[i]=0;
	visited[s]=1;
	rear=(rear+1) % MAXV;				//起点s进队
	qu[rear].no=s; 
	qu[rear].level=0;					//起点的层次设置为0
	while (front!=rear)					//队不空循环
	{
		front=(front+1) % MAXV;
		w=qu[front].no;					//出队顶点w
		l=qu[front].level;				//顶点w的层次为l
		p=G->adjlist[w].firstarc;		//找顶点w的第一个相邻点
		while (p!=NULL)
		{
			if (visited[p->no]==0)		//若该顶点没有访问过
			{
				if (p->no==e)			//找到终点e，访问其层次
					return qu[rear].level;
				visited[p->no]=1;		//访问它
				rear=(rear+1) % MAXV;	//将它进队
				qu[rear].no=p->no;
				qu[rear].level=l+1;
			}
			p=p->nextarc;
		}
	}
	return -1;
}

void InitGraph(ALGraph *&G,int n)		//初始化邻接表
{	int i;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	for (i=0;i<n;i++)
		G->adjlist[i].firstarc=NULL;
	G->n=n;
	G->m=0;
}
void Add(ALGraph *&G,int a,int b)		//图中添加一条边(a,b)
{	ArcNode *p;
	p=(ArcNode *)malloc(sizeof(ArcNode));
	p->no=b;
	p->nextarc=G->adjlist[a].firstarc;
	G->adjlist[a].firstarc=p;
	p=(ArcNode *)malloc(sizeof(ArcNode));
	p->no=a;
	p->nextarc=G->adjlist[b].firstarc;
	G->adjlist[b].firstarc=p;
	G->m++;
}
void DestroyGraph(ALGraph *&G)	//销毁图
{
	ArcNode *pre,*p;
	for (int i=0;i<G->n;i++)
	{
		pre=G->adjlist[i].firstarc;
		if (pre!=NULL)
		{
			p=pre->nextarc;
			while (p!=NULL)
			{
				free(pre);
				pre=p; p=p->nextarc;
			}
			free(pre);
		}
	}
	free(G);
}
void DispGraph(ALGraph *G)		//输出图
{
	int i;
	ArcNode *p;
	printf("n=%d,e=%d\n",G->n,G->m);
	for (i=0;i<G->n;i++)
	{	printf("[%3d]:",i);
		p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	printf("→(%d)",p->no);
			p=p->nextarc;
		}
		printf("→∧\n");
	}
}
int main()
{
	ALGraph *G;
	int m,n,k,a,b,s,e,i;
	FILE *fp;
	fp=fopen("test.txt","r");
	if (fp==NULL)
	{
		printf("不能打开test.txt文件\n");
		return 0;
	}
	fscanf(fp,"%d%d",&n,&m);
	InitGraph(G,n);
	for (i=0;i<m;i++)		//根据输入建立邻接表中的单链表
	{
		fscanf(fp,"%d%d",&a,&b);
		Add(G,a,b);
	}
	printf("邻接表:\n"); DispGraph(G);
	printf("求解结果:\n");
	fscanf(fp,"%d",&k);
	for (i=0;i<k;i++)
	{
		fscanf(fp,"%d %d",&s,&e);
		printf("  case%d至少需要%d个翻译\n",i+1,BFS(G,s,e));
	}
	DestroyGraph(G);
	fclose(fp);
	return 1;
}
