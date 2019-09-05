#include "Nota.h"

ostream & operator<<(ostream & ot, const Nota & n)
{
	string s = "";
	char c;

	if (n.visina == Nota::C) c = 'C';
	else if (n.visina == Nota::D) c = 'D';
	else if (n.visina == Nota::E) c = 'E';
	else if (n.visina == Nota::F) c = 'F';
	else if (n.visina == Nota::G) c = 'G';
	else if (n.visina == Nota::A) c = 'A';
	else if (n.visina == Nota::B) c = 'B';

	Razlomak test = Razlomak(1, 8);
	if (n.trajanje == test) c = c + 32;
	s = s + c;

	if (n.povisena == true) s = s + '#';

	s = s + to_string(n.oktava);

	s = s + " " + to_string(n.broj);

	ot << s;

	return ot;
}

void Nota::povecajVisinu()
{
	if (visina == Nota::C) visina = D;
	else if (visina == Nota::D) visina = E;
	else if (visina == Nota::E) visina = F;
	else if (visina == Nota::F) visina = G;
	else if (visina == Nota::G) visina = A;
	else if (visina == Nota::A) visina = B;
}

void Nota::smanjiVisinu()
{
	if (visina == Nota::D) visina = C;
	else if (visina == Nota::E) visina = D;
	else if (visina == Nota::F) visina = E;
	else if (visina == Nota::G) visina = F;
	else if (visina == Nota::A) visina = G;
	else if (visina == Nota::B) visina = A;
}

void Nota::ispisi()
{
	string s = "";
	char c;

	if (visina == Nota::C) c = 'C';
	else if (visina == Nota::D) c = 'D';
	else if (visina == Nota::E) c = 'E';
	else if (visina == Nota::F) c = 'F';
	else if (visina == Nota::G) c = 'G';
	else if (visina == Nota::A) c = 'A';
	else if (visina == Nota::B) c = 'B';

	Razlomak test = Razlomak(1, 8);
	if (trajanje == test) c = c + 32;
	s = s + c;

	if (povisena == true) s = s + '#';

	s = s + to_string(oktava);

	if (povisena == false) s = s + " ";

	cout << s;
}

char Nota::getVisinaXML() const
{
	char c;
	if (visina == Nota::C) return c = 'C';
	else if (visina == Nota::D) return c = 'D';
	else if (visina == Nota::E) return c = 'E';
	else if (visina == Nota::F) return c = 'F';
	else if (visina == Nota::G) return c = 'G';
	else if (visina == Nota::A) return c = 'A';
	else if (visina == Nota::B) return c = 'B';
}
