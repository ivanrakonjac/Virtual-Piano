#include "Takt.h"

void Takt::dodaj(MuzickiZnak * mz)
{
	if (mz->getTrajanje() > trajanjeTakta) {
		throw Izuzetak("Nema mesta, takt je prekratak!");
	}
	else {
		niz.push_back(mz);
		trajanjeTakta = trajanjeTakta - mz->getTrajanje();
	}
}

void Takt::stampaj()
{
	for (int i = 0; i < niz.size(); i++) {
		niz[i]->ispisi();
		cout << " ";
	}
	cout << "| ";
}

void Takt::iterirajKrozTakt()
{
	vector<MuzickiZnak*>::iterator iter;
	iter = niz.begin();

	while (true) {
		cout << endl << "Mogucnosti za takt:" << endl;
		cout << "1) Zapocni iteriranje kroz takt" << endl;
		cout << "2) Predji na sledecu notu" << endl;
		cout << "3) Vrati se na prethodnu notu" << endl;
		cout << "4) Podesi notu" << endl;
		cout << "5) Zavrsi iteriranje kroz takt" << endl;
		int opcija = 0;
		cout << endl << "Unesite broj odabrane mogucnosti: ";
		cin >> opcija;

		if (opcija == 1) {
			iter = niz.begin();
			MuzickiZnak* mz = *iter;
			mz->ispisi();
		}
		else if (opcija == 2) {
			if (iter == niz.end()) cout << "Na kraju ste takta!" << endl;
			else {
				auto it = next(iter, 1);
				MuzickiZnak* mz = *it;
				mz->ispisi();
				iter = it;
			}
		}
		else if (opcija == 3) {
			MuzickiZnak* pocetak = *iter;
			MuzickiZnak* temp = *(niz.begin());
			if (pocetak == temp) cout << "Na pocetku ste takta!" << endl;
			else {
				auto it = prev(iter, 1);
				MuzickiZnak* mz = *it;
				mz->ispisi();
				iter = it;
			}
		}
		else if (opcija == 4) {
			MuzickiZnak* mz = *iter;
			if (Nota* n = dynamic_cast<Nota*>(*iter)) {
				while (true) {
					cout << endl << "Mogucnosti za notu:" << endl;
					cout << "1) Na kojoj sam noti?" << endl;
					cout << "2) Povecaj oktavu" << endl;
					cout << "3) Smanji oktavu" << endl;
					cout << "4) Povecaj visinu" << endl;
					cout << "5) Smanji visinu" << endl;
					cout << "6) Dodaj povisilicu" << endl;
					cout << "7) Skloni povisilicu" << endl;
					cout << "8) Zavrsi sa podesavanjem note" << endl;
					int opcija2 = 0;
					cout << endl << "Unesite broj odabrane mogucnosti: ";
					cin >> opcija2;

					if (opcija2 == 1) {
						n->ispisi();
					}
					else if (opcija2 == 2) {
						n->povecajOktavu();
					}
					else if (opcija2 == 3) {
						n->smanjiOktavu();
					}
					else if (opcija2 == 4) {
						n->povecajVisinu();
					}
					else if (opcija2 == 5) {
						n->smanjiVisinu();
					}
					else if (opcija2 == 6) {
						n->povisiTon();
					}
					else if (opcija2 == 7) {
						n->sniziTon();
					}
					else if (opcija2 == 8) {
						break;
					}
				}
			}
		}
		else if (opcija == 5) {
			break;
		}

	}

}

void Takt::smanjiOktavuSvihNotaPuta(int i)
{
	for (int j = 0;j < i;j++) {
		for (int k = 0;k < niz.size();k++) {
			if (Nota* n = dynamic_cast<Nota*>(niz[k])) {
				n->smanjiOktavu();
			}
		}
	}
}

void Takt::povecajOktavuSvihNotaPuta(int i)
{
	for (int j = 0;j < i;j++) {
		for (int k = 0;k < niz.size();k++) {
			if (Nota* n = dynamic_cast<Nota*>(niz[k])) {
				n->povecajOktavu();
			}
		}
	}
}
