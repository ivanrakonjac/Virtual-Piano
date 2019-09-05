#include "Kompozicija.h"

void Kompozicija::stampajLeva()
{
	for (int i = 0; i < leva.size(); i++) {
		leva[i].stampaj();
		cout << " ";
	}
	cout << endl;
}

void Kompozicija::stampajDesna()
{
	for (int i = 0; i < desna.size(); i++) {
		desna[i].stampaj();
		cout << " ";
	}
	cout << endl;
}

void Kompozicija::stampaj()
{
	int brojac1 = 0;
	int brojac2 = 10;

	cout << endl << "-------------KOMPOZICIJA-------------" << endl;
	cout << endl;

	while (true) {
		if (brojac1 >= getBrMuzickihSimbola()) break;

		cout << "D: ";
		for (int i = brojac1; i < brojac2; i++) {
			desna[i].stampaj();
			cout << " ";
		}
		cout << endl;

		cout << "L: ";
		for (int i = brojac1; i < brojac2; i++) {
			leva[i].stampaj();
			cout << " ";
		}
		cout << endl;

		cout << endl;

		brojac1 = brojac2;
		brojac2 = brojac2 + 10;
		if (brojac2 > getBrMuzickihSimbola()) brojac2 = getBrMuzickihSimbola();
	}
}

void Kompozicija::iterirajKrozLevuRuku()
{
	vector<Takt>::iterator ptr;
	ptr = leva.begin();

	while (true) {
		cout << endl << "Mogucnosti:" << endl;
		cout << "1) Zapocni iteriranje kroz levu ruku" << endl;
		cout << "2) Predji na sledeci takt" << endl;
		cout << "3) Vrati se na prethodni takt" << endl;
		cout << "4) iteriraj kroz takt" << endl;
		cout << "5) Zavrsi iteriranje kroz kompoziciju" << endl;
		int opcija = 0;
		cout << endl << "Unesite broj odabrane mogucnosti: ";
		cin >> opcija;

		if (opcija == 1) {
			ptr = leva.begin();
			ptr->stampaj();
		}
		else if (opcija == 2) {
			if (ptr == leva.end()) cout << "Na kraju ste kompozicije za levu ruku!" << endl;
			else {
				auto it = next(ptr, 1);
				it->stampaj();
				ptr = it;
			}
		}
		else if (opcija == 3) {
			if (ptr == leva.begin()) cout << "Na pocetku ste kompozicije za levu ruku!" << endl;
			else {
				auto it = prev(ptr, 1);
				it->stampaj();
				ptr = it;
			}
		}
		else if (opcija == 4) {
			ptr->iterirajKrozTakt();
		}
		else if (opcija == 5) break;

	}

}

void Kompozicija::iterirajKrozDesnuRuku()
{
	vector<Takt>::iterator ptr;
	ptr = desna.begin();

	while (true) {
		cout << endl << "Mogucnosti za kompoziciju:" << endl;
		cout << "1) Zapocni iteriranje kroz desnu ruku" << endl;
		cout << "2) Predji na sledeci takt" << endl;
		cout << "3) Vrati se na prethodni takt" << endl;
		cout << "4) Iteriraj kroz takt" << endl;
		cout << "5) Zavrsi iteriranje kroz desnu ruku" << endl;
		int opcija = 0;
		cout << endl << "Unesite broj odabrane mogucnosti: ";
		cin >> opcija;

		if (opcija == 1) {
			ptr = desna.begin();
			ptr->stampaj();
		}
		else if (opcija == 2) {
			if (ptr == desna.end()) cout << "Na kraju ste kompozicije za desnu ruku!" << endl;
			else {
				auto it = next(ptr, 1);
				it->stampaj();
				ptr = it;
			}
		}
		else if (opcija == 3) {
			if (ptr == desna.begin()) cout << "Na pocetku ste kompozicije za desnu ruku!" << endl;
			else {
				auto it = prev(ptr, 1);
				it->stampaj();
				ptr = it;
			}
		}
		else if (opcija == 4) {
			ptr->iterirajKrozTakt();
		}
		else if (opcija == 5) break;

	}

}

void Kompozicija::povecajOktavuSvihNota(int i)
{
	vector<Takt>::iterator ptr;
	for (ptr = leva.begin(); ptr < leva.end(); ptr++) {
		ptr->povecajOktavuSvihNotaPuta(i);
	}
	for (ptr = desna.begin(); ptr < desna.end(); ptr++) {
		ptr->povecajOktavuSvihNotaPuta(i);
	}
}

void Kompozicija::smanjiOktavuSvihNota(int i)
{
	vector<Takt>::iterator ptr;
	for (ptr = leva.begin(); ptr < leva.end(); ptr++) {
		ptr->smanjiOktavuSvihNotaPuta(i);
	}
	for (ptr = desna.begin(); ptr < desna.end(); ptr++) {
		ptr->smanjiOktavuSvihNotaPuta(i);
	}
}
