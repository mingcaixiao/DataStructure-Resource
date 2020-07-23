//文件名:exp12_2.cpp
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MaxRec 100  		//最多的记录个数
typedef struct Index 		//定义索引文件结构
{
	int no;					//学号
	long offset;			//主文件中的记录号
} Index;
typedef struct
{	int no;					//学号
	char name[10];			//姓名
	int age;				//年龄
	char sex[3];			//性别
	int deg1,deg2,deg3;		//课程1-课程3成绩
} StudType;
void InsertSort(Index R[],int n) //采用直接插入排序法对R[0..n-1]按学号递增排序
{
	int i,j;
	Index temp;
	for (i=1;i<n;i++) 
	{
		temp=R[i];
		j=i-1; 
		while (j>=0 && temp.no<R[j].no) 
		{ 	
			R[j+1]=R[j];	//将关键字大于R[i].key的记录后移
			j--;
		}
		R[j+1]=temp;		//在j+1处插入R[i]
	}
}
void CreatIdxFile()			//建立索引文件
{
	FILE *mfile,*idxfile;
	Index idx[MaxRec];
	StudType st;
	int n=0,i;
	if ((mfile=fopen("stud.dat","rb"))==NULL) 
	{
	    printf("  提示:不能打开主文件\n");
		return;
	}
	if ((idxfile=fopen("index.dat","wb"))==NULL) 
	{
	    printf("  提示:不能建立索引文件\n");
		return;
	}
	i=0;
   	while ((fread(&st,sizeof(StudType),1,mfile))!=NULL)
	{
		idx[i].no=st.no;
		idx[i].offset=++n;
		i++;
	}
	InsertSort(idx,n);	//对idx数组按no值排序
	rewind(idxfile);
	for (i=0;i<n;i++)
		fwrite(&idx[i],sizeof(Index),1,idxfile);
	fclose(mfile);
	fclose(idxfile);
	printf("  提示:索引文件建立完毕\n");
}
void OutputMainFile()	//输出主文件全部记录
{
 	FILE *mfile;
	StudType st;
	int i=1;
	if ((mfile=fopen("stud.dat","rb"))==NULL)
	{
		printf("  提示:不能读主文件\n");
		return;
	}
	printf("                ----学生成绩表----\n");
	printf("记录号  学号     姓名   年龄 性别 语文 数学 英语\n");
   	while ((fread(&st,sizeof(StudType),1,mfile))==1)
	{
		printf("%6d%5d%10s%6d%5s%5d%5d%5d\n",i,st.no,st.name,st.age,st.sex,st.deg1,st.deg2,st.deg3);
		i++;
	}
	fclose(mfile);
}
void OutputIdxFile()	//输出索引文件全部记录
{
 	FILE *idxfile;
	Index irec;
	int i=0;
	printf("     ----学生索引表----\n");
	printf("\t学号  记录号\n");
	if ((idxfile=fopen("index.dat","rb"))==NULL)
	{
		printf("  提示:不能读索引文件\n");
		return;
	}
   	while ((fread(&irec,sizeof(Index),1,idxfile))==1)
		printf("\t%5d%6d\n",irec.no,irec.offset);
	fclose(idxfile);
}
void ReadIndexFile(Index idx[MaxRec],int &n)	//读索引文件数据存入idx数组中
{
	int j;
	FILE *idxfile;
	if ((idxfile=fopen("index.dat","rb"))==NULL) 
	{
	    printf("  提示:索引文件不能打开\n");
		return;
	}
	fseek(idxfile,0,2); 
	j=ftell(idxfile);    	//j求出文件长度
	rewind(idxfile);
	n=j/sizeof(Index); 		//n求出文件中的记录个数
	fread(idx,sizeof(Index),n,idxfile);
	fclose(idxfile);
}
int SearchNum(Index idx[],int n,int no)	//在含有n个记录的索引文件idx中查找学号为no的记录对应的记录号
{
	int mid,low=0,high=n-1;
	while (low<=high)    				//二分查找
	{
		mid=(low+high)/2;
		if (idx[mid].no>no) 
			high=mid-1;
		else if (idx[mid].no<no) 
			low=mid+1;
		else	//idx[mid].no==no
			return idx[mid].offset;
	}
	return -1;
}
void FindStudent()			//输出指定学号的记录
{
	int no;
	FILE *mfile;
	Index idx[MaxRec];
	StudType st;
	int i,n;
	if ((mfile=fopen("stud.dat","rb+"))==NULL)
	{
		printf("  提示:主文件中没有任何记录\n");
		return;
	}
	ReadIndexFile(idx,n);		//读取索引数组idx
	printf("  输入学号:");	
	scanf("%d",&no);		
	i=SearchNum(idx,n,no);		//在idx中查找
	if (i==-1)
		printf("  提示:学号%d不存在\n",no);
	else 
	{
		fseek(mfile,(i-1)*sizeof(StudType),SEEK_SET); //由记录号直接跳到主文件中对应的记录
		fread(&st,sizeof(StudType),1,mfile);
		printf("%5d%10s%6d%5s%5d%5d%5d\n",st.no,st.name,st.age,st.sex,st.deg1,st.deg2,st.deg3);
	}
	fclose(mfile);
}
void WriteFile(int n)  //将st数组中的n个学生记录写入stud.dat文件中
{
	StudType st[]={{1,"陈华",20,"男",78,90,84},
	{5,"张明",21,"男",78,68,92},
	{8,"王英",20,"女",86,81,86},
	{3,"刘丽",21,"女",78,92,88},
	{2,"许可",20,"男",80,83,78},
	{4,"陈军",20,"男",78,88,82},
	{7,"马胜",21,"男",56,67,75},
	{6,"曾强",20,"男",78,89,82}};
	int i;
	FILE *fp;
	if ((fp=fopen("stud.dat","wb"))==NULL)
	{	printf("\t提示:不能创建stud.dat文件\n");
		return;
	}
	for (i=0;i<n;i++)
		fwrite(&st[i],1,sizeof(StudType),fp);
	fclose(fp);
	printf("  提示:文件stud.dat创建完毕\n");
}
int main()
{
	int n=8,sel;		//n为实际学生人数
	printf("建立主文件\n");
	WriteFile(n);		//建立主文件
	do
	{
		printf("1:输出主文件 2:建索引文件 3:输出索引文件 4:按学号查找 0:退出:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 1:
			OutputMainFile();
			break;
		case 2:
			CreatIdxFile();
			break;
		case 3:
			OutputIdxFile();
			break;
		case 4:
			FindStudent();
			break;
		}
	} while (sel!=0);
	return 1;
}
