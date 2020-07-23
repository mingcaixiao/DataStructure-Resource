//文件名:exp8-1.cpp
#include "graph.cpp"		//包含图的存储结构及基本运算算法
int main()
{
	MatGraph g;
	AdjGraph *G;
	int A[MAXV][MAXV]={
		{0,5,INF,7,INF,INF},
		{INF,0,4,INF,INF,INF},
		{8,INF,0,INF,INF,9},
		{INF,INF,5,0,INF,6},
		{INF,INF,INF,5,0,INF},
		{3,INF,INF,INF,1,0}};
	int n=6,e=10;			//图8.1中的数据
	CreateMat(g,A,n,e);
	printf("(1)图G的邻接矩阵:\n");	DispMat(g);
	CreateAdj(G,A,n,e);
	printf("(2)图G的邻接表:\n"); DispAdj(G);
	printf("(3)销毁图G的邻接表\n");
	DestroyAdj(G);
	return 1;
}