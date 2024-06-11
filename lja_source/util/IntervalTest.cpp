#include <iostream>
#include <vector>
#include "Interval.h"

using namespace std;

namespace interval_test {

	void constructor() {
		Interval a, b(-1.1, 3.5), c(1000, -1000);
		cout << "a: " << a << endl;
		cout << "b: " << b << endl;
		cout << "c: " << c << endl;
	}
	void add() {
		Interval a(1, 2), b(3, 4);
		cout << "a: " << a << endl;
		cout << "b: " << b << endl;
		cout << "a + b: " << (a + b) << endl;
	}
	void subtract() {
		Interval a(-1, 2), b(-3, 4);
		cout << "a: " << a << endl;
		cout << "b: " << b << endl;
		cout << "a - b: " << (a - b) << endl;
	}
	void multiply() {
		Interval a(-1, 2), b(-3, 4);
		cout << "a: " << a << endl;
		cout << "b: " << b << endl;
		cout << "a * b: " << (a * b) << endl;
	}
	void divide() {
		Interval a(-1, 2), b(-3, 4);
		cout << "a: " << a << endl;
		cout << "b: " << b << endl;
		cout << "a / b: " << (a / b) << endl;
	}


	void register_tests(vector<pair<void (*)(void), string>>& t) {
		t.push_back({ constructor/* test func */, "constructor"/* test name */ });
		t.push_back({ add, "add" });
		t.push_back({ subtract, "subtract" });
		t.push_back({ multiply, "multiply" });
		t.push_back({ divide, "divide" });
	}

	void unit_test() {
		vector<pair<void (*)(void), string>> unit_test;
		register_tests(unit_test);

		cout << "************************************" << endl;
		cout << "************************************" << endl;
		cout << "****                            ****" << endl;
		cout << "****     Interval Unit Test     ****" << endl;
		cout << "****                            ****" << endl;
		cout << "************************************" << endl;
		cout << "************************************" << "\n\n\n";

		for (size_t i = 0; i < unit_test.size(); i++) {
			cout << "------------------------------------------\n";
			cout << "< Test: " << unit_test[i].second << " >\n";
			unit_test[i].first();
			cout << "\n\n\n";
		}
	}
}

//int main() { interval_test::unit_test(); }