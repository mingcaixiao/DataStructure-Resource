//文件名:exp12-1.cpp
#include <stdio.h>
#include <string.h>
#define N 10				//最多学生人数
typedef struct
{	int no;					//学号
	char name[10];			//姓名
	int age;				//年龄
	char sex[3];			//性别
	int deg1,deg2,deg3;		//课程1-课程3成绩
} StudType;
typedef struct
{	int no;					//学号
	char name[10];			//姓名
	int age;				//年龄
	char sex[2];			//性别
	int deg1,deg2,deg3;		//课程1-课程3成绩
	double avg;				//平均分
} StudType1;
void WriteFile(StudType st[],int n)		//将st数组中的学生记录写入到stud.dat文件中
{
	int i;
	FILE *fp;
	if ((fp=fopen("stud.dat","wb"))==NULL)
	{
		printf("\t提示:不能创建stud.dat文件\n");
		return;
	}
	for (i=0;i<n;i++)
		fwrite(&st[i],1,sizeof(StudType),fp);
	fclose(fp);
	printf("\t提示:文件stud.dat创建完毕\n");
}
void WriteFile1(StudType1 st1[],int n)	//将st1数组中的学生记录写入到stud1.dat文件中
{
	int i;
	FILE *fp;
	if ((fp=fopen("stud1.dat","wb"))==NULL)
	{
		printf("\t提示:不能创建stud1.dat文件\n");
		return;
	}
	for (i=0;i<n;i++)
		fwrite(&st1[i],1,sizeof(StudType),fp);
	fclose(fp);
	printf("\t提示:文件stud1.dat创建完毕\n");
}
void ReadFile(StudType st[],int &n)		//将stud.dat文件中的n个学生记录读入到st数组中
{
	FILE *fp;
	if ((fp=fopen("stud.dat","rb"))==NULL)
	{
		printf("\t提示:不能打开stud.dat文件\n");
		return;
	}
	n=0;
	while (fread(&st[n],sizeof(StudType),1,fp)==1)
		n++;
	printf("\t提示:文件stud.dat读取完毕\n");
}
void ReadFile1(StudType1 st1[],int &n)	//将stud1.dat文件中的n个学生记录读入到st1数组中
{
	FILE *fp;
	if ((fp=fopen("stud1.dat","rb"))==NULL)
	{
		printf("\t提示:不能打开stud1.dat文件\n");
		return;
	}
	n=0;
	while (fread(&st1[n],sizeof(StudType),1,fp)==1)
		n++;
	printf("\t提示:文件stud1.dat读取完毕\n");
}
void Display(StudType st[],int n)	//显示学生记录
{
	int i;
	printf("                ----学生成绩表----\n");
	printf("  学号     姓名   年龄 性别 语文 数学 英语\n");
	for (i=0;i<n;i++)
		printf("%5d%10s%6d%5s%5d%5d%5d\n",st[i].no,st[i].name,st[i].age,st[i].sex,st[i].deg1,st[i].deg2,st[i].deg3);
	printf("\n");
}
void Display1(StudType1 st1[],int n)	//显示求平均分后的学生记录
{
	int i;
	printf("                ----排序后学生成绩表----\n");
	printf("  学号     姓名   年龄 性别 语文 数学 英语 平均分\n");
	for (i=0;i<n;i++)
		printf("%5d%10s%6d%5s%5d%5d%5d%6.1f\n",st1[i].no,st1[i].name,st1[i].age,st1[i].sex,st1[i].deg1,st1[i].deg2,st1[i].deg3,st1[i].avg);
	printf("\n");
}
void Average(StudType st[],StudType1 st1[],int n)	//求平均分
{
	int i;
	for (i=0;i<n;i++)
	{
		st1[i].no=st[i].no;
		strcpy(st1[i].name,st[i].name);
		st1[i].age=st[i].age;
		strcpy(st1[i].sex,st[i].sex);
		st1[i].deg1=st[i].deg1;
		st1[i].deg2=st[i].deg2;
		st1[i].deg3=st[i].deg3;
		st1[i].avg=(st1[i].deg1+st1[i].deg2+st1[i].deg3)/3.0;
	}
}
void Sort(StudType1 st1[],int n)		//按平均分递减排序
{
	int i,j;
	StudType1 temp;
	for (i=1;i<n;i++)			//直接插入排序
	{
		temp=st1[i];
		for (j=i-1;j>=0 && temp.avg>st1[j].avg;j--)
			st1[j+1]=st1[j];
		st1[j+1]=temp;
	}
}
int main()
{
	int n=8;
	StudType st[]={{1,"陈华",20,"男",78,90,84},
	{5,"张明",21,"男",78,68,92},
	{8,"王英",20,"女",86,81,86},
	{3,"刘丽",21,"女",78,92,88},
	{2,"许可",20,"男",80,83,78},
	{4,"陈军",20,"男",78,88,82},
	{7,"马胜",21,"男",56,67,75},
	{6,"曾强",20,"男",78,89,82}};
	StudType1 st1[N];
	printf("操作过程如下:\n");
	printf("  (1)将st数组中学生记录写入stud.dat文件\n");
	WriteFile(st,n);
	printf("  (2)将stud.dat文件中学生记录读入到st数组中\n");
	ReadFile(st,n);
	printf("  (3)显示st数组中的学生记录\n");
	Display(st,n);
	printf("  (4)求学生的平均分并放在st1数组中\n");
	Average(st,st1,n);
	printf("  (5)对st1数组按平均分递减排序\n");
	Sort(st1,n);
	printf("  (6)将st1数组中学生记录写入stud1.dat文件\n");
	WriteFile1(st1,n);
	printf("  (7)将stud1.dat文件中学生记录读入到st1数组中\n");
	ReadFile1(st1,n);
	printf("  (8)显示st1数组中的学生记录\n");
	Display1(st1,n);
	return 1;
}
