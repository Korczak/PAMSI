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

    iloscWykonanychRuchow++;
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

    if(iloscWykonanychRuchow >= WIELKOSC_PLANSZY * WIELKOSC_PLANSZY)
        return true;

    if(CzyKoniec(GRACZ)) //czy Gracz wygral
        return true;

    if(CzyKoniec(PC)) //czy PC wygral
        return true;

    return false;
}

bool Plansza::CzyKoniec(int gracz) {
    int ilosc[ILOSC_W_RZEDZIE];

    for(int i = 0; i < ILOSC_W_RZEDZIE; i++)
        ilosc[i] = 0;
    for(int i = -WIELKOSC_PLANSZY * 2; i < WIELKOSC_PLANSZY * 2; i++)
        SprawdzSkosyLewe(ilosc, i, gracz);
    for(int i = -WIELKOSC_PLANSZY * 2; i < WIELKOSC_PLANSZY * 2; i++)
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


    //Sprawdzanie elementow w rzedzie dla PC
    for(int i = -WIELKOSC_PLANSZY * 2; i < WIELKOSC_PLANSZY * 2; i++)
        p.SprawdzSkosyLewe(ilosc, i, PC, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = -WIELKOSC_PLANSZY * 2; i < WIELKOSC_PLANSZY * 2; i++)
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
    for(int i = -WIELKOSC_PLANSZY * 2; i < WIELKOSC_PLANSZY * 2; i++)
        p.SprawdzSkosyLewe(ilosc, i, GRACZ, czyOtwarte, czyOtwarteZ2Stron);
    for(int i = -WIELKOSC_PLANSZY * 2; i < WIELKOSC_PLANSZY * 2; i++)
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

int min(int a, int b) { //zwraca wartosc minimalna
    if(a > b)
        return b;
    return a;
}


int max(int a, int b) { //zwraca wartosc maksymalna
    if(a > b)
        return a;
    return b;
}

int alfaBeta(Plansza p, int glebokosc, int gracz, int alfa, int beta, Punkt& ruch) {
    if(p.CzyKoniec(PC)) 
        return inf - 1; //sprawdz czy nie wygral jeden z graczy danej planszy
    if(p.CzyKoniec(GRACZ))
        return -inf + 1;
    
    
    if(glebokosc == 0)
        return obliczWartoscPlanszy(p); //oblicz wartosc planszy

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
                if(gracz == PC) {
                    wynik = alfaBeta(nowaPlansza, glebokosc - 1, GRACZ, alfa, beta, ruch);
                    if(GLEBOKOSC == glebokosc && wynik > alfa) { //zapisz tylko ruchy dla pierwszego ruchu od obecnej planszy
                        ruch.x = x;
                        ruch.y = y;
                    }
                    alfa = max(alfa, wynik); //wylicz alfaBeta dla planszy
                    if(alfa>=beta) //odcinamy galaz, poniewaz nie ma sensu jej dalej sprawdzac
                        return alfa;
                }
                else {
                    wynik = alfaBeta(nowaPlansza, glebokosc - 1, PC, alfa, beta, ruch);
                    beta = min(beta, wynik);
                    if(alfa>=beta) //odcinamy galaz, poniewaz nie ma sensu jej dalej sprawdzac
                        return beta;
                }

                   

            }
        }
    }

    if(iloscNowychRuchow == 0) { //jezeli nie ma mozliwych nowych ruchow dla obecnej planszy
        wynik = alfaBeta(p, 0, gracz, alfa, beta, ruch);

        if(gracz == PC)
            alfa = max(alfa, wynik); //wylicz alfaBeta dla planszy
        else
            beta = min(beta, wynik);
    }

    if(gracz == PC)
        return alfa;
    return beta;
}


int minMax(Plansza p, int glebokosc, int gracz, Punkt& ruch) {
    return alfaBeta(p, glebokosc, gracz, -inf, inf, ruch);
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





