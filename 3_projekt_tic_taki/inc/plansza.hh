#ifndef PLANSZA_HH
#define PLANSZA_HH

#include <iostream>
#include <vector>

#define PC 0
#define GRACZ 1
#define GLEBOKOSC 2
#define WIELKOSC_PLANSZY 8
#define ILOSC_W_RZEDZIE 5

struct Punkt
{
	int x;
	int y;
};

class Plansza
{
    public:
    int plansza[WIELKOSC_PLANSZY][WIELKOSC_PLANSZY];

    Plansza(); //Creates an empty board
    Plansza(const Plansza &p); //Creates copied board
    Plansza& operator=(const Plansza &p); //Creates copied board

    void RysujPlansze();
	 void ZrobRuch(int x, int y, int gracz);
    bool CzyPoprawnePole(int x, int y);
    bool CzyZajetePole(int x, int y);
    bool CzyKoniec();
    bool CzyKoniec(int gracz);
    void RuchGracza(int gracz);
    void RuchPC();

    void DodajIlosc(int iloscElem, int ilosc[]);
    void SprawdzPoziomy(int ilosc[], int poziom, 
                        int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
  	void SprawdzPiony(int ilosc[], int poziom, 
      				  int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
  	void SprawdzSkosyPrawe(int ilosc[], int skos, 
                        int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
  	void SprawdzSkosyLewe(int ilosc[], int skos, 
                        int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
  	void SprawdzanieElementow(int gracz, int x, int y, int &iloscElem, 
                        int ilosc[],
                        bool otwartyPoczatek, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);


};

#endif