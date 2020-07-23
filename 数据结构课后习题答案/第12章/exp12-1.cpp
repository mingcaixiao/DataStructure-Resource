//文件名:exp12-1.cpp
#include <stdio.h>
typedef struct
{	int no;					//学号
	char name[10];			//姓名
	int age;				//年龄
	char sex[3];			//性别
	int deg1,deg2,deg3;		//课程1-课程3成绩
} StudType;
void CreateFile()			//用st数组的学生记录创建stud.dat文件
{
	int n=8;
	StudType st[]={
		{1,"陈华",20,"男",78,90,84},
		{5,"张明",21,"男",78,68,92},
		{8,"王英",20,"女",86,81,86},
		{3,"刘丽",21,"女",78,92,88},
		{2,"许可",20,"男",80,83,78},
		{4,"陈军",20,"男",78,88,82},
		{7,"马胜",21,"男",56,67,75},
		{6,"曾强",20,"男",78,89,82} };
	FILE *fp;
	if ((fp=fopen("stud.dat","wb"))==NULL)
	{
		printf("\t提示:不能创建stud.dat文件\n");
		return;
	}
	for (int i=0;i<n;i++)
		fwrite(&st[i],1,sizeof(StudType),fp);
	fclose(fp);
	printf("   提示:文件stud.dat创建完毕\n");
}

bool Findi(StudType &s,int i)		//在stud.dat文件中查找序号为i的学生记录s
{
	FILE *fp;
	if (i<=0) return false;			//i错误返回假
	if ((fp=fopen("stud.dat","rb"))==NULL)
	{
		printf("\t提示:不能打开stud.dat文件\n");
		return false;
	}
	fseek(fp,(i-1)*sizeof(StudType),SEEK_SET);	//定位在第i个记录之前
	if (fread(&s,sizeof(StudType),1,fp)==1)
	{
		fclose(fp);
		return true;				//成功读取第i个记录,返回真
	}
	else
	{
		fclose(fp);
		return false;				//不能读取第i个记录,返回假
	}
}

bool Findno(StudType &s,int no)		//在stud.dat文件中查找学号为no的学生记录s
{
	FILE *fp;
	if ((fp=fopen("stud.dat","rb"))==NULL)
	{
		printf("\t提示:不能打开stud.dat文件\n");
		return false;
	}
	fseek(fp,0,SEEK_SET);				//定位在文件开头
	while (fread(&s,sizeof(StudType),1,fp)==1)
	{
		if (s.no==no)				//找到学号为no的记录，返回真
		{
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;					//没有找到学号为no的记录，返回假
}

void DispaStud(StudType s)			//显示一个学生记录s
{
	printf("  学号     姓名   年龄 性别 语文 数学 英语\n");
	printf("%5d%10s%6d%5s%5d%5d%5d\n",s.no,s.name,s.age,s.sex,s.deg1,s.deg2,s.deg3);
}
int main()
{
	int i,no;
	StudType s;
	printf("操作过程如下:\n");
	printf("  (1)创建学生记录stud.dat文件\n");
	CreateFile();
	printf("  (2)按序号查找，输入序号:");
	scanf("%d",&i);
	if (Findi(s,i))
		DispaStud(s);
	else
		printf("    >文件不能打开或者输入的记录序号错误n\n");
	printf("  (3)按学号查找，输入学号:");
	scanf("%d",&no);
	if (Findno(s,no))
		DispaStud(s);
	else
		printf("    >文件不能打开或者输入的学号错误\n");
	return 1;
}
