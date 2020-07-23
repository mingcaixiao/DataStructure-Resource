//【例13.9】的程序:队列容器的使用
#include <iostream>
#include <queue>
using namespace std;
int main()
{	queue<int> q;
	q.push(1); q.push(2); q.push(3);
	cout << q.front() << " "; 
	q.pop(); cout << q.front() << " ";  q.pop();
	q.push(4); q.push(5);
	q.pop();
	while (!q.empty())   //队不空时出队
	{	cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
	return 1;
}

