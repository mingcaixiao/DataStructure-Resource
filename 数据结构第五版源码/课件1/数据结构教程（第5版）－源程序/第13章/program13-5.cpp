//【例13.5】的程序:向量容器的使用
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	vector<int> v(3);						//定义初始长度为3的整数容器
	v[0]=5;									//下标0处放置元素5
	v[1]=2;									//下标1处放置元素2
	v.push_back(7);							//在尾部插入元素7
	vector<int>::iterator first=v.begin();	//让first指向开头元素
	vector<int>::iterator last=v.end();		//让last指向尾部元素
	while (first!=last)						//循环输出所有元素
		cout << *first++ << " ";
	cout << endl;
	return 1;
}

