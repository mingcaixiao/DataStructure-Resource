//【例13.4】的程序:模板类的使用
#include <iostream>
using namespace std;
template <typename T>
class Array
{	int size;
	T *data;				//T为类型参数
public:
	Array(int);				//构造函数
	~Array();				//析构函数
	void setvalue();		//输入数组元素
	void dispvalue();		//输出所有数组元素
};
template <typename T>
Array<T>::Array(int n)		//构造函数
{	size=n;
	data=new T[n];			//为动态数组分配内存空间
}
template <typename T>
Array<T>::~Array()			//析构函数
{	delete [] data; }
template <typename T>
void Array<T>::setvalue()
{	cout << "(输入" << size << "个数据)" << endl;
	for (int i=0;i<size;i++)
	{	cout << "  第" << i+1 << "个数据:";
		cin >> data[i];
	}
}
template <typename T>
void Array<T>::dispvalue()
{	for (int i=0;i<size;i++)
		cout << data[i] << " ";
	cout << endl;
}
int main()
{	Array<char> ac(2);	//Array<char>为模板类,ac(2)定义模板类的对象
	cout << "建立一个字符数组";
	ac.setvalue();
	cout << "  数组的内容是:";
	ac.dispvalue();
	Array<int> ad(3);	//Array<int>为模板类,ad(3)定义模板类的对象
	cout << "建立一个整数数组:";
	ad.setvalue();
	cout << "  数组的内容是:";
	ad.dispvalue();
	return 1;
}
