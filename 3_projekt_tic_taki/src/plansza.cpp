#include "plansza.hh"

using namespace std;

Plansza::Plansza()
{
    for(int i=0; i<WIELKOSC_PLANSZY; i++)
    {
        for (int j=0; j<WIELKOSC_PLANSZY; j++)
        {
            plansza[i][j]=0;
        }
    }
}

Plansza::Plansza(const Plansza &p)
{
    for(int x = 0; x < WIELKOSC_PLANSZY; x++)
    {
        for(int y = 0; y < WIELKOSC_PLANSZY; y++)
        {
            this->plansza[x][y]=p.plansza[x][y];
        }
    }
}

Plansza& Plansza::operator=(const Plansza &p)
{
    for(int x = 0; x < WIELKOSC_PLANSZY; x++)
    {
        for(int y = 0; y < WIELKOSC_PLANSZY; y++)
        {
            this->plansza[x][y]=p.plansza[x][y];
        }
    }
    return *this;
}

void Plansza::RysujPlansze()
{
    cout<<endl<<"                      WIERSZE                         ";
    cout<<endl<<"    ";
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        cout << " " << i;
    cout << endl;

    for(int i=0; i<WIELKOSC_PLANSZY; i++)
    {   
        cout << "    ";
        for(int j = 0; j < WIELKOSC_PLANSZY; j++) 
            cout << "--";
        cout << "-" << endl;
        cout<< i << "   ";
        for(int j=0; j<WIELKOSC_PLANSZY; j++)
        {
            if(plansza[i][j]==-1)
                cout<<"|X";
            if(plansza[i][j]==1)
                cout<<"|O";
            if(plansza[i][j]==0)
                cout<<"| ";
        }
        cout<< "|  " << i <<endl;
    }        
    cout << "    ";
    for(int j = 0; j < WIELKOSC_PLANSZY; j++) 
        cout << "--";
    cout << "-" << endl;    
    cout<<"    ";
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        cout << " " << i;
    cout << endl << endl;

}

void Plansza::ZrobRuch(int x, int y, int gracz) {
    if(gracz == GRACZ)
        plansza[x][y] = 1;
    else 
        plansza[x][y] = -1;
}

bool Plansza::CzyPoprawnePole(int x, int y) {
    if(x >= 0 && x < WIELKOSC_PLANSZY && y >= 0 && y < WIELKOSC_PLANSZY)
        return true;
    return false; 
}

bool Plansza::CzyZajetePole(int x, int y) {
    if(plansza[x][y] == 0)
        return false;
    return true;
}

void Plansza::DodajIlosc(int iloscElem, int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5) {
    switch(iloscElem) {
        case 1:
            ilosc1++;
            break;
        case 2:
            ilosc2++;
            break;
        case 3:
            ilosc3++;
            break;
        case 4:
            ilosc4++;
            break;
        case 5:
            ilosc5++;
            break;
    }
}

void Plansza::SprawdzanieElementow(int gracz, int x, int y, int &iloscElem, 
                                    int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5,
                                    bool otwartyPoczatek, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron) {
    if(gracz == GRACZ) {
        if(plansza[x][y] == 1) {
            iloscElem++;
        }
        else {
            if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron) {
                DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
            }
            iloscElem = 0;
        }
    }
    else {
        if(plansza[x][y] == -1) {
            iloscElem++;
        }
        else {
            if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron) {
                DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
            }
            iloscElem = 0;
        }
    }
}

void Plansza::SprawdzPoziomy(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int poziom, 
                             int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste
    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if(plansza[poziom][i] == 0) {
            otwartyPoczatek = true;
            DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
            iloscElem = 0;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                
                SprawdzanieElementow(gracz, poziom, i, iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);
                
            }
        }
    }

    if(otwartyPoczatek || !sprawdzOtwarte)
        DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
}



void Plansza::SprawdzPiony(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int pion, 
                           int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste
    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if(plansza[i][pion] == 0) {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron)
                DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
            otwartyPoczatek = true;
            iloscElem = 0;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                SprawdzanieElementow(gracz, i, pion, iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);                
            }
        }
    }

    if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron)
        DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
}

void Plansza::SprawdzSkosyPrawe(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int skos, 
                           int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste
    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if((skos - i >= 0 && skos - i < WIELKOSC_PLANSZY) == false)
            break;

        if(plansza[skos - i][i] == 0) {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron)
                DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
            iloscElem = 0;
            otwartyPoczatek = true;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                
                SprawdzanieElementow(gracz, skos - i, i, iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);
                
            }
        }
    }

    if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron)
        DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
}

void Plansza::SprawdzSkosyLewe(int& ilosc1, int& ilosc2, int& ilosc3, int&ilosc4, int& ilosc5, int skos, 
                           int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste
    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if((skos + i >= 0 && skos + i < WIELKOSC_PLANSZY) == false)
            break;

        if(plansza[skos + i][i] == 0) {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron)
                DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
            iloscElem = 0;
            otwartyPoczatek = true;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                
                SprawdzanieElementow(gracz, skos + i, i, iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);
                
            }
        }
    }

    if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron)
        DodajIlosc(iloscElem, ilosc1, ilosc2, ilosc3, ilosc4, ilosc5);
}

bool Plansza::CzyKoniec() {
    bool czyKoniec = false;
    czyKoniec = CzyKoniec(GRACZ);
    if(czyKoniec)
        return true;
    czyKoniec = CzyKoniec(PC);
    if(czyKoniec)
        return true;

    return false;
}

bool Plansza::CzyKoniec(int gracz) {
    int ilosc1, ilosc2 = 0, ilosc3 = 0, ilosc4 = 0, ilosc5 = 0;

    for(int i = -WIELKOSC_PLANSZY + 1; i < WIELKOSC_PLANSZY; i++)
        SprawdzSkosyLewe(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, gracz);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY - 1; i++)
        SprawdzSkosyPrawe(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, gracz);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        SprawdzPiony(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, gracz);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        SprawdzPoziomy(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, gracz);
    
    if(ilosc5 > 0)
        return true;
    return false;
    
}

int obliczWartoscPlanszy(Plansza p, bool czyOtwarte, bool czyOtwarteZ2Stron) {
    int wartosc = 0;
    int ilosc1 = 0, ilosc2 = 0, ilosc3 = 0, ilosc4 = 0, ilosc5 = 0;


    for(int i = -WIELKOSC_PLANSZY; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyLewe(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyPrawe(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPiony(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPoziomy(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, PC, czyOtwarte, czyOtwarteZ2Stron);

    wartosc += (ilosc1 * 1 + ilosc2 * 3 + ilosc3 * 10 + ilosc4 * 30 + ilosc5 * 100);

    ilosc1 = 0, ilosc2 = 0, ilosc3 = 0, ilosc4 = 0, ilosc5 = 0;
    
    for(int i = -WIELKOSC_PLANSZY; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyLewe(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyPrawe(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPiony(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPoziomy(ilosc1, ilosc2, ilosc3, ilosc4, ilosc5, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);

    wartosc -= (ilosc1 * 1 + ilosc2 * 3 + ilosc3 * 10 + ilosc4 * 30 + ilosc5 * 100);

    return wartosc;
}

int obliczWartoscPlanszy(Plansza p) {
    int wartosc = 0;
    wartosc += 1 * obliczWartoscPlanszy(p, false, false);
    wartosc += 3 * obliczWartoscPlanszy(p, true, false);
    wartosc += 10 * obliczWartoscPlanszy(p, true, true);

    return wartosc;
}

int minMax(Plansza p, int glebokosc, int gracz, Punkt& ruch) {
    if(glebokosc == 0)
        return obliczWartoscPlanszy(p);

    int max = -999999, min = 999999;

    for(int x = 0; x < WIELKOSC_PLANSZY; x++) {
        for(int y = 0; y < WIELKOSC_PLANSZY; y++) {
            if(!p.CzyZajetePole(x, y)) {
                Plansza nowaPlansza;
                nowaPlansza = p;
                nowaPlansza.ZrobRuch(x, y, gracz);
                int wynik;
                if(gracz == PC)
                    wynik = minMax(nowaPlansza, glebokosc - 1, GRACZ, ruch);
                else
                    wynik = minMax(nowaPlansza, glebokosc - 1, PC, ruch);

                /*
                if(glebokosc == GLEBOKOSC) {
                    nowaPlansza.RysujPlansze();
                    cout << wynik << endl;
                }
                */

                if(gracz == PC) {
                    if(max < wynik) {
                        max = wynik;
                        if(glebokosc == GLEBOKOSC) {
                            ruch.x = x;
                            ruch.y = y;
                        }
                    }
                }
                else {
                    if(min > wynik) {
                        min = wynik;
                        if(glebokosc == GLEBOKOSC) {
                            ruch.x = x;
                            ruch.y = y;
                        }
                    }
                }
            }
        }
    }

    if(gracz == PC)
        return max;
    else
        return min;
    return 0;
}

void Plansza::RuchPC() {
    Punkt ruch;
    minMax((*this), GLEBOKOSC, PC, ruch);

    ZrobRuch(ruch.x, ruch.y, PC);
}

void Plansza::RuchGracza(int gracz) {
    int x, y;
    bool czyPoprawnePola = false;
    while(!czyPoprawnePola) {
        cout << "Podaj wiersz i kolumne pola" << endl;
        cin >> x >> y;
        
        if(CzyPoprawnePole(x, y)) {
            if(!CzyZajetePole(x, y)) {
                czyPoprawnePola = true;
                
            }
        }    
    }

    ZrobRuch(x, y, gracz);    
}





