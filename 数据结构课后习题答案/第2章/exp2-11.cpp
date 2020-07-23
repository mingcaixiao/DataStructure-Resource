//文件名:exp2-11.cpp
#include <stdio.h>
#include <malloc.h>
typedef struct
{
	int no;						//职工号
	char name[10];				//姓名
	int depno;					//部门号
	float salary;				//工资数
} EmpType;						//职工类型
typedef struct node
{
	EmpType data;				//存放职工信息
	struct node *next;			//指向下一个结点的指针
}  EmpList;						//职工单链表结点类型
void DestroyEmp(EmpList *&L)	//释放职工单链表L
{
	EmpList *pre=L,*p=pre->next;
	while (p!=NULL)
	{
		free(pre);
		pre=p;
		p=p->next;
	}
	free(pre);
}
void DelAll(EmpList *&L)		//删除职工文件中全部记录
{
	FILE *fp;
	if ((fp=fopen("emp.dat","wb"))==NULL)	//重写清空emp.dat文件
	{	
		printf("  提示:不能打开职工文件\n");
		return;
	}
	fclose(fp);
	DestroyEmp(L);						//释放职工单链表L
	L=(EmpList *)malloc(sizeof(EmpList));	
	L->next=NULL;						//建立一个空的职工单链表L
	printf("  提示:职工数据清除完毕\n");
}
void ReadFile(EmpList *&L)		//读emp.dat文件建立职工单键表L
{
	FILE *fp;
	EmpType emp;
	EmpList *p,*r;
	int n=0;
	L=(EmpList *)malloc(sizeof(EmpList));	//建立头结点
	r=L;
	if ((fp=fopen("emp.dat","rb"))==NULL) //不存在emp.dat文件
	{	
		 if ((fp=fopen("emp.dat","wb"))==NULL) 
			 printf("  提示:不能创建emp.dat文件\n");
	}
	else		//若存在emp.dat文件
	{
		while (fread(&emp,sizeof(EmpType),1,fp)==1)
		{	//采用尾插法建立单链表L
			p=(EmpList *)malloc(sizeof(EmpList));
			p->data=emp;
			r->next=p;
			r=p;
			n++;
		}
	}
	r->next=NULL;
	printf("  提示:职工单键表L建立完毕,有%d个记录\n",n);
	fclose(fp);
}
void SaveFile(EmpList *L)	//将职工单链表数据存入数据文件
{
	EmpList *p=L->next;
	int n=0;
	FILE *fp;
	if ((fp=fopen("emp.dat","wb"))==NULL) 
	{	
		printf("  提示:不能创建文件emp.dat\n");
		return;
	}
	while (p!=NULL)
	{
		fwrite(&p->data,sizeof(EmpType),1,fp);
		p=p->next;
		n++;
	}
	fclose(fp);
	DestroyEmp(L);				//释放职工单链表L
	if (n>0)
		printf("  提示:%d个职工记录写入emp.dat文件\n",n);
	else
		printf("  提示:没有任何职工记录写入emp.dat文件\n");
}
void InputEmp(EmpList *&L)	//添加一个职工记录
{
	EmpType p;
	EmpList *s;
	printf("  >>输入职工号(-1返回):");
	scanf("%d",&p.no);
	if (p.no==-1) return;
	printf("  >>输入姓名 部门号 工资:");
	scanf("%s%d%f",&p.name,&p.depno,&p.salary);
	s=(EmpList *)malloc(sizeof(EmpList));
	s->data=p;
	s->next=L->next;		//采用头插法插入结点s
	L->next=s;
	printf("  提示:添加成功\n");
}

void DelEmp(EmpList *&L)	//删除一个职工记录
{
	EmpList *pre=L,*p=L->next;
	int no;
	printf("  >>输入职工号(-1返回):");
	scanf("%d",&no);
	if (no==-1) return;
	while (p!=NULL && p->data.no!=no)
	{
		pre=p;
		p=p->next;
	}
	if (p==NULL)
		printf("  提示:指定的职工记录不存在\n");
	else
	{
		pre->next=p->next;
		free(p);
		printf("  提示:删除成功\n");
	}
}
void Sortno(EmpList *&L)	//采用直接插入法单链表L按no递增有序排序
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.no<p->data.no)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  提示:按no递增排序完毕\n");
}
void Sortdepno(EmpList *&L) //采用直接插入法单链表L按depno递增有序排序
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.depno<p->data.depno)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  提示:按depno递增排序完毕\n");
}
void Sortsalary(EmpList *&L) //采用直接插入法单链表L按salary递增有序排序
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.salary<p->data.salary)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  提示:按salary递增排序完毕\n");
}
void DispEmp(EmpList *L)	//输出所有职工记录
{
	EmpList *p=L->next;
	if (p==NULL)
		printf("  提示:没有任何职工记录\n");
	else
	{
		printf("    职工号  姓名  部门号       工资\n");
		printf("   ----------------------------------\n");
		while (p!=NULL)
		{
			printf("  %3d%10s    %-8d%7.2f\n",p->data.no,p->data.name,p->data.depno,p->data.salary);
			p=p->next; 
		}
		printf("   ----------------------------------\n");
	}
}
int main()
{
	EmpList *L;
	int sel;
	printf("由emp.dat文件建立职工单键表L\n");
	ReadFile(L);
	do
	{	
		printf(">1:添加 2:显示 3:按职工号排序 4:按部门号排序 5:按工资数排序\n");
		printf(">6:删除 9:全删 0:退出 请选择:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 9:
			DelAll(L);
			break;
		case 1:
			InputEmp(L);
			break;
		case 2:
			DispEmp(L);
			break;
		case 3:
			Sortno(L);
			break;
		case 4:
			Sortdepno(L);
			break;
		case 5:
			Sortsalary(L);
			break;
		case 6:
			DelEmp(L);
			break;
		}
	} while (sel!=0);
	SaveFile(L);
	return 1;
}
