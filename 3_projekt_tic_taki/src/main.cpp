#include<iostream>
#include "plansza.hh"

using namespace std;

int main() {
	Plansza plansza;
	while(!plansza.CzyKoniec()) {
		plansza.RysujPlansze();
		plansza.RuchGracza(GRACZ);
		if(plansza.CzyKoniec())
			break;
		plansza.RuchPC();
	}
	plansza.RysujPlansze();
	if(plansza.CzyKoniec(GRACZ))
		cout << "GRACZ WYGRAL" << endl;
	else
		cout << "PC WYRAL" << endl;
	return 0;
}
