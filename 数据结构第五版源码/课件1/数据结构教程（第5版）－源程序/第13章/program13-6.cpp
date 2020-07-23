//【例13.6】的程序:双端队列容器的使用
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
void disp(deque<int> &dq);
int main()
{
	deque<int> dq;			//建立一个双端队列dq
	dq.push_front(1);			//队头插入1
	dq.push_back(2);			//队尾插入2
	dq.push_front(3);			//队头插入3
	dq.push_back(4);			//队尾插入4
	disp(dq);
	dq.pop_front();			//删除队头元素
	dq.pop_back();			//删除队尾元素
	disp(dq);
	return 1;
}
void disp(deque<int> &dq)
{
	deque<int>::iterator iter;
	for (iter=dq.begin();iter!=dq.end();iter++)
		cout << *iter << " ";
	cout << endl;
}
