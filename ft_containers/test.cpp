#include "vector.hpp"
#include <vector>
#include <iostream>

struct test_s
{
	int a;
	std::string s;
};
int main() {

	ft::vector<int> v;
	ft::vector<int>::iterator iter;
	int a = int();
	a = 10;
	//std::cout << a;
	std::vector<int> v_i;
	std::vector<double> v_d;
	v_d.push_back(4.2);
	v_i.reserve(6);
	v_i.insert(v_i.begin(), v_d.begin(), v_d.end());
	//v_i.erase(v_i.begin());
	//v_i.erase(v_i.begin());
	//v_i.erase(v_i.begin());
	//v_i.assign(7, -2);
	//for (int i=0; i<1; i++)
		//v_i.insert(v_i.begin(), 3, -1);
	//v_i.pop_back();
	//v_i.insert(v_i.begin(), 2, -1);
	std::cout << "resize \n";
	//v_i.insert(v_i.begin(), 5, -1);
	//v_i.resize(11);
	for (int i=0; i<v_i.capacity(); i++)
		std::cout << v_i[i] << " ";
	//v_i.push_back(-1);
	std::cout << std::endl;
	std::cout << v_i.capacity() << "\n";
	std::cout << v_i.size() << "\n";
	//std::cout << "\nreserve \n";
	//v_i.reserve(10);
	//for (int i=0; i<10; i++)
	//	std::cout << v_i[i] << " ";
	//std::cout << std::endl;
	//std::cout << v_i.capacity() << "\n";
	//std::cout << v_i.size();
	return 0;
}
