//文件名:exp8-10.cpp
#include "graph.cpp"	//包含图的存储结构及基本运算算法
int visited[MAXV];		//全局数组
void PathAll1(AdjGraph *G,int u,int v,int path[],int d)
//输出图G中从顶点u到v的所有简单路径
{
	ArcNode *p;
	int j,w;
	d++; path[d]=u;						//路径长度d增1,将当前顶点添加到路径中
	visited[u]=1;
	if (u==v && d>0)					//找到终点
	{
		for (j=0;j<=d;j++)
			printf("%3d",path[j]);
		printf("\n");
	}
	p=G->adjlist[u].firstarc;  			//p指向顶点u的第一个相邻点
	while (p!=NULL)
	{
		w=p->adjvex;					//w为u的相邻点编号
		if (visited[w]==0 ) 			//若该顶点未标记访问,则递归访问之
			PathAll1(G,w,v,path,d);
		p=p->nextarc;					//找u的下一个相邻点
	}
	visited[u]=0;
}
void PathAll2(AdjGraph *G,int u,int v,int l,int path[],int d)
//输出图G中从顶点u到v的长度为l的所有简单路径,d是到当前为止已走过的路径长度,调用时初值为-1
{
	int w,i;
	ArcNode *p;
	visited[u]=1;
	d++; path[d]=u;					//路径长度d增1,将当前顶点添加到路径中
	if (u==v && d==l)				//满足条件，输出一条路径
	{
		for (i=0;i<=d;i++)
			printf("%3d",path[i]);
		printf("\n");
	}
	p=G->adjlist[u].firstarc;  		//p指向顶点u的第一个相邻点
	while (p!=NULL)
	{
		w=p->adjvex;				//w为顶点u的相邻点
		if (visited[w]==0)			//若该顶点未标记访问,则递归访问之
			PathAll2(G,w,v,l,path,d);
		p=p->nextarc;				//找u的下一个相邻点
	}
	visited[u]=0;					//取消访问标记,以使该顶点可重新使用
}
int ShortPath(AdjGraph *G,int u,int v,int path[])
//求顶点u到顶点v(u≠v)的最短路径
{	struct 
	{	int vno;						//当前顶点编号
		int level;					//当前顶点的层次
		int parent;					//当前顶点的当一个节点编号
	} qu[MAXV];						//定义顺序非循环队列
	int front=-1,rear=-1,k,lev,i,j;
	ArcNode *p;
	visited[u]=1;
	rear++;							//顶点u已访问,将其入队
	qu[rear].vno=u;
	qu[rear].level=0;					//根节点层次置为1
	qu[rear].parent=-1;
	while (front<rear)					//队非空则执行
	{	front++;
		k=qu[front].vno;				//出队顶点k
		lev=qu[front].level;
		if (k==v) 					//若顶点k为终点
		{	i=0;						//在队列中前推从一条正向路径
			j=front;					//该路径存放在path中
			while (j!=-1)
			{	path[lev-i]=qu[j].vno;	//将最短路径存入path中
				j=qu[j].parent;
				i++;
			}
			return lev;				//找到顶点v,返回其层次
		}
		p=G->adjlist[k].firstarc;		//p指向顶点k的第一个相邻点           
		while (p!=NULL)                 	//依次搜索k的相邻点
		{	if (visited[p->adjvex]==0)  //若未访问过
			{	visited[p->adjvex]=1;
				rear++;
				qu[rear].vno=p->adjvex;	//访问过的相邻点进队
				qu[rear].level=lev+1;
				qu[rear].parent=front;
			}
			p=p->nextarc;				//找顶点k的下一相邻点
		}
	}
	return -1;     			//如果未找到顶点v,返回一特殊值-1
}
int main()
{ 
	int i,j;
	int u=5,v=2,l=3;
	int path[MAXV];
	AdjGraph *G;
	int A[MAXV][MAXV]={
		{0,1,0,1,0,0},
		{0,0,1,0,0,0},
		{1,0,0,0,0,1},
		{0,0,1,0,0,1},
		{0,0,0,1,0,0},
		{1,1,0,1,1,0}};
	int n=6, e=10;
	CreateAdj(G,A,n,e);		//建立图8.21的邻接表
	printf("图G的邻接表:\n"); DispAdj(G);
	printf("(1)从顶点%d到%d的所有路径:\n",u,v);
	for (i=0;i<n;i++) visited[i]=0;
	PathAll1(G,u,v,path,-1);

	printf("(2)从顶点%d到%d的所有长度为%d路径:\n",u,v,l);
	PathAll2(G,u,v,l,path,-1);

	printf("(3)从顶点%d到%d的最短路径:\n",u,v);
	for (i=0;i<n;i++) visited[i]=0;
	j=ShortPath(G,u,v,path);
	for (i=0;i<=j;i++)
		printf("%3d",path[i]);
	printf("\n");
	DestroyAdj(G);
	return 1;
}
