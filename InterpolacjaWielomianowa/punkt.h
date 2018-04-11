#include <iostream>

using namespace std;


class Punkt
{
    float x,y;
    int krotnosc;
    float *tab;
public:
    static int suma_krotnosci;
    Punkt();
    ~Punkt();
    float zwroc_x();
    float zwroc_y();
    int get_krotnosc();
    float zwroc_krotnosc(int);
    void pobierz();
    void wyswietl();

};
