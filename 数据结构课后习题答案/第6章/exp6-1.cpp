//文件名:exp6-1.cpp
#include <stdio.h>
#define N 4
typedef int ElemType;
#define MaxSize  100		//矩阵中非零元素最多个数
typedef struct 
{	int r;              	//行号
    int c;					//列号
    ElemType d;            	//元素值
} TupNode;              	//三元组定义
typedef struct 
{	int rows;              	//行数值
    int cols;              	//列数值
    int nums;              	//非零元素个数
    TupNode data[MaxSize];
} TSMatrix;                	//三元组顺序表定义
void CreatMat(TSMatrix &t,ElemType A[N][N])  //产生稀疏矩阵A的三元组表示t
{
	int i,j;
	t.rows=N;t.cols=N;t.nums=0;
	for (i=0;i<N;i++)
	{ 
		for (j=0;j<N;j++) 
			if (A[i][j]!=0) 
			{	
				t.data[t.nums].r=i;t.data[t.nums].c=j;
				t.data[t.nums].d=A[i][j];t.nums++;
			}
	}
}
void DispMat(TSMatrix t)	//输出三元组表示t
{
	int i;
	if (t.nums<=0) 
		return;
	printf("\t%d\t%d\t%d\n",t.rows,t.cols,t.nums);
		printf("\t------------------\n");
	for (i=0;i<t.nums;i++)
		printf("\t%d\t%d\t%d\n",t.data[i].r,t.data[i].c,t.data[i].d);
}
void TranMat(TSMatrix t,TSMatrix &tb)	//求三元组表示t的转置矩阵tb
{
	int p,q=0,v;      					//q为tb.data的下标
	tb.rows=t.cols;tb.cols=t.rows;tb.nums=t.nums;
	if (t.nums!=0) 
	{	
		for (v=0;v<t.cols;v++)			//tb.data[q]中的记录以c域的次序排列
			for (p=0;p<t.nums;p++) 		//p为t.data的下标
				if (t.data[p].c==v) 
				{	
					tb.data[q].r=t.data[p].c;
					tb.data[q].c=t.data[p].r;
					tb.data[q].d=t.data[p].d;
					q++;
				}
	}
}
bool MatAdd(TSMatrix a,TSMatrix b,TSMatrix &c)	//求c=a+b
{
	int i=0,j=0,k=0;
	ElemType v;
	if (a.rows!=b.rows || a.cols!=b.cols)
		return false;						//行数或列数不等时不能进行相加运算
	c.rows=a.rows;c.cols=a.cols;			//c的行列数与a的相同
	while (i<a.nums && j<b.nums)			//处理a和b中的每个元素
	{	
		if (a.data[i].r==b.data[j].r)		//行号相等时
		{	
			if(a.data[i].c<b.data[j].c)		//a元素的列号小于b元素的列号
			{	
				c.data[k].r=a.data[i].r;	//将a元素添加到c中
				c.data[k].c=a.data[i].c;
				c.data[k].d=a.data[i].d;
				k++;i++;
           	}
           	else if (a.data[i].c>b.data[j].c)//a元素的列号大于b元素的列号
			{	
				c.data[k].r=b.data[j].r;	//将b元素添加到c中
               	c.data[k].c=b.data[j].c;
               	c.data[k].d=b.data[j].d;
               	k++;j++;
           	}
           	else							//a元素的列号等于b元素的列号
			{ 	
				v=a.data[i].d+b.data[j].d;
				if (v!=0)					//只将不为0的结果添加到c中
				{	
					c.data[k].r=a.data[i].r;
					c.data[k].c=a.data[i].c;
					c.data[k].d=v;
					k++;
				}
				i++;j++;
          	 }
		}
     	else if (a.data[i].r<b.data[j].r)	//a元素的行号小于b元素的行号
		{	
			c.data[k].r=a.data[i].r;		//将a元素添加到c中
			c.data[k].c=a.data[i].c;
			c.data[k].d=a.data[i].d;
			k++;i++;
		}
    	else								//a元素的行号大于b元素的行号
		{	
			c.data[k].r=b.data[j].r;		//将b元素添加到c中
			c.data[k].c=b.data[j].c;
			c.data[k].d=b.data[j].d;
			k++;j++;
     	}
     	c.nums=k;
	}
	return true;
}
int getvalue(TSMatrix t,int i,int j)		//返回三元组t表示的A[i][j]值
{
    int k=0;
    while (k<t.nums && (t.data[k].r!=i || t.data[k].c!=j)) 
		k++;
    if (k<t.nums) 
		return(t.data[k].d);
    else 
		return(0);
}
bool MatMul(TSMatrix a,TSMatrix b,TSMatrix &c)	//求c=a×b
{
    int i,j,k,p=0;
	ElemType s;
	if (a.cols!=b.rows)		//a的列数不等于b的行数时不能进行相乘运算
		return false;
	for (i=0;i<a.rows;i++)
		for (j=0;j<b.cols;j++) 
		{
            s=0;
            for (k=0;k<a.cols;k++)
				s=s+getvalue(a,i,k)*getvalue(b,k,j);
            if (s!=0)     //产生一个三元组元素
            {
                c.data[p].r=i;
                c.data[p].c=j;
                c.data[p].d=s;
                p++;
            }
        }
	c.rows=a.rows; 
	c.cols=b.cols;
	c.nums=p;
	return true;
}
int main()
{
	ElemType a1[N][N]={{1,0,3,0},{0,1,0,0},{0,0,1,0},{0,0,1,1}};
	ElemType b1[N][N]={{3,0,0,0},{0,4,0,0},{0,0,1,0},{0,0,0,2}};
	TSMatrix a,b,c;
	CreatMat(a,a1);
	CreatMat(b,b1);
	printf("a的三元组:\n");DispMat(a);
	printf("b的三元组:\n");DispMat(b);
	printf("a转置为c\n");
	TranMat(a,c);
	printf("c的三元组:\n");DispMat(c);
	printf("c=a+b\n");
	MatAdd(a,b,c);
	printf("c的三元组:\n");DispMat(c);
	printf("c=a×b\n");
	MatMul(a,b,c);
	printf("c的三元组:\n");DispMat(c);
	return 1;
}
