//【例13.2】的程序:构造函数的使用
#include <iostream>
using namespace std;
class Sample2
{
	int value;
public:
	Sample2() { value=0; }			//构造函数
	Sample2(int v) { value=v; }		//重载构造函数
	int getvalue() { return value; }
	void setvalue(int v) { value=v; }
};
int main()
{
	Sample2 a[10]={0,1,2,3,4,5,6,7,8,9},b[10];
	cout << "输出a:" << endl;
	for (int i=0;i<10;i++)
	{
		cout << "a[" << i << "]=" << a[i].getvalue() << " ";
		if ((i+1)%5==0)				//每输出5个元素换一行
			cout << endl;
	}
	cout << "输出b:" << endl;
	for (int i=0;i<10;i++)
	{	
		cout << "b[" << i << "]=" << b[i].getvalue() << " ";
		if ((i+1)%5==0)				//每输出5个元素换一行
			cout << endl;
	}
	return 1;
}
