#include<iostream>

using namespace std;

void swapByRef(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
	return;
}

void swapByPointer(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

int main() {
	int a;
	int b;

	cout << "Nhap so nguyen a: ";
	cin >> a;

	cout << "Nhap so nguyen b: ";
	cin >> b;

	cout << "Swap by ref:" << endl;
	swapByRef(a, b);
	cout << "a = " << a << ", b = " << b << endl;

	cout << "Swap again by pointer:" << endl;
	swapByPointer(&a, &b);
	cout << "a = " << a << ", b = " << b << endl;
}