#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <map>
#include <cmath>

using namespace std;


void DispatchTable() {

	map<const char, function<double(double, double)> > dispTable{
					{ '+', [](double a, double b) {return a + b; } },
					{ '-', [](double a, double b) {return a - b; } },
					{ '*', [](double a, double b) {return a * b; } },
					{ '/', [](double a, double b) {return a / b; } }
	};

	cout << "3.5+4.5= " << dispTable['+'](3.5, 4.5) << endl;
	cout << "3.5-4.5= " << dispTable['-'](3.5, 4.5) << endl;
	cout << "3.5*4.5= " << dispTable['*'](3.5, 4.5) << endl;
	cout << "3.5/4.5= " << dispTable['/'](3.5, 4.5) << endl;

	dispTable['^'] = [](double a, double b) {return pow(a, b); };
	cout << "3.5^4.5= " << dispTable['^'](3.5, 4.5) << endl;
}

int main() {

	auto sequence = [](size_t i) {
		vector<size_t> result(i);
		iota(begin(result), end(result), 0);
		return result;
	};

	auto s = sequence(22);
	s.push_back(42);

	//[0] - simple variables
	//template<class C>
	//auto print(C const& container)
	// same as ...
	auto print = [](auto const& container) {
		for (auto&&e : container) {
			cout << e << ' ';
		}
		cout << endl;
	};

	print(s);


	//[1] - trailing types
	auto divide = [](double a, double b) -> double {
		if (b == 0)
			return 0;
		else
			return a / b;
	};
	cout << divide(6, 2) << endl;

	int one = 1;
	int two = 2;
	int three = 3;

	//[2] - capture local variables by value
	[one, two]() {
		cout << one << " " << two << endl;
	}();

	//[3] - capture all local variables by value
	[=]() { cout << "Hello " << one << " " << two << " " << three << endl; }();

	//[4] - capture all local variables by value, but capture three by referenece
	[=, &three]() {
		cout << "Hello " << one << " " << two << " " << three << endl;
		three = 56;
	}();

	cout << three << endl;

	//[5] - capture all local variables by referenece
	[&]() {
		cout << "Hello " << one << " " << two << " " << three << endl;
		three = 56;
	}();

	cout << three << endl;

	//[6] - capture all local variables by referenece by default but two and three by value
	[&, two, three]() {
		cout << "Hello " << one << " " << two << " " << three << endl;
	}();

	cout << three << endl;

	//[7] - capture mutable vectors
	int m = 0;
	int n = 0;
	[&, n](int a) mutable { m = ++n + a; }(7);
	cout << m << endl << n << endl;

	//[8] - dispatch table
	DispatchTable();

	/*
	//[9] - C++14 generic lambda functions
	auto myAdd = [](auto fir, auto sec) { retunr fir + sec;  };
	std::cout << "myAdd(1, 10)= " << myAdd(1, 10) << std::endl;
	std::cout << "myAdd(1, 10.0)= " << myAdd(1, 10.0) << std::endl;
	std::cout << "myAdd(std::string(1),std::string(10.0)= "	<< myAdd(std::string("1"), std::string("10")) << std::endl;
	std::cout << "myAdd(true, 10.0)= " << myAdd(true, 10.0) << std::endl;
	*/


	return 0;
}
