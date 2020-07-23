//文件名:exp7-10.cpp
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 100			//最多记录个数
#define MaxSons 10			//最多下级单位数
typedef struct
{
	char fname[20];			//单位名称
	char sname[20];			//下级单位名称或者人数
} RecType;

typedef struct node
{	char data[20];					//结点的值：单位名称或者人数
	struct node *sons[MaxSons];		//指向孩子结点
} TSonNode;							//声明孩子链存储结构结点类型

void ReadFile(RecType R[],int &n)	//读abc.txt文件存入R数组中
{
	FILE *fp;
	n=0;
	if ((fp=fopen("abc.txt","r"))==NULL) 
	{
		printf("不能打开文件abc.txt");
		return;
	}
	while (!feof(fp))
	{
		fscanf(fp,"%s",&R[n].fname);	//读fname域数据
		fscanf(fp,"%s",&R[n].sname);	//读sname域数据
		n++;
	}	
	fclose(fp);
}
TSonNode *CreateTree(char root[],RecType R[],int n) //创建一棵树
{
	int i,j,k;
	TSonNode *t;
	t=(TSonNode *)malloc(sizeof(TSonNode));		//创建根结点
	strcpy(t->data,root);
	for (k=0;k<MaxSons;k++)						//结点所有指针域置为空
		t->sons[k]=NULL;
	i=0; j=0;
	while (i<n)
	{
		if (strcmp(R[i].fname,root)==0)			//找到fname为root的记录
		{
			t->sons[j]=CreateTree(R[i].sname,R,n);
			j++;
		}
		i++;
	}
	return t;
}

void DispTree(TSonNode *t)				//输出孩子链存储结构
{
	int i;
	if (t!=NULL)
	{	printf("%s",t->data);
		if (t->sons[0]!=NULL)			//t结点至少有一个孩子
		{	printf("(");				//输出一个左括号
			for (i=0;i<MaxSons;i++)
			{	DispTree(t->sons[i]);
				if (t->sons[i+1]!=NULL)	//如果有下一个孩子
					printf(",");		//输出一个','
				else					//如果没有下一个孩子
					break;				//退出循环
			}
			printf(")");				//输出一个右括号
		}
	}
}
void DestroyTree(TSonNode *&t)				//销毁树t
{
	int i;
	if (t!=NULL)
	{	for (i=0;i<MaxSons;i++)
		{	if (t->sons[i]!=NULL)			//有子树
				DestroyTree(t->sons[i]);	//销毁该子树
			else							//再没有子树
				break;						//退出循环
		}
		free(t);							//释放根结点
	}
}
TSonNode *FindNode(TSonNode *t,char x[])	//求x结点的指针
{	int i;
	TSonNode *p;
	if (t==NULL)
		return NULL;
	else if (strcmp(t->data,x)==0)			//找到值为x的结点
		return t;
	else
	{	for (i=0;i<MaxSons;i++)
			if (t->sons[i]!=NULL)
			{	p=FindNode(t->sons[i],x);
				if (p!=NULL) return p;
			}
			else break;
		return NULL;
	}
}
int ChildCount(TSonNode *p)		//求p所指结点的孩子个数
{	int i,num=0;
	for (i=0;i<MaxSons;i++)
		if (p->sons[i]!=NULL)
			num++;
		else
			break;
	return num;
}
int Sonnum(TSonNode *t,char x[])	//求x单位的下一级单位数
{
	TSonNode *p;
	p=FindNode(t,x);
	if (p==NULL)
		return 0;
	else
		return ChildCount(p);
}
int LeafCount(TSonNode *t)			//求树中叶子结点个数
{
	int i,num=0;
	if (t==NULL)
		return 0;
	else
	{	if (t->sons[0]==NULL)	//t为叶子结点
			num++;
		else					//t不为叶子结点
		{	for (i=0;i<MaxSons;i++)
				if (t->sons[i]!=NULL)
					num+=LeafCount(t->sons[i]);
				else break;
		}
		return num;
	}
}
int Classnum(TSonNode *t,char x[])	//求x单位的班数
{
	TSonNode *p;
	p=FindNode(t,x);
	if (p==NULL)
		return 0;
	else
		return LeafCount(p);
}
int LeafSum(TSonNode *t)		//求树中叶子结点的数值和
{
	int i,sum=0;
	if (t==NULL)
		return 0;
	else
	{
		if (t->sons[0]==NULL)	//t为叶子结点
			return atoi(t->data);
		else					//t不为叶子结点
		{	for (i=0;i<MaxSons;i++)
				if (t->sons[i]!=NULL)
					sum+=LeafSum(t->sons[i]);
				else break;
		}
		return sum;
	}
}
int Studnum(TSonNode *t,char x[])	//求x单位的总学生人数
{
	TSonNode *p;
	p=FindNode(t,x);
	if (p==NULL)
		return 0;
	else
		return LeafSum(p);
}
int main()
{
	TSonNode *t;
	RecType R[MaxSize];
	int n;
	printf("(1)从abc.txt文件读数据到R数组中\n");
	ReadFile(R,n);
	if (n==0) return 1;				//记录个数为0时直接返回
	printf("(2)由数组R创建树t的孩子链存储结构\n");
	t=CreateTree(R[0].fname,R,n);	//创建一棵树
	printf("(3)输出树t:"); DispTree(t); printf("\n");
	printf("(4)计算机学院的专业数:%d\n",Sonnum(t,"计算机学院"));
	printf("(5)计算机学院的班数:%d\n",Classnum(t,"计算机学院"));
	printf("(6)电信学院的学生数:%d\n",Studnum(t,"电信学院"));
	printf("(7)销毁树t\n");
	DestroyTree(t);

	return 1;
}
