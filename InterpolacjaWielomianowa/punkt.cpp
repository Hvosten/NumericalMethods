#include <iostream>
#include "punkt.h"

using namespace std;

Punkt::Punkt()
{
    x = 0;
    y = 0;
    krotnosc = 0;
    tab = NULL;
}

Punkt::~Punkt()
{
    delete [] tab;
}

float Punkt::zwroc_x()
{
    return x;
}

float Punkt::zwroc_y()
{
    return y;
}

int Punkt::get_krotnosc()
{
    return krotnosc;
}

float Punkt::zwroc_krotnosc(int n)
{
    return tab[n-1];
}

void Punkt::pobierz()
{
    cout<<"Podaj wspolrzedne punktu: ";
    cin>>x>>y;
    cout<<"Podaj krotnosc punktu: ";
    cin>>krotnosc;
    if(krotnosc > 1)
    {
        suma_krotnosci += krotnosc;
        tab = new float [krotnosc-1];
        cout<<"Podaj "<<krotnosc-1<<" wartosci odpowiadajace krotnosciom: ";
        for(int i = 0 ; i < krotnosc-1 ; ++i)
            cin>>tab[i];
    }
    else
        ++suma_krotnosci;
}

void Punkt::wyswietl()
{
    cout<<"("<<x<<","<<y<<") "<<krotnosc<<" ";
    for(int i = 0 ; i < krotnosc-1 ; ++i)
        cout<<i+1<<"#"<<tab[i]<<" ";
    cout<<endl;
}

