#include "Akord.h"

void Akord::ispisi()
{
	for (int i = 0; i < nizNota.size(); i++) {
		nizNota[i]->ispisi();
		if (nizNota[i]->getPovisena()) cout << " ";
	}
}
