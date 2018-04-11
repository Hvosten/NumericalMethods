#include <iostream>
#include "punkt.h"
#include <windows.h>
#include <conio.h>
#include <math.h>

using namespace std;
HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);

int Punkt::suma_krotnosci = 0;

int silnia(int n)
{
    int wynik = 1;
    for(int i = 2 ; i <= n ; ++i)
        wynik *= i;
    return wynik;
}

void wyswietl_punkty(Punkt *tab,int ilosc)
{
    for(int i = 0 ; i < ilosc ; ++i)
        tab[i].wyswietl();
}

void wyswietl_tablice(float **A)
{
    ///WYPISYWANIE TABLICY
    cout<<endl;
    for(int i = 0 ; i < Punkt::suma_krotnosci ; ++i , cout<<endl)
        for(int j = 0 ; j < Punkt::suma_krotnosci+1 ; ++j)
            if(i+1 == j)
            {
                SetConsoleTextAttribute(uchwyt,12);
                cout<<A[i][j]<<'\t';
                SetConsoleTextAttribute(uchwyt,15);
            }
            else
                cout<<A[i][j]<<'\t';
}

void oblicz_wspol(float **A,int ile, Punkt *tab)
{
    int kolumna = 0;
    for(int i = 0 ; i < ile ; ++i)
    {
        for(int j = 1 ; j <= tab[i].get_krotnosc() ; ++j)
        {
            A[kolumna][0] = tab[i].zwroc_x();
            A[kolumna][1] = tab[i].zwroc_y();
            for(int k = 1 ; k < j ; ++k)
                A[kolumna][1+k] = tab[i].zwroc_krotnosc(k)/silnia(k);
            ++kolumna;
        }
    }

    ///OBLICZANIE WSPÓ£CZYNNIKÓW
    for(int j = 2 ; j <= Punkt::suma_krotnosci ; ++j)
    {
        int  s = 0;
        for(int i = j-1 ; i < Punkt::suma_krotnosci ; ++i)
            if(A[i][0]!=A[s][0])
                A[i][j] = (A[i][j-1]-A[i-1][j-1])/(A[i][0]-A[s++][0]);
            else
                ++s;
    }

}

float suma_iloczynow(float **A,int n, int k)///n z ilu elementów, k ile elemntów
{
    float suma = 0 , iloczyn;

    int *tab = new int[n];

    int dokad = pow(2,n);
    for(int i = 0 ; i < dokad ; ++i)
    {
        for(int j = 0 ; j < n ; ++j)
            tab[j] = 0;

        int licznik = 0 , liczba = i, miejsce = n-1;
        while(liczba)
        {
            if(liczba - pow(2,miejsce) >= 0)
            {
                tab[n-miejsce-1] = 1;
                liczba -= pow(2,miejsce);
                ++licznik;
            }
            --miejsce;
        }
        if(licznik == k)
        {
            ///DODAWANIE SUM
            iloczyn = 1;
            for(int s = 0 ; s < n ; ++s)
                if(tab[s] == 1)
                    iloczyn *= A[s][0];
            suma += iloczyn;
        }
    }



    delete [] tab;

    return suma*pow(-1,k);
}


int main()
{
    cout<<endl;
    SetConsoleTextAttribute(uchwyt,10);
    cout<<"INTERPOLACJA WIELOMIANOWA METODA NEWTONA Z POWTARZALNYMI WEZLAMI"<<endl;
    SetConsoleTextAttribute(uchwyt,15);
    cout<<endl;
    int maks_p, ilosc_p = 0, wybor;
    cout << "Ile punktow maksymalnie bedziesz chcial podac: ";
    cin>>maks_p;
    Punkt *punkty = new Punkt [maks_p];
    float **tab = new float *[Punkt::suma_krotnosci];
    for(int i = 0 ; i < Punkt::suma_krotnosci ; ++i)
    {
        tab[i] = new float [Punkt::suma_krotnosci+1];
        ///WYPE£NIENIE ZERAMI
        for(int j = 0 ; j < Punkt::suma_krotnosci+1 ; ++j)
            tab[i][j] = 0;
    }



    do
    {
        system("cls");
        float **tab = new float *[Punkt::suma_krotnosci];
        for(int i = 0 ; i < Punkt::suma_krotnosci ; ++i)
        {
            tab[i] = new float [Punkt::suma_krotnosci+1];
            ///WYPE£NIENIE ZERAMI
            for(int j = 0 ; j <= Punkt::suma_krotnosci ; ++j)
                tab[i][j] = 0;
        }
        oblicz_wspol(tab,ilosc_p,punkty);
        wyswietl_tablice(tab);

        cout<<endl;
        SetConsoleTextAttribute(uchwyt,10);
        cout<<"INTERPOLACJA WIELOMIANOWA METODA NEWTONA Z POWTARZALNYMI WEZLAMI - MENU"<<endl;
        SetConsoleTextAttribute(uchwyt,14);
        cout<<"---------------------------------"<<endl;
        cout<<"1.Koniec"<<endl;
        cout<<"2.Dodaj punkt"<<endl;
        cout<<"3.Oblicz wspolczynniki wielomianu"<<endl;
        cout<<"---------------------------------"<<endl;
        SetConsoleTextAttribute(uchwyt,15);
        cout<<"Wybor: ";
        cin>>wybor;

        switch(wybor)
        {
            case 1:
                {
                    ///ZWALNIANIE PAMIÊCI
                    for(int i = 0 ; i < Punkt::suma_krotnosci ; ++i)
                        delete [] tab[i];
                    delete [] tab;

                    delete [] punkty;
                    exit(0);
                }
            case 2:
                if( maks_p == ilosc_p )
                {
                    cout<<"Zadeklarowales tylko "<<maks_p<<" punktow !!!"<<endl;
                    getch();
                }
                else
                {
                    for(int i = 0 ; i < Punkt::suma_krotnosci ; ++i)
                        delete [] tab[i];
                    delete [] tab;
                    punkty[ilosc_p++].pobierz();
                }
                break;
            case 3:
                {
                    ///OBLICZANIE WSPÓ£CZYNNIKÓW WIELOMIANU
                    float *wspol = new float[Punkt::suma_krotnosci];
                    for(int i = 0 ; i < Punkt::suma_krotnosci ; ++i)
                        wspol[i] = 0;

                    wspol[Punkt::suma_krotnosci-1] = tab[Punkt::suma_krotnosci-1][Punkt::suma_krotnosci];
                    for(int i = Punkt::suma_krotnosci-2 ; i >= 0 ; --i)
                    {
                        wspol[i] = tab[i][i+1];
                        for(int j = Punkt::suma_krotnosci-1 ; j > i ; --j)
                           wspol[i] += tab[j][j+1]*suma_iloczynow(tab,j,j-i);
                    }

                    cout<<endl;
                    SetConsoleTextAttribute(uchwyt,11);
                    for(int i = 0 ; i < Punkt::suma_krotnosci ; ++i)
                    {
                        if(wspol[i] != 0 && wspol[i] != 1)
                            cout<<wspol[i];
                        else
                            if(wspol[i] == 1 && i == 0)
                                cout<<wspol[i];
                        if(i != 0 && i != 1 && wspol[i] != 0)
                            cout<<"x^"<<i;
                        else
                            if(i == 1 && wspol[i] != 0)
                                cout<<"x";
                        if(i != Punkt::suma_krotnosci-1)
                            if(wspol[i+1] > 0)
                                cout<<"+";
                    }
                    SetConsoleTextAttribute(uchwyt,15);
                    getch();
                    break;
                }
            default:
                {
                    cout<<"POMYLKA!";
                    getch();
                    break;
                }
        }

    }while(wybor != 1);

    return 0;
}
