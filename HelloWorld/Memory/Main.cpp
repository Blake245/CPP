#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <map>
void f2();

void f(int* v)
{
	*v = 99;
}

void f3(const int& v)
{
	//v = 98;
}

void f2()
{
	int num2[100000];
	f2();
}


int main()
{
	int i = 15;
	float b = 2.5f;
	int i1 = 7;

	int* p1 = nullptr;
	p1 = &i;
	p1 = &i1;

	int& r = i;
	r = i1;

	f(&i);
	f3(i);
	int* p = new int(5);
	
	*p = 6;

	int* texture = new int[1000];
	texture[0] = 20;
	texture[1] = 65;
	std::cout << &texture[0] << std::endl;
	std::cout << *(texture + 1) << std::endl;
	std::cout << *p << std::endl;

	std::cout << i << std::endl;
	delete p;

	//containers
	int a[10]; //stack
	int* ap = new int[10]; //heap

	std::vector<int> v;
	v.push_back(5);
	v.push_back(6);
	v.push_back(8);
	v.push_back(10);

	std::list<int> l;
	l.push_back(4);
	l.push_back(2);
	l.push_back(7);
	l.remove(2);

	std::stack<int> s;
	s.push(15);
	s.push(17);
	s.push(19);
	s.pop();
	std::cout << s.top() << std::endl;

	std::map<std::string, float> students;
	students["blake"] = 4.0f;
	students["jason"] = 3.5f;

	std::cout << students["jason"] << std::endl;
}