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

void Plansza::DodajIlosc(int iloscElem, int ilosc[]) {
    if(iloscElem == 0)
        return;
    ilosc[iloscElem - 1]++;
}

void Plansza::SprawdzanieElementow(int gracz, int x, int y, int &iloscElem, 
                                    int ilosc[],
                                    bool otwartyPoczatek, bool sprawdzOtwarte, bool sprawdzOtwarteZ2Stron) {
    if(gracz == GRACZ) {
        if(plansza[x][y] == 1) {
            iloscElem++;
        }
        else {
            if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron) {
                DodajIlosc(iloscElem, ilosc);
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
                DodajIlosc(iloscElem, ilosc);
            }
            iloscElem = 0;
        }
    }
}

void Plansza::SprawdzPoziomy(int ilosc[], int poziom, 
                             int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste
    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if(plansza[poziom][i] == 0) {
            otwartyPoczatek = true;
            DodajIlosc(iloscElem, ilosc);
            iloscElem = 0;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                
                SprawdzanieElementow(gracz, poziom, i, iloscElem, ilosc,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);
                
            }
        }
    }

    if(otwartyPoczatek || !sprawdzOtwarte)
        DodajIlosc(iloscElem, ilosc);
}



void Plansza::SprawdzPiony(int ilosc[], int pion, 
                           int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste
    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if(plansza[i][pion] == 0) {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron)
                DodajIlosc(iloscElem, ilosc);
            otwartyPoczatek = true;
            iloscElem = 0;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                SprawdzanieElementow(gracz, i, pion, iloscElem, ilosc,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);                
            }
        }
    }

    if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron)
        DodajIlosc(iloscElem, ilosc);
}

void Plansza::SprawdzSkosyPrawe(int ilosc[], int skos, 
                           int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste
    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if((skos - i >= 0 && skos - i < WIELKOSC_PLANSZY) == false)
            break;

        if(plansza[skos - i][i] == 0) {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron)
                DodajIlosc(iloscElem, ilosc);
            iloscElem = 0;
            otwartyPoczatek = true;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                SprawdzanieElementow(gracz, skos - i, i, iloscElem, ilosc,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);
            }
        }
    }

    if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron)
        DodajIlosc(iloscElem, ilosc);
}

void Plansza::SprawdzSkosyLewe(int ilosc[], int skos, 
                           int gracz, bool sprawdzOtwarte = false, bool sprawdzOtwarteZ2Stron = false) { //z obu stron jest puste

    bool otwartyPoczatek = false;
    int iloscElem = 0;
    for(int i = 0; i < WIELKOSC_PLANSZY; i++) {
        if((skos + i >= 0 && skos + i < WIELKOSC_PLANSZY) == false)
            break;

        if(plansza[skos + i][i] == 0) {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron)
                DodajIlosc(iloscElem, ilosc);
            iloscElem = 0;
            otwartyPoczatek = true;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                
                SprawdzanieElementow(gracz, skos + i, i, iloscElem, ilosc,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron);
                
            }
        }
    }

    if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron)
        DodajIlosc(iloscElem, ilosc);
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
    int ilosc[ILOSC_W_RZEDZIE];

    for(int i = 0; i < ILOSC_W_RZEDZIE; i++)
        ilosc[i] = 0;
    for(int i = -WIELKOSC_PLANSZY + 1; i < WIELKOSC_PLANSZY; i++)
        SprawdzSkosyLewe(ilosc, i, gracz);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY - 1; i++)
        SprawdzSkosyPrawe(ilosc, i, gracz);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        SprawdzPiony(ilosc, i, gracz);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        SprawdzPoziomy(ilosc, i, gracz);
    
    if(ilosc[ILOSC_W_RZEDZIE - 1] > 0)
        return true;
    return false;
    
}

int obliczWartoscPlanszy(Plansza p, bool czyOtwarte, bool czyOtwarteZ2Stron) {
    int wartosc = 0;
    int ilosc[ILOSC_W_RZEDZIE];
    for(int i = 0; i < ILOSC_W_RZEDZIE; i++)
        ilosc[i] = 0;


    for(int i = -WIELKOSC_PLANSZY; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyLewe(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyPrawe(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPiony(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPoziomy(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);

    int wartoscRzedu = 1;
    for(int i = 0; i < ILOSC_W_RZEDZIE; i++) {
        wartosc += ilosc[i] * wartoscRzedu;
        wartoscRzedu *= 25;
        ilosc[i] = 0;
    }
    
    for(int i = -WIELKOSC_PLANSZY; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyLewe(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyPrawe(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPiony(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPoziomy(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);

    wartoscRzedu = 1;
    for(int i = 0; i < ILOSC_W_RZEDZIE; i++) {
        wartosc -= ilosc[i] * wartoscRzedu;
        wartoscRzedu *= 30;
        ilosc[i] = 0;
    }

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





