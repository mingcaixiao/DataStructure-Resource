//【例13.7】的程序:链表容器的使用
#include <iostream>
#include <list>
using namespace std;
int main()
{    list<int> lst;
	list<int>::iterator i,start,end;
	lst.push_back(5); lst.push_back(2); lst.push_back(4);
	lst.push_back(1); lst.push_back(3); lst.push_back(8);
	lst.push_back(6); lst.push_back(7);
	cout << "lst: ";
	for (i=lst.begin();i!=lst.end();i++)
		cout << *i << " ";
	cout << endl;
	i=lst.begin();
	start=++lst.begin();
	end=--lst.end();
	lst.insert(i,start,end);
	cout << "lst.insert(i,start,end)" << endl;
	cout << "lst: ";
	for (i=lst.begin();i!=lst.end();i++)
		cout << *i << " ";
	cout << endl;
	return 1;
}

