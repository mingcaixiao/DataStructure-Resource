//文件名:exp7-9.cpp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 30			//栈的最大元素个数
#define NAMEWIDTH 10		//姓名的最多字符个数
typedef struct fnode
{
	char father[NAMEWIDTH];	//父
	char wife[NAMEWIDTH];	//母
	char son[NAMEWIDTH];	//子
} FamType;					//家谱文件的记录类型
typedef struct tnode
{
	char name[NAMEWIDTH];
	struct tnode *lchild,*rchild;
} BTree;					//家谱二叉树结点树类型
int n;						//家谱记录个数
FamType fam[MaxSize];		//家谱记录数组
//----家谱二叉树操作算法-----------------------------------
BTree *CreateBTree(char *root)	//从fam(含n个记录)递归创建一棵二叉树
{
	int i=0,j;
	BTree *b,*p;
	b=(BTree *)malloc(sizeof(BTree));			//创建父亲结点
	strcpy(b->name,root);
	b->lchild=b->rchild=NULL;
	while (i<n && strcmp(fam[i].father,root)!=0) 
		i++;
	if (i<n)									//找到了该姓名的记录
	{
		p=(BTree *)malloc(sizeof(BTree));		//创建母亲结点
		p->lchild=p->rchild=NULL;
		strcpy(p->name,fam[i].wife);
		b->lchild=p;
		for (j=0;j<n;j++)						//找所有儿子
			if (strcmp(fam[j].father,root)==0)	//找到一个儿子
			{
				p->rchild=CreateBTree(fam[j].son);
				p=p->rchild;
			}
	}
	return(b);
}
void DispTree(BTree *b)	//以括号表示法输出二叉树
{
	if (b!=NULL)
	{
		printf("%s",b->name);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{
			printf("(");
			DispTree(b->lchild);
			if (b->rchild!=NULL) 
				printf(",");
			DispTree(b->rchild);
			printf(")");
		}
	}
}
BTree *FindNode(BTree *b,char xm[]) //采用先序递归算法找name为xm的结点
{
	BTree *p;
	if (b==NULL) 
		return(NULL);
	else
	{
		if (strcmp(b->name,xm)==0)
			return(b);
		else
		{
			p=FindNode(b->lchild,xm);
			if (p!=NULL) 
				return(p);
			else 
				return(FindNode(b->rchild,xm));
		}
	}
}
void FindSon(BTree *b)		//输出某人的所有儿子
{
	char xm[NAMEWIDTH];
	BTree *p;
	printf("  >>父亲姓名:");
	scanf("%s",xm);
	p=FindNode(b,xm);
	if (p==NULL)
		printf("  >>不存在%s的父亲!\n",xm);
	else
	{
		p=p->lchild;
		if (p==NULL)
			printf("  >>%s没有妻子\n",xm);
		else
		{
			p=p->rchild;
			if (p==NULL)
				printf("  >>%s没有儿子!\n",xm);
			else
			{
				printf("  >>%s的儿子:",xm);
				while (p!=NULL)
				{
					printf("%10s",p->name);
					p=p->rchild;
				}
				printf("\n");
			}
		} 
	}
}
int Path(BTree *b,BTree *s)		//采用后序非递归遍历方法输出从根结点到s结点的路径
{
	BTree *St[MaxSize];
	BTree *p;
	int i,top=-1;					//栈指针置初值
	bool flag;
	do
	{
		while (b)                 	//将b的所有左下结点进栈
		{	
			top++;
			St[top]=b;
			b=b->lchild;
		}
		p=NULL;                   	//p指向当前结点的前一个已访问的结点
		flag=true;					//flag为真表示正在处理栈顶结点
		while (top!=-1 && flag)
		{	
			b=St[top];          	//取出当前的栈顶元素
			if (b->rchild==p)		//右子树不存在或已被访问,访问之
			{	if (b==s)			//当前访问的结点为要找的结点,输出路径
				{	
					printf("  >>所有祖先:");
					for (i=0;i<top;i++) 
					   	printf("%s ",St[i]->name);
					printf("\n");
				   	return 1;
				}
				else
				{	
					top--;
				   	p=b;			//p指向则被访问的结点
				}
			}
			else
			{	
				b=b->rchild;		//b指向右子树
				flag=false;         //表示当前不是处理栈顶结点
			}
		}
	} while (top!=-1);				//栈不空时循环
	return 0;						//其他情况时返回0
}
void Ancestor(BTree *b)				//输出某人的所有祖先
{
	BTree *p;
	char xm[NAMEWIDTH];
	printf("  >>输入姓名:");
	scanf("%s",xm);
	p=FindNode(b,xm);
	if (p!=NULL)
		Path(b,p);
	else
		printf("  >>不存在%s\n",xm);
}
void DestroyBTree(BTree *b)		//销毁家谱二叉树
{
	if (b!=NULL)
	{
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
		
//----家谱文件操作算法---------------------------------------------
void DelAll()					//清除家谱文件全部记录
{
	FILE *fp;
	if ((fp=fopen("fam.dat","wb"))==NULL) 
	{	
		printf("  >>不能打开家谱文件\n");
		return;
	}
	n=0;
	fclose(fp);
}
void ReadFile()				//读家谱文件存入fam数组中
{
	FILE *fp;
	long len;
	int i;
	if ((fp=fopen("fam.dat","rb"))==NULL) 
	{
		n=0;
		return;
	}
	fseek(fp,0,2);				//家谱文件位置指针移到家谱文件尾
	len=ftell(fp);    			//len求出家谱文件长度
	rewind(fp);					//家谱文件位置指针移到家谱文件首
	n=len/sizeof(FamType); 		//n求出家谱文件中的记录个数
	for (i=0;i<n;i++)
		fread(&fam[i],sizeof(FamType),1,fp);//将家谱文件中的数据读到fam中
	fclose(fp);
}
void SaveFile()					//将fam数组存入数据家谱文件
{
	int i;
	FILE *fp;
	if ((fp=fopen("fam.dat","wb"))==NULL) 
	{	
		printf("  >>数据家谱文件不能打开\n");
		return;
	}
	for (i=0;i<n;i++)
		fwrite(&fam[i],sizeof(FamType),1,fp);
	fclose(fp);
}
void InputFam()					//添加一个记录
{
	printf("  >>输入父亲、母亲和儿子姓名:");
	scanf("%s%s%s",fam[n].father,fam[n].wife,fam[n].son);
	n++;
}
void OutputFile()				//输出家谱文件全部记录
{
	int i;
	if (n<=0)
	{
		printf("  >>没有任何记录\n");
		return;
	}
	printf("         父亲     母亲      儿子\n");
	printf("       ------------------------------\n");
	for (i=0;i<n;i++)
		printf("  %10s%10s%10s\n",fam[i].father,fam[i].wife,fam[i].son);
	printf("       ------------------------------\n");
}
//---------------------------------------------------------------------
void Fileop()		//家谱文件操作
{
	int sel;
	do 
	{
		printf(" >1:输入 2:输出 9:全清 0:存盘返回 请选择:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 9:
			DelAll();
			break;
		case 1:
			InputFam();
			break;
		case 2:
			OutputFile();
			break;
		case 0:
			SaveFile();
			break;
		} 
	} while (sel!=0);
}
void BTreeop()		//家谱二叉树操作
{
	BTree *b;
	int sel;
	if (n==0) return;				//家谱记录为0时直接返回
	b=CreateBTree(fam[0].father);
	do 
	{
		printf(" >1:括号表示法 2.找某人所有儿子 3.找某人所有祖先 0:返回 请选择:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 1:
			printf("  >>");DispTree(b);printf("\n");
			break;
		case 2:
			FindSon(b);
			break;
		case 3:
			printf("  >>");Ancestor(b);
			break;
		} 
	} while (sel!=0);
	DestroyBTree(b);		//销毁家谱二叉树
}
int main()
{
	BTree *b;
	int sel;
	ReadFile();
	do
	{	
		printf("*1.文件操作 2:家谱操作 0:退出 请选择:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 1:
			Fileop();
			break;
		case 2:
			BTreeop();
			break;
		}
	} while (sel!=0);
	return 1;
}
