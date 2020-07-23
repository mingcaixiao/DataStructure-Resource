//【例13.1】的程序:类的定义
#include <iostream>
using namespace std;
class Sample  					//定义类Sample
{
private:
    int x,y; 						//数据成员
public:
    void setvalue(int x1,int y1); 	//成员函数
    void display();
};
void Sample::setvalue(int x1,int y1) { x=x1;y=y1; }
void Sample::display()
{
    cout << "x=" << x << ",y=" << y << endl;
}
