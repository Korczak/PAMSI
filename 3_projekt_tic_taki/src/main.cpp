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
		//plansza.RysujPlansze();
		//plansza.RuchGracza(PC);
		plansza.RuchPC();
	}
	plansza.RysujPlansze();
	if(plansza.CzyKoniec(GRACZ))
		cout << "GRACZ WYGRAL" << endl;
	else if(plansza.CzyKoniec(PC))
		cout << "PC WYRAL" << endl;
	else
		cout << "REMIS" << endl;
	return 0;
}
