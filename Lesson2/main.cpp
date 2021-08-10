#include<iostream>
#include <sstream>

using namespace std;

bool isNumber(string str) {
	char* p;
	strtol(str.c_str(), &p, 10);
	return *p == 0;
}

int main() {
	{
		string input;
		int n;
		cout.precision(0);

		cout << "Nhap so mau: ";

		/*Input Validation*/
		do {
			cin >> input;

			if (!isNumber(input)) {
				cout << "Khong duoc phep nhap ki tu!" << endl;
			}
			else {
				n = stoi(input);
				if (n < 0 || n > 20) {
					cout << "Mau so khong hop le (n >= 0 && n <= 20)" << endl;
				}
				else {
					break;
				}
			}

			cout << "Nhap lai so mau: ";

		} while (true);

		/*Calculating*/
		long double result = 1;
		for (register int i = 2; i <= n; i++) {
			result *= i;
		}
		cout << n << "! = " << fixed << result;
	}
}