#include "Razlomak.h"

Razlomak operator+(const Razlomak & r1, const Razlomak & r2)
{
	int brojilac = r1.b*r2.i + r2.b*r1.i;
	int imenilac = r1.i*r2.i;

	while (brojilac % 2 == 0 && imenilac % 2 == 0) {
		brojilac = brojilac / 2;
		imenilac = imenilac / 2;
	}

	return Razlomak(brojilac, imenilac);
}

Razlomak operator-(const Razlomak & r1, const Razlomak & r2)
{
	int brojilac = r1.b*r2.i - r2.b*r1.i;
	int imenilac = r1.i*r2.i;

	while (brojilac % 2 == 0 && imenilac % 2 == 0) {
		brojilac = brojilac / 2;
		imenilac = imenilac / 2;
	}

	return Razlomak(brojilac, imenilac);
}
