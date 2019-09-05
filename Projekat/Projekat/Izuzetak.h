#pragma once

#include <iostream>
#include <string>
using namespace std;

class Izuzetak
{
private:
	string opis;
public:
	Izuzetak(string o) :opis(o) {};

	friend ostream& operator<<(ostream &ot, const Izuzetak &i) {
		ot << i.opis;
		return ot;
	}
};

