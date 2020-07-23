//文件名:exp7-3.cpp
#include "btree.cpp"				//包含二叉树的基本运算算法
#define MaxWidth 40
BTNode *CreateBT1(char *pre,char *in,int n)
{	BTNode *b;
	char *p;
	int k;
	if (n<=0) return NULL;
	b=(BTNode *)malloc(sizeof(BTNode));		//创建二叉树结点*b
	b->data=*pre;
	for (p=in;p<in+n;p++)					//在中序序列中找等于*pre的位置k
		if (*p==*pre)						//pre指向根结点
			break;						//在in中找到后退出循环
	k=p-in;								//确定根结点在in中的位置
	b->lchild=CreateBT1(pre+1,in,k);			//递归构造左子树
	b->rchild=CreateBT1(pre+k+1,p+1,n-k-1); 	//递归构造右子树
	return b;
}
BTNode *CreateBT2(char *post,char *in,int n)
{	BTNode *b;
	char r,*p;
	int k;
	if (n<=0) return NULL;
	r=*(post+n-1);						//根结点值
	b=(BTNode *)malloc(sizeof(BTNode));		//创建二叉树结点*b
	b->data=r;
	for (p=in;p<in+n;p++)					//在in中查找根结点
		if (*p==r)	break;
	k=p-in;								//k为根结点在in中的下标
	b->lchild=CreateBT2(post,in,k);			//递归构造左子树
	b->rchild=CreateBT2(post+k,p+1,n-k-1);	//递归构造右子树
	return b;
}

void DispBTree1(BTNode *b)  //以凹入表表示法输出一棵二叉树
{
	BTNode *St[MaxSize],*p;
	int level[MaxSize][2],top=-1,n,i,width=4;
	char type;
	if (b!=NULL)
	{
		top++;
		St[top]=b;						//根结点入栈
		level[top][0]=width;
		level[top][1]=2;				//2表示是根
		while (top>-1)
		{
			p=St[top];					//退栈并凹入显示该结点值
			n=level[top][0];
			switch(level[top][1])
			{
			case 0:type='L';break;		//左结点之后输出(L)
			case 1:type='R';break;		//右结点之后输出(R)
			case 2:type='B';break;		//根结点之后前输出(B)
			}
			for (i=1;i<=n;i++)			//其中n为显示场宽,字符以右对齐显示
				printf(" ");
			printf("%c(%c)",p->data,type);
			for (i=n+1;i<=MaxWidth;i+=2)
				printf("--");
			printf("\n");
			top--;
			if (p->rchild!=NULL)
			{							//将右子树根结点入栈
				top++;
				St[top]=p->rchild;
				level[top][0]=n+width;	//显示场宽增width
				level[top][1]=1;		//1表示是右子树
			}
			if (p->lchild!=NULL)
			{							//将左子树根结点入栈
				top++;
				St[top]=p->lchild;
				level[top][0]=n+width;  //显示场宽增width
				level[top][1]=0;        //0表示是左子树
			}
		}
	}
}

int main()
{
	BTNode *b;
	ElemType pre[]="ABDEHJKLMNCFGI";
	ElemType in[]="DBJHLKMNEAFCGI";
	ElemType post[]="DJLNMKHEBFIGCA";
	int n=14;
	b=CreateBT1(pre,in,n);
	printf("先序序列:%s\n",pre);
	printf("中序序列:%s\n",in);
	printf("构造一棵二叉树b:\n");
	printf("  括号表示法:");DispBTree(b);printf("\n");
	printf("  凹入表示法:\n");DispBTree1(b);printf("\n\n");
	printf("中序序列:%s\n",in);
	printf("后序序列:%s\n",post);
	b=CreateBT2(post,in,n);
	printf("构造一棵二叉树b:\n");
	printf(" 括号表示法:");DispBTree(b);printf("\n");
	printf(" 凹入表示法:\n");DispBTree1(b);printf("\n");
	DestroyBTree(b);
	return 1;
}
