#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

#include "Nota.h"
#include "Pauza.h"
#include "Takt.h"
#include "Akord.h"
#include "Kompozicija.h"
#include "MIDI.h"
#include "XML.h"

using namespace std;

int main() {

	struct Elem {
		string nota;
		int broj;
	};
	map<string, Elem> mapa;
	Elem elem;

	//Kompozicija* k = nullptr;
	int imenilac = 0, brojilac = 0;
	cout << endl << "Unesi brojilac pa imenilac" << endl;
	cin >> brojilac;
	cin >> imenilac;

	Takt* tekuciLevo = nullptr;
	Takt* tekuciDesno = nullptr;
	Takt* sledeciLevo = nullptr;
	Takt* sledeciDesno = nullptr;

	Razlomak duzinaTakta = Razlomak(brojilac, imenilac);

	Kompozicija k = Kompozicija(duzinaTakta);

	bool checkXML = false, checkMIDI = false;


	while (true) {
		int opcija = 0;
		cout <<endl<< " ----------------MENI----------------" << endl;
		cout << " 1) Ucitaj podatke o notama" << endl;
		cout << " 2) Formiraj kompozociju" << endl;
		cout << " 3) Pogledaj kompozociju" << endl;
		cout << " 4) Iteriraj kroz levu ruku" << endl;
		cout << " 5) Iteriraj kroz desnu ruku" << endl;
		cout << " 6) Promeni trajanje takta" << endl;
		cout << " 7) Eksportuj MIDI fajl" << endl;
		cout << " 8) Eksportuj XML fajl" << endl;
		cout << " 9) Eksportuj BMP fajl" << endl;
		cout << "10) Zavrsi" << endl;
		cout << endl;
		cout<<"Unesite broj odabrane opcije: ";
		cin >> opcija;

		if (opcija == 1) {
			ifstream file2("map.csv");
			string textLine;
			regex rx("([^,]*),([^,]*),([^,]*)");

			while (getline(file2, textLine)) {
				smatch result;
				if (regex_match(textLine, result, rx)) {
					string kar = result.str(1);
					string opis = result.str(2);
					string broj = result.str(3);

					elem.nota = opis;
					elem.broj = stoi(broj);

					mapa.insert(pair<string, Elem>(kar, elem));
					cout << kar << "," << opis << "," << broj << endl;
				}
			}
		}
		else if (opcija == 2) {

			checkMIDI = false;
			checkXML = false;

			string naziv;
			cout << "Upisite naziv ulaznog fajla: ";
			cin >> naziv;
			naziv += ".txt";

			ifstream file(naziv);
			string textLine2;
			regex rx2(".*?(\\[[0-9a-z\\s]*\\]|[a-zA-Z0-9]*)[^;]*");
			if (file.is_open())
			{
				smatch result;
				getline(file, textLine2);
				while (textLine2.length()>0) {

					char space = ' ';char crta = '|';
					if (textLine2[0] == space || textLine2[0] == crta) {
						//ako je pauza a takt prazan
						if (tekuciLevo == nullptr || tekuciDesno == nullptr) {
							tekuciLevo = new Takt(duzinaTakta);
							tekuciDesno = new Takt(duzinaTakta);

							if (textLine2[0] == space) {
								Razlomak trajanjePauze = Razlomak(1, 8);

								Pauza* p1p = new Pauza(trajanjePauze);
								Pauza* p2p = new Pauza(trajanjePauze);

								tekuciDesno->dodaj(p1p);
								tekuciLevo->dodaj(p2p);
							}
							else if (textLine2[0] == crta) {
								Pauza* p1p = new Pauza(Razlomak(1, 4));
								Pauza* p2p = new Pauza(Razlomak(1, 4));

								tekuciDesno->dodaj(p1p);
								tekuciLevo->dodaj(p2p);
							}
						}
						//ako je pauza a takt pun
						else if (tekuciLevo->getTrajanjeTakta().getBrojilac() == 0 || tekuciDesno->getTrajanjeTakta().getBrojilac() == 0) {
							k.dodajDesna(*tekuciDesno);
							k.dodajLeva(*tekuciLevo);

							sledeciLevo = new Takt(duzinaTakta);
							sledeciDesno = new Takt(duzinaTakta);

							if (textLine2[0] == space) {
								Razlomak trajanjePauze = Razlomak(1, 8);

								Pauza* p1p = new Pauza(trajanjePauze);
								Pauza* p2p = new Pauza(trajanjePauze);

								sledeciDesno->dodaj(p1p);
								sledeciLevo->dodaj(p2p);
							}
							else if (textLine2[0] == crta) {
								Razlomak trajanjePauze = Razlomak(1, 4);

								Pauza* p1p = new Pauza(trajanjePauze);
								Pauza* p2p = new Pauza(trajanjePauze);

								sledeciDesno->dodaj(p1p);
								sledeciLevo->dodaj(p2p);
							}

							tekuciLevo = sledeciLevo;
							tekuciDesno = sledeciDesno;
						}
						//ako je pauza | => 1/4 pa moze da se deli u 2 takta, pauzu space => 1/8 nema smisla deliti
						else if (textLine2[0] == crta && Razlomak(1, 4) > tekuciDesno->getTrajanjeTakta()) {
							sledeciLevo = new Takt(duzinaTakta);
							sledeciDesno = new Takt(duzinaTakta);

							Razlomak trajanjePauze = Razlomak(1, 8);

							Pauza* p1p = new Pauza(trajanjePauze, false, true);
							Pauza* p2p = new Pauza(trajanjePauze, false, true);
							Pauza* p3p = new Pauza(trajanjePauze, false, true);
							Pauza* p4p = new Pauza(trajanjePauze, false, true);

							tekuciDesno->dodaj(p1p);
							sledeciDesno->dodaj(p2p);
							tekuciLevo->dodaj(p3p);
							sledeciLevo->dodaj(p4p);

							k.dodajDesna(*tekuciDesno);
							k.dodajLeva(*tekuciLevo);

							tekuciLevo = sledeciLevo;
							tekuciDesno = sledeciDesno;

						}
						//ako ima mesta u taktu
						else {
							if (textLine2[0] == space) {
								Razlomak trajanjePauze = Razlomak(1, 8);

								Pauza* p1p = new Pauza(trajanjePauze);
								Pauza* p2p = new Pauza(trajanjePauze);

								tekuciDesno->dodaj(p1p);
								tekuciLevo->dodaj(p2p);
							}
							else if (textLine2[0] == crta) {
								Razlomak trajanjePauze = Razlomak(1, 4);

								Pauza* p1p = new Pauza(trajanjePauze);
								Pauza* p2p = new Pauza(trajanjePauze);

								tekuciDesno->dodaj(p1p);
								tekuciLevo->dodaj(p2p);
							}
						}

						for (int i = 0;i < textLine2.length() - 1;i++) textLine2[i] = textLine2[1 + i];
						textLine2.resize(textLine2.length() - 1);

					}
					else if (regex_match(textLine2, result, rx2)) {
						string kar = result.str(1);
						cout << endl << kar << " ";
						cout << kar.length() << endl;
						cout << endl;

						if (kar[0] != '[') {
							string visina;
							int oktava;
							bool povisena, part, spojena;

							for (int i = 0; i < kar.length(); i++)
							{
								string c = "";
								c = c + kar[i];
								Elem e2 = mapa.find(c)->second;
								string nota = e2.nota;
								int broj = e2.broj;

								cout << kar[i] << "->" << nota << " ";
								cout << broj << " " << nota.length() << endl;

								if (nota.length() == 2) {
									visina = nota[0];
									string temp = "";
									temp = temp + nota[1];
									oktava = atoi(temp.c_str());
									povisena = false;
								}
								else {
									visina = nota[0];
									povisena = true;
									string temp = "";
									temp = temp + nota[2];
									oktava = atoi(temp.c_str());

								}

								Razlomak trajanje = Razlomak(1, 4);

								Nota::Visina v = Nota::A;

								if (visina == "C") v = Nota::C;
								else if (visina == "D") v = Nota::D;
								else if (visina == "E") v = Nota::E;
								else if (visina == "F") v = Nota::F;
								else if (visina == "G") v = Nota::G;
								else if (visina == "A") v = Nota::A;
								else if (visina == "B") v = Nota::B;


								if (tekuciLevo == nullptr || tekuciDesno == nullptr) {
									tekuciLevo = new Takt(duzinaTakta);
									tekuciDesno = new Takt(duzinaTakta);

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);
									Pauza* p1p = new Pauza(trajanje);

									if (oktava > 3) {
										tekuciDesno->dodaj(n1p);
										tekuciLevo->dodaj(p1p);
									}
									else {
										tekuciDesno->dodaj(p1p);
										tekuciLevo->dodaj(n1p);
									}
								}
								else if (tekuciLevo->getTrajanjeTakta().getBrojilac() == 0 || tekuciDesno->getTrajanjeTakta().getBrojilac() == 0) {
									k.dodajDesna(*tekuciDesno);
									k.dodajLeva(*tekuciLevo);

									sledeciLevo = new Takt(duzinaTakta);
									sledeciDesno = new Takt(duzinaTakta);

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);
									Pauza* p1p = new Pauza(trajanje);

									if (oktava > 3) {
										sledeciDesno->dodaj(n1p);
										sledeciLevo->dodaj(p1p);
									}
									else {
										sledeciDesno->dodaj(p1p);
										sledeciLevo->dodaj(n1p);
									}

									tekuciLevo = sledeciLevo;
									tekuciDesno = sledeciDesno;

								}
								else if (trajanje > tekuciLevo->getTrajanjeTakta() || trajanje > tekuciDesno->getTrajanjeTakta()) {
									sledeciLevo = new Takt(duzinaTakta);
									sledeciDesno = new Takt(duzinaTakta);

									Razlomak duzinaPauze = Razlomak(trajanje.getBrojilac(), trajanje.getImenilac() * 2);

									Nota* np1 = new Nota(duzinaPauze, v, oktava, broj, povisena, true);
									Nota* np2 = new Nota(duzinaPauze, v, oktava, broj, povisena, true);

									Pauza* p1p = new Pauza(duzinaPauze);
									Pauza* p2p = new Pauza(duzinaPauze);


									if (oktava > 3) {
										tekuciDesno->dodaj(np1);
										sledeciDesno->dodaj(np2);
										tekuciLevo->dodaj(p1p);
										sledeciLevo->dodaj(p2p);
									}
									else {
										tekuciDesno->dodaj(p1p);
										sledeciDesno->dodaj(p2p);
										tekuciLevo->dodaj(np1);
										sledeciLevo->dodaj(np2);
									}

									k.dodajDesna(*tekuciDesno);
									k.dodajLeva(*tekuciLevo);

									tekuciLevo = sledeciLevo;
									tekuciDesno = sledeciDesno;

								}
								else {
									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);
									Pauza* p1p = new Pauza(trajanje);

									if (oktava > 3) {
										tekuciDesno->dodaj(n1p);
										tekuciLevo->dodaj(p1p);
									}
									else {
										tekuciDesno->dodaj(p1p);
										tekuciLevo->dodaj(n1p);
									}
								}

							}
						}
						else if (kar[0] == '[' && kar[2] == space) {
							string visina;
							int oktava;
							bool povisena, part, spojena;

							for (int i = 1; i < kar.length() - 1; i = i + 2)
							{
								string c = "";
								c = c + kar[i];
								Elem e2 = mapa.find(c)->second;
								string nota = e2.nota;
								int broj = e2.broj;

								cout << kar[i] << "->" << nota << " ";
								cout << broj << " " << nota.length() << endl;

								if (nota.length() == 2) {
									visina = nota[0];
									string temp = "";
									temp = temp + nota[1];
									oktava = atoi(temp.c_str());
									povisena = false;
								}
								else {
									visina = nota[0];
									povisena = true;
									string temp = "";
									temp = temp + nota[2];
									oktava = atoi(temp.c_str());

								}

								Razlomak trajanje = Razlomak(1, 8);

								Nota::Visina v = Nota::A;

								if (visina == "C") v = Nota::C;
								else if (visina == "D") v = Nota::D;
								else if (visina == "E") v = Nota::E;
								else if (visina == "F") v = Nota::F;
								else if (visina == "G") v = Nota::G;
								else if (visina == "A") v = Nota::A;
								else if (visina == "B") v = Nota::B;


								if (tekuciLevo == nullptr || tekuciDesno == nullptr) {
									tekuciLevo = new Takt(duzinaTakta);
									tekuciDesno = new Takt(duzinaTakta);

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);
									Pauza* p1p = new Pauza(trajanje);

									if (oktava > 3) {
										tekuciDesno->dodaj(n1p);
										tekuciLevo->dodaj(p1p);
									}
									else {
										tekuciDesno->dodaj(p1p);
										tekuciLevo->dodaj(n1p);
									}
								}
								else if (tekuciLevo->getTrajanjeTakta().getBrojilac() == 0 || tekuciDesno->getTrajanjeTakta().getBrojilac() == 0) {
									k.dodajDesna(*tekuciDesno);
									k.dodajLeva(*tekuciLevo);

									sledeciLevo = new Takt(duzinaTakta);
									sledeciDesno = new Takt(duzinaTakta);

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);
									Pauza* p1p = new Pauza(trajanje);

									if (oktava > 3) {
										sledeciDesno->dodaj(n1p);
										sledeciLevo->dodaj(p1p);
									}
									else {
										sledeciDesno->dodaj(p1p);
										sledeciLevo->dodaj(n1p);
									}

									tekuciLevo = sledeciLevo;
									tekuciDesno = sledeciDesno;
								}
								else {
									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);
									Pauza* p1p = new Pauza(trajanje);

									if (oktava > 3) {
										tekuciDesno->dodaj(n1p);
										tekuciLevo->dodaj(p1p);
									}
									else {
										tekuciDesno->dodaj(p1p);
										tekuciLevo->dodaj(n1p);
									}
								}

							}
						}
						else if (kar[0] == '[' && kar[2] != space) {
							string visina;
							int oktava;
							bool povisena, part, spojena;

							if (tekuciLevo == nullptr || tekuciDesno == nullptr) {
								tekuciLevo = new Takt(duzinaTakta);
								tekuciDesno = new Takt(duzinaTakta);

								Akord* akordDesni = new Akord(Razlomak(1, 4));
								Akord* akordLevi = new Akord(Razlomak(1, 4));;

								for (int i = 1; i < kar.length() - 1; i++)
								{
									string c = "";
									c = c + kar[i];
									Elem e2 = mapa.find(c)->second;
									string nota = e2.nota;
									int broj = e2.broj;

									cout << kar[i] << "->" << nota << " ";
									cout << broj << " " << nota.length() << endl;

									if (nota.length() == 2) {
										visina = nota[0];
										string temp = "";
										temp = temp + nota[1];
										oktava = atoi(temp.c_str());
										povisena = false;
									}
									else {
										visina = nota[0];
										povisena = true;
										string temp = "";
										temp = temp + nota[2];
										oktava = atoi(temp.c_str());

									}

									Razlomak trajanje = Razlomak(1, 4);

									Nota::Visina v = Nota::A;

									if (visina == "C") v = Nota::C;
									else if (visina == "D") v = Nota::D;
									else if (visina == "E") v = Nota::E;
									else if (visina == "F") v = Nota::F;
									else if (visina == "G") v = Nota::G;
									else if (visina == "A") v = Nota::A;
									else if (visina == "B") v = Nota::B;

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);

									if (oktava > 3) {
										akordDesni->dodaj(n1p);
									}
									else {
										akordLevi->dodaj(n1p);
									}
								}

								if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									tekuciDesno->dodaj(akordDesni);
									tekuciLevo->dodaj(akordLevi);
								}
								else if (akordDesni->getBrMuzickihSimbola() == 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);

									tekuciDesno->dodaj(p1);
									tekuciLevo->dodaj(akordLevi);
								}
								else if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() == 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);

									tekuciDesno->dodaj(akordDesni);
									tekuciLevo->dodaj(p1);
								}
							}
							else if (tekuciLevo->getTrajanjeTakta().getBrojilac() == 0 || tekuciDesno->getTrajanjeTakta().getBrojilac() == 0) {
								k.dodajDesna(*tekuciDesno);
								k.dodajLeva(*tekuciLevo);

								sledeciLevo = new Takt(duzinaTakta);
								sledeciDesno = new Takt(duzinaTakta);

								Akord* akordDesni = new Akord(Razlomak(1, 4));
								Akord* akordLevi = new Akord(Razlomak(1, 4));;

								for (int i = 1; i < kar.length() - 1; i++)
								{
									string c = "";
									c = c + kar[i];
									Elem e2 = mapa.find(c)->second;
									string nota = e2.nota;
									int broj = e2.broj;

									cout << kar[i] << "->" << nota << " ";
									cout << broj << " " << nota.length() << endl;

									if (nota.length() == 2) {
										visina = nota[0];
										string temp = "";
										temp = temp + nota[1];
										oktava = atoi(temp.c_str());
										povisena = false;
									}
									else {
										visina = nota[0];
										povisena = true;
										string temp = "";
										temp = temp + nota[2];
										oktava = atoi(temp.c_str());

									}

									Razlomak trajanje = Razlomak(1, 4);

									Nota::Visina v = Nota::A;

									if (visina == "C") v = Nota::C;
									else if (visina == "D") v = Nota::D;
									else if (visina == "E") v = Nota::E;
									else if (visina == "F") v = Nota::F;
									else if (visina == "G") v = Nota::G;
									else if (visina == "A") v = Nota::A;
									else if (visina == "B") v = Nota::B;

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);

									if (oktava > 3) {
										akordDesni->dodaj(n1p);
									}
									else {
										akordLevi->dodaj(n1p);
									}
								}


								if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									sledeciDesno->dodaj(akordDesni);
									sledeciLevo->dodaj(akordLevi);
								}
								else if (akordDesni->getBrMuzickihSimbola() == 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);

									sledeciDesno->dodaj(p1);
									sledeciLevo->dodaj(akordLevi);
								}
								else if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() == 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);

									sledeciDesno->dodaj(akordDesni);
									sledeciLevo->dodaj(p1);
								}

								tekuciLevo = sledeciLevo;
								tekuciDesno = sledeciDesno;
							}
							else if (Razlomak(1, 4) > tekuciLevo->getTrajanjeTakta() || Razlomak(1, 4) > tekuciDesno->getTrajanjeTakta()) {
								sledeciLevo = new Takt(duzinaTakta);
								sledeciDesno = new Takt(duzinaTakta);


								Akord* akordDesni = new Akord(Razlomak(1, 8));
								Akord* akordLevi = new Akord(Razlomak(1, 8));;
								Akord* akordDesni2 = new Akord(Razlomak(1, 8));
								Akord* akordLevi2 = new Akord(Razlomak(1, 8));;

								for (int i = 1; i < kar.length() - 1; i++)
								{
									string c = "";
									c = c + kar[i];
									Elem e2 = mapa.find(c)->second;
									string nota = e2.nota;
									int broj = e2.broj;

									cout << kar[i] << "->" << nota << " ";
									cout << broj << " " << nota.length() << endl;

									if (nota.length() == 2) {
										visina = nota[0];
										string temp = "";
										temp = temp + nota[1];
										oktava = atoi(temp.c_str());
										povisena = false;
									}
									else {
										visina = nota[0];
										povisena = true;
										string temp = "";
										temp = temp + nota[2];
										oktava = atoi(temp.c_str());

									}

									Razlomak trajanje = Razlomak(1, 8);

									Nota::Visina v = Nota::A;

									if (visina == "C") v = Nota::C;
									else if (visina == "D") v = Nota::D;
									else if (visina == "E") v = Nota::E;
									else if (visina == "F") v = Nota::F;
									else if (visina == "G") v = Nota::G;
									else if (visina == "A") v = Nota::A;
									else if (visina == "B") v = Nota::B;

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena, true);
									Nota* n2p = new Nota(trajanje, v, oktava, broj, povisena, true);

									if (oktava > 3) {
										akordDesni->dodaj(n1p);
										akordDesni2->dodaj(n2p);
									}
									else {
										akordLevi->dodaj(n1p);
										akordLevi2->dodaj(n2p);
									}
								}


								if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									tekuciDesno->dodaj(akordDesni);
									tekuciLevo->dodaj(akordLevi);
									sledeciDesno->dodaj(akordDesni2);
									sledeciLevo->dodaj(akordLevi2);
								}
								else if (akordDesni->getBrMuzickihSimbola() == 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);
									Pauza* p2 = new Pauza(Razlomak(1, 4), true);

									tekuciDesno->dodaj(p1);
									tekuciLevo->dodaj(akordLevi);
									sledeciDesno->dodaj(p2);
									sledeciLevo->dodaj(akordLevi2);
								}
								else if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() == 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);
									Pauza* p2 = new Pauza(Razlomak(1, 4), true);

									tekuciDesno->dodaj(akordDesni);
									tekuciLevo->dodaj(p1);
									sledeciDesno->dodaj(akordDesni2);
									sledeciLevo->dodaj(p2);
								}

								k.dodajDesna(*tekuciDesno);
								k.dodajLeva(*tekuciLevo);

								tekuciLevo = sledeciLevo;
								tekuciDesno = sledeciDesno;
							}
							else {
								Akord* akordDesni = new Akord(Razlomak(1, 4));
								Akord* akordLevi = new Akord(Razlomak(1, 4));;

								for (int i = 1; i < kar.length() - 1; i++)
								{
									string c = "";
									c = c + kar[i];
									Elem e2 = mapa.find(c)->second;
									string nota = e2.nota;
									int broj = e2.broj;

									cout << kar[i] << "->" << nota << " ";
									cout << broj << " " << nota.length() << endl;

									if (nota.length() == 2) {
										visina = nota[0];
										string temp = "";
										temp = temp + nota[1];
										oktava = atoi(temp.c_str());
										povisena = false;
									}
									else {
										visina = nota[0];
										povisena = true;
										string temp = "";
										temp = temp + nota[2];
										oktava = atoi(temp.c_str());

									}

									Razlomak trajanje = Razlomak(1, 4);

									Nota::Visina v = Nota::A;

									if (visina == "C") v = Nota::C;
									else if (visina == "D") v = Nota::D;
									else if (visina == "E") v = Nota::E;
									else if (visina == "F") v = Nota::F;
									else if (visina == "G") v = Nota::G;
									else if (visina == "A") v = Nota::A;
									else if (visina == "B") v = Nota::B;

									Nota* n1p = new Nota(trajanje, v, oktava, broj, povisena);

									if (oktava > 3) {
										akordDesni->dodaj(n1p);
									}
									else {
										akordLevi->dodaj(n1p);
									}
								}

								if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									tekuciDesno->dodaj(akordDesni);
									tekuciLevo->dodaj(akordLevi);
								}
								else if (akordDesni->getBrMuzickihSimbola() == 0 && akordLevi->getBrMuzickihSimbola() != 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);

									tekuciDesno->dodaj(p1);
									tekuciLevo->dodaj(akordLevi);
								}
								else if (akordDesni->getBrMuzickihSimbola() != 0 && akordLevi->getBrMuzickihSimbola() == 0) {
									Pauza* p1 = new Pauza(Razlomak(1, 4), true);

									tekuciDesno->dodaj(akordDesni);
									tekuciLevo->dodaj(p1);
								}
							}


						}

						for (int i = 0;i < textLine2.length() - kar.length();i++) textLine2[i] = textLine2[kar.length() + i];
						textLine2.resize(textLine2.length() - kar.length());

					}

				}
				file.close();

				k.dodajDesna(*tekuciDesno);
				k.dodajLeva(*tekuciLevo);
			}
			else cout << "Unable to open file\n";
		}
		else if (opcija==3){
			k.stampaj();
		}
		else if (opcija == 4) {
			k.iterirajKrozLevuRuku();
		}
		else if (opcija == 5) {
			k.iterirajKrozDesnuRuku();
		}
		else if (opcija == 6) {
			cout << endl << "Unesi brojilac pa imenilac" << endl;
			cin >> brojilac;
			cin >> imenilac;

			tekuciLevo = nullptr;
			tekuciDesno = nullptr;
			sledeciLevo = nullptr;
			sledeciDesno = nullptr;

			duzinaTakta = Razlomak(brojilac, imenilac);

			k = Kompozicija(duzinaTakta);
		}
		else if (opcija == 7) {
			checkMIDI = true;

			MIDI m = MIDI(k);
			m.formatiraj();
			m.eksportuj();

		}
		else if (opcija == 8) {
			checkMIDI = true;

			XML x = XML(k);
			x.formatirajXML();

		}
		else if (opcija == 9) {
			//BMP
		}
		else {
			if (checkMIDI == false) {
				cout << endl << "Zelite li da eksportujete MIDI fajl?" << endl;
				cout << "Unesite 1 za da i 0 za ne." << endl;
				int eksport = 0;
				cin >> eksport;
				if (eksport == 1) {
					MIDI m = MIDI(k);
					m.formatiraj();
					m.eksportuj();
				}
			}
			if (checkXML == false) {
				cout << endl << "Zelite li da eksportujete XML fajl?" << endl;
				cout << "Unesite 1 za da i 0 za ne." << endl;
				int eksport = 0;
				cin >> eksport;
				if (eksport == 1) {
					XML x = XML(k);
					x.formatirajXML();
				}
			}
			break;
		
		}
	}

	return 0;
}