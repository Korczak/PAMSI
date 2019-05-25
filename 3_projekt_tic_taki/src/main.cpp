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
	return 0;
}
