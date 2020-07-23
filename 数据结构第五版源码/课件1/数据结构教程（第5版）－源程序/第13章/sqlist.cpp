//顺序表类模板
#include <iostream>
using namespace std;
template <typename T>
class SqList					//顺序表类
{	T *pelem;
   	int length;
public:
	SqList(int n)				//构造函数,用于初始化单链表
	{
		pelem=new T[n];
		length=0; 
	}
	~SqList()					//析构函数,用于释放分配的空间
	{
		delete pelem;
	}
	bool ListEmpty()			//判断线性表是否为空表
	{
		return(length==0); 
	}
	int ListLength()			//求线性表的长度
	{
		return(length);
	}
	void DispList()			//输出线性表
	{
		int i;
		if (ListEmpty()) return;
		cout << "顺序表:";
		for (i=0;i<length;i++)
			cout << pelem[i] << " ";
		cout << endl;
	}
	bool GetElem(int i,T &e)	//求线性表中某个数据元素值
	{
		if (i<1 || i>length)
			return false;
		e=pelem[i-1];
		return true;
	}
	int LoacteElem(T e)		//按元素值查找
	{
		int i=0;
		while (i<length && pelem[i]!=e) i++;
		if (i>=length)
			return 0;
		else
			return i+1;
	}
	bool ListInsert(int i,T e)	//插入数据元素
	{	int j;
		if (i<1 || i>length+1)
			return false;
		i--;						//将顺序表位序转化为pelem下标
		for (j=length;j>i;j--)		//将pelem[i]及后面元素后移一个位置
			pelem[j]=pelem[j-1];
		pelem[i]=e;
		length++;					//顺序表长度增1
		return true;
	}
	bool ListDelete(int i,T &e)//删除数据元素
	{	int j;
		if (i<1 || i>length) return false;
		i--;						//将顺序表位序转化为pelem下标
		e=pelem[i];
		for (j=i;j<length-1;j++)
			pelem[j]=pelem[j+1];
		length--;
		return true;
	}
};
int main()
{
	char e;int i;
	SqList<char> s(10);			//定义一个字符顺序表对象s
	s.ListInsert(1,'a');
	s.ListInsert(2,'b');
	s.ListInsert(3,'c');
	s.ListInsert(4,'d');
	s.DispList();
	s.GetElem(2,e);
	cout << "第2个节点值:" << e << endl;
	i=s.LoacteElem('d');
	cout << "数据值为d的节点序号为" << i << endl;
	cout << "删除第2个节点" << endl;
	s.ListDelete(2,e);
	s.DispList();
	cout << "删除第3个节点" << endl;
	s.ListDelete(3,e);
	s.DispList();
	cout << "插入e作为第1个节点" << endl;
	s.ListInsert(1,'e');
	s.DispList();
	cout << "插入f作为第3个节点" << endl;
	s.ListInsert(3,'f');
	s.DispList();
	return 1;
}
