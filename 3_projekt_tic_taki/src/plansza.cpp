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

Plansza::Plansza(const Plansza &p) //konstruktor kopiujacy
{
    for(int x = 0; x < WIELKOSC_PLANSZY; x++)
    {
        for(int y = 0; y < WIELKOSC_PLANSZY; y++)
        {
            this->plansza[x][y]=p.plansza[x][y];
        }
    }
}

Plansza& Plansza::operator=(const Plansza &p) //operator przypisania
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

void Plansza::RysujPlansze() //rysuj plansze
{
    cout<<endl<<"         KOLUMNY                         ";
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
                cout<<"|X"; //PC
            if(plansza[i][j]==1)
                cout<<"|O"; //GRACZ
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
        plansza[x][y] = 1; //zaznacz O na planszy
    else 
        plansza[x][y] = -1; //zaznacz X na planszy
}

bool Plansza::CzyPoprawnePole(int x, int y) {
    if(x >= 0 && x < WIELKOSC_PLANSZY && y >= 0 && y < WIELKOSC_PLANSZY)
        return true; //czy miesci sie w zakresie planszy
    return false; 
}

bool Plansza::CzyZajetePole(int x, int y) {
    if(plansza[x][y] == 0)//puste pole
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
    if(gracz == GRACZ) { //sprawdzenie elementu dla gracza
        if(plansza[x][y] == 1) {
            iloscElem++; //jezeli jest O
        }
        else {//puste pole
            if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron) {
                DodajIlosc(iloscElem, ilosc); //pod odpowiednimi warunkami dodaj do ilosci
            }
            iloscElem = 0; 
        }
    }
    else { //sprawdzenie dla PC
        if(plansza[x][y] == -1) { //jezeli jest X
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
        if((skos + i >= 0 && skos + i < WIELKOSC_PLANSZY) == false) //sprawdzenie czy poza zakresem
            break;

        if(plansza[skos + i][i] == 0) { //sprawdzenie czy 'puste' pole
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron)
                DodajIlosc(iloscElem, ilosc); //Dodaj do wartosc iloscElem do tablicy ilosc
            iloscElem = 0;
            otwartyPoczatek = true;
        }
        else {
            if(otwartyPoczatek || !sprawdzOtwarteZ2Stron || !sprawdzOtwarte) {
                
                SprawdzanieElementow(gracz, skos + i, i, iloscElem, ilosc,
                                        otwartyPoczatek, sprawdzOtwarte, sprawdzOtwarteZ2Stron); //dodaj do tablicy ilosc, 
                                                                                                 //gdy spelnione odpowiednie warunki
                
            }
        }
    }

    if((otwartyPoczatek || !sprawdzOtwarte) && !sprawdzOtwarteZ2Stron)
        DodajIlosc(iloscElem, ilosc);
}

bool Plansza::CzyKoniec() {
    bool czyKoniec = false;
    czyKoniec = CzyKoniec(GRACZ); //czy Gracz wygral
    if(czyKoniec)
        return true;
    czyKoniec = CzyKoniec(PC); //czy PC wygral
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
    if(ilosc[ILOSC_W_RZEDZIE - 1] > 0) //sprawdzenie czy ilosc elementow w rzedzie jest rowna maksymalnej wartosci
        return true;
    return false;
    
}

int obliczWartoscPlanszy(Plansza p, bool czyOtwarte, bool czyOtwarteZ2Stron) {
    int wartosciX[10] = {1, 5, 50, 500, 5000, 50000, 500000, 5000000}; //wartosci mnoznika dla X
    int wartosciKolek[10] = {1, 6, 60, 600, 6000, 60000, 600000, 6000000}; //wartosci mnoznika dla O

    int wartosc = 0; //wartosc planszy
    int ilosc[ILOSC_W_RZEDZIE]; //ilosc elementow w rzedzie
    for(int i = 0; i < ILOSC_W_RZEDZIE; i++)
        ilosc[i] = 0;

    if(p.CzyKoniec(PC))
        return -9999999; //sprawdz czy nie wygral jeden z graczy danej planszy
    if(p.CzyKoniec(GRACZ))
        return 9999999;

    //Sprawdzanie elementow w rzedzie dla PC
    for(int i = -WIELKOSC_PLANSZY; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyLewe(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyPrawe(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPiony(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPoziomy(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);

    for(int i = 0; i < ILOSC_W_RZEDZIE; i++) {
        wartosc += ilosc[i] * wartosciX[i];
        ilosc[i] = 0;
    }

    //Sprawdzanie elementow w rzedzie dla GRACZA    
    for(int i = -WIELKOSC_PLANSZY; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyLewe(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY + WIELKOSC_PLANSZY; i++)
        p.SprawdzSkosyPrawe(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPiony(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = 0; i < WIELKOSC_PLANSZY; i++)
        p.SprawdzPoziomy(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);

    for(int i = 0; i < ILOSC_W_RZEDZIE; i++) {
        wartosc -= ilosc[i] * wartosciKolek[i];
        ilosc[i] = 0;
    }


    return wartosc;
}

int obliczWartoscPlanszy(Plansza p) {
    int wartosc = 0;
    wartosc += 1 * obliczWartoscPlanszy(p, false, false); //wynik pomnoz przez 1 dla wszystkich elementow, nawet zamknietych z obu stron
    wartosc += 2 * obliczWartoscPlanszy(p, true, false); //wynik pomnoz przez 3 dla otwartych z jednej strony elementow
    wartosc += 3 * obliczWartoscPlanszy(p, true, true); //wynik pomnoz przez 10 dla otwartych z obu stron

    return wartosc;
}

int minMax(Plansza p, int glebokosc, int gracz, Punkt& ruch) {
    if(glebokosc == 0)
        return obliczWartoscPlanszy(p); //oblicz wartosc planszy

    int max = -9999999, min = 9999999;
    int iloscNowychRuchow = 0;
    int wynik;

    for(int x = 0; x < WIELKOSC_PLANSZY; x++) {
        for(int y = 0; y < WIELKOSC_PLANSZY; y++) {
            if(!p.CzyZajetePole(x, y)) { //sprawdz wszystkie mozliwe ruchy dla obecnej planszy
                iloscNowychRuchow++; //do sprawdzenia czy jest mozliwy ruch dla planszy
                Plansza nowaPlansza;
                nowaPlansza = p;
                nowaPlansza.ZrobRuch(x, y, gracz); //zrob ruch dla planszy
                wynik = 0;
                if(gracz == PC)
                    wynik = minMax(nowaPlansza, glebokosc - 1, GRACZ, ruch); //wylicz minMax dla planszy
                else
                    wynik = minMax(nowaPlansza, glebokosc - 1, PC, ruch);
                
                if(glebokosc == GLEBOKOSC) {
                    nowaPlansza.RysujPlansze();
                    cout << wynik << endl;
                }

                if(gracz == PC) { //wybierz najlepszy ruch dla PC
                    if(max < wynik) {
                        max = wynik;
                        if(GLEBOKOSC == glebokosc) { //zapisz tylko ruchy dla pierwszego ruchu od obecnej planszy
                            ruch.x = x;
                            ruch.y = y;
                        }
                    }
                }
                else {
                    if(min > wynik) { //wybierz najlepszy ruch dla GRACZA
                        min = wynik;
                        if(GLEBOKOSC == glebokosc) { //zapisz tylko ruchy dla pierwszego ruchu od obecnej planszy
                            ruch.x = x;
                            ruch.y = y;
                        }
                    }
                }
            }
        }
    }
    if(iloscNowychRuchow == 0) { //jezeli nie ma mozliwych nowych ruchow dla obecnej planszy
        wynik = minMax(p, 0, gracz, ruch);

        if(gracz == PC) {
            if(max < wynik) {
                max = wynik;
            }
        }
        else {
            if(min > wynik) {
                min = wynik;
            }
        }
    }

    if(gracz == PC)
        return max;
    return min;
}

void Plansza::RuchPC() {
    Punkt ruch;
    minMax((*this), GLEBOKOSC, PC, ruch); //znajdz najlepszy ruch, zapisz go w parametrze ruch

    ZrobRuch(ruch.x, ruch.y, PC);
}

void Plansza::RuchGracza(int gracz) {
    int x, y;
    bool czyPoprawnePola = false;
    while(!czyPoprawnePola) {
        cout << "Podaj wiersz i kolumne pola" << endl; //podaj ruch gracza
        cin >> x >> y;
        
        if(CzyPoprawnePole(x, y)) {
            if(!CzyZajetePole(x, y)) {
                czyPoprawnePola = true; //sprawdz czy poprawnie podano pole
                
            }
        }    
    }

    ZrobRuch(x, y, gracz);    
}





