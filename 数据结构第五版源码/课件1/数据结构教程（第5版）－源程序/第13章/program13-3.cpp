//【例13.3】的程序:析构函数的使用
#include <iostream>
using namespace std;
class Sample3
{
    int x,y;
public:
    Sample3(int x1,int y1)	//构造函数
    {	x=x1;y=y1;  }
    ~Sample3()				//析构函数
    {	cout << "调用析构函数." << endl; }
    void dispoint()
    {	cout << "(" << x << "," << y << ")" << endl; }
};
int main()
{
	Sample3 a(12,6),*p=new Sample3(5,12);	//对象指针指向创建的无名对象
	cout << "First point=>";
	a.dispoint();
	cout << "Second point=>";
	p->dispoint();
	//delete p;
	return 1;
}
