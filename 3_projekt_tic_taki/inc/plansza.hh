#ifndef PLANSZA_HH
#define PLANSZA_HH

#include <iostream>
#include <vector>

#define PC 0
#define GRACZ 1
#define WIELKOSC_PLANSZY 8
#define GLEBOKOSC 2

struct Punkt
{
	int x;
	int y;
};

class Plansza
{
    int plansza[WIELKOSC_PLANSZY][WIELKOSC_PLANSZY];
public:
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

    void DodajIlosc(int iloscElem, int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5);
    void SprawdzPoziomy(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int poziom, 
                        int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
	void SprawdzPiony(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int poziom, 
    				  int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
	void SprawdzSkosyPrawe(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int skos, 
                      int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
	void SprawdzSkosyLewe(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int skos, 
                      int gracz, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);
	void SprawdzanieElementow(int gracz, int x, int y, int &iloscElem, 
                      int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5,
                      bool otwartyPoczatek, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron);


};

#endif