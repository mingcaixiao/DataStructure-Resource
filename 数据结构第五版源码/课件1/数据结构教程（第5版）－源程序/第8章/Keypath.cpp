//求关键路径算法
#include "graph.cpp"
typedef struct
{	int ino;			//起点
	int eno;			//终点
} KeyNode;				//关键活动类型

bool TopSort(AdjGraph *G,int topseq[])
//产生含有n个顶点编号的拓扑序列topseq
{
	int i,j,n=0;
	int st[MAXV];						//定义一个顺序栈
	int top=-1;							//栈顶指针为top
	ArcNode *p;
	for (i=0;i<G->n;i++)				//所有顶点的入度置初值0
		G->adjlist[i].count=0;
	for (i=0;i<G->n;i++)				//求所有顶点的入度
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	G->adjlist[p->adjvex].count++;
			p=p->nextarc;
		}
	}
	for (i=0;i<G->n;i++)
		if (G->adjlist[i].count==0)		//入度为0的顶点进栈
		{	top++;
			st[top]=i;
		}
	while (top>-1)						//栈不为空时循环
	{	i=st[top];top--;				//出栈
		topseq[n]=i; n++;
		p=G->adjlist[i].firstarc;		//找第一个邻接点
		while (p!=NULL)
		{	j=p->adjvex;
			G->adjlist[j].count--;
			if (G->adjlist[j].count==0)	//入度为0的相邻顶点进栈
			{	top++;
				st[top]=j;
			}
			p=p->nextarc;				//找下一个邻接点
		}
	}
	if (n<G->n)					//拓扑序列中不含所有顶点时
		return false;
	else
	{
		printf("拓扑序列:");
		for (i=0;i<n;i++)
			printf("%c ",(char)(topseq[i]+'A')); 
		printf("\n");
		return true;
	}
}
bool KeyPath(AdjGraph *G,int &inode,int &enode,KeyNode keynode[],int &d)
//从图邻接表G中求出从源点inode到汇点enode的关键活动keynode[0..d]
{	int topseq[MAXV];						//topseq用于存放拓扑序列
	int i,w;
	ArcNode *p;
	if (!TopSort(G,topseq))
		return false;						//不能产生拓扑序列时返回false
	inode=topseq[0];						//求出源点
	enode=topseq[G->n-1];					//求出汇点
	int ve[MAXV];							//事件的最早开始时间
	int vl[MAXV];							//事件的最迟开始时间
	for (i=0;i<G->n;i++) ve[i]=0;			//先将所有事件的ve置初值为0
	for (i=0;i<G->n;i++)					//从左向右求所有事件的最早开始时间
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)						//遍历每一条边即活动
		{	w=p->adjvex;
			if (ve[i]+p->weight>ve[w])		//求最大者
				ve[w]=ve[i]+p->weight;
			p=p->nextarc;
		}
	 }
	for (i=0;i<G->n;i++)					//先将所有事件的vl值置为最大值
		vl[i]=ve[enode];
	for (i=G->n-2;i>=0;i--)					//从右向左求所有事件的最迟开始时间
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	w=p->adjvex;
			if (vl[w]-p->weight<vl[i])		//求最小者
				vl[i]=vl[w]-p->weight; 
			p=p->nextarc;
		}
	}
	d=-1;									//d存放keynode中的关键活动下标,置初置为-1
	for (i=0;i<G->n;i++)					//求关键活动
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	w=p->adjvex;
			if (ve[i]==vl[w]-p->weight)		//(i→w)是一个关键活动
			{
				d++; keynode[d].ino=i; keynode[d].eno=w;
			}
			p=p->nextarc;
		}
	}
	return true;
}
void DispKeynode(AdjGraph *G)
{
	int inode,enode,d,i;
	KeyNode keynode[MAXV];
	if (KeyPath(G,inode,enode,keynode,d))
	{
		printf("从源点%c到汇点%c的关键活动:",char(inode='A'),char(enode+'A'));
		for (i=0;i<=d;i++)
			printf("(%c,%c)  ",char(keynode[i].ino+'A'),char(keynode[i].eno+'A'));
		printf("\n");
	}
	else printf("不能求关键活动\n");
}
int main()
{
	AdjGraph *G;
	int n=9,e=11;
	int A[MAXV][MAXV]={
		{ 0,  6,  4,  5 ,INF,INF,INF,INF,INF},
		{INF, 0, INF,INF, 1 ,INF,INF,INF,INF},
		{INF,INF, 0 ,INF, 1 ,INF,INF,INF,INF},
		{INF,INF,INF, 0 ,INF,INF,INF, 2 ,INF},
		{INF,INF,INF,INF, 0 , 9 , 7 ,INF,INF},
		{INF,INF,INF,INF,INF, 0 ,INF,INF, 2 },
		{INF,INF,INF,INF,INF,INF, 0 ,INF, 4 },
		{INF,INF,INF,INF,INF,INF,INF, 0 , 4 },
		{INF,INF,INF,INF,INF,INF,INF,INF, 0 }};
	printf("建立图的邻接表:\n");
	CreateAdj(G,A,n,e);							//创建图8.45的邻接表
	printf("图G的邻接表:\n"); DispAdj(G);
	DispKeynode(G);								//求构成关键路径的关键活动
	DestroyAdj(G);								//销毁图
	return 1;
}