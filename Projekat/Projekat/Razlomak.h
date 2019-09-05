#pragma once

#include <iostream>
using namespace std;

class Razlomak
{
private:
	int i, b;
public:
	Razlomak(int br, int im = 1) :i(im), b(br) {};

	friend Razlomak operator+(const Razlomak &r1, const Razlomak &r2);
	friend Razlomak operator-(const Razlomak &r1, const Razlomak &r2);

	friend bool operator>(const Razlomak &r1, const Razlomak &r2) {
		return r1.b*r2.i > r2.b*r1.i;
	}
	friend bool operator==(const Razlomak &r1, const Razlomak &r2) {
		if (r1.b == r2.b && r1.i == r2.i) return true;
		else return false;
	}

	friend ostream& operator<<(ostream &it, const Razlomak &r) {
		return it << r.b << "/" << r.i;
	}

	int getImenilac() const {
		return i;
	}

	int getBrojilac() const {
		return b;
	}
};

