#ifndef MacierzKwadratowa_h
#define MacierzKwadratowa_h

#include "MacierzProstokatna.h"

class MacierzKwadratowa:public MacierzProstokatna
{
    int rozmiar;
    complex<double> det;

    void permutacja(int,int*,int*);///POTRZEBNE DO WYZNACZNIKA
    int znak_permutacji(int*);///POTRZEBNE DO WYZNACZNIKA
    complex<double> dopelnienie_algebraiczne(int,int);///POTRZEBNE DO MACIERZY ODWROTNEJ
    float Knorma2_wektora(int,int);///POTRZEBNE DO HAUSHOLDERA kwadrat normy(od ktorego elementu,ktora kolumna)
    void zamien_na_jednostkowa();
    void wyznacznik();
    void subtract_to_element_macierzy(int,int,complex<double>);///MODYFIKACJA MACIERZY
    void zamien_wiersze_macierzy(int,int);///POTRZEBNE DO LU Z WEG
    int zwroc_wiersz(int);///ZWRACA NUMER WIERSZA W KTORYM JEST NAJWIEKSZY ELEMENT W DANEJ KOLUMNIE
    complex<double> Hyman_podzadanie(int,int);///JEZELI ELEMENT PODPRZEKATNIOWY 0 TO ZADANIE ROZBIJA SIE NA 2 NIEZALEZNE
    complex<double> Hyman_symetryczna(int);///JEZELI MACIERZ SYMETRYCZNA TO MAMY MACIERZ TROJDIAGONALNA I INNY ALGORYTM OBLICZENIA DET

public:
    void pobierz_z_pliku();
    MacierzKwadratowa odejmij_na_przekatnej(complex<double>);
    complex<double> przesuniecie(int,int);
    MacierzKwadratowa();
    MacierzKwadratowa(int);
    MacierzKwadratowa(const MacierzKwadratowa&);///KONSTRUKTOR KOPIUJACY
    ~MacierzKwadratowa();
    void pobierz_macierz();
    int get_rozmiar() const {return rozmiar;}
    MacierzKwadratowa operator*(const MacierzKwadratowa&);
    MacierzKwadratowa& operator=(const MacierzKwadratowa&);
    MacierzKwadratowa& operator=(const MacierzProstokatna&);
    MacierzKwadratowa operator-();///MACIERZ ODWROTNA
    MacierzKwadratowa odwrotnaLU();///ZWRACA MACIERZ ODWRORNA, KTORA LICZY KORZYSTAJAC Z ROZKLADU LU
    MacierzKwadratowa operator~();///MACIERZ TRANSPONOWANA
    complex<double>* operator*(complex<double>*);///MNOZENIE MACIERZY PRZEZ WEKTOR
    complex<double> get_det(){wyznacznik();return det;}
    MacierzKwadratowa eliminacja_Gaussa(int);///ROZKLAD LU 0-ZWRACA MACIERZ L, pozstale - zwraca U
    void rozwiaz_ukladLU(complex<double>*);///ROZWIAZANIE UKLADU KORZYSTAJAC Z ROZKLADU LU
    MacierzKwadratowa eliminacja_GaussaWEG();///ROZKLAD LU Z CZESCIOWYM WYBOREM ELEMENTU GLOWNEGO
    ///ZWRACA MACIERZ 0-1 KTORA MA 1 ZGODNE Z PERMUTACJA
    void rozwiaz_ukladLUzWEG(complex<double>*);///ROZWIAZANIE UKLADU KORZYSTAJAC Z ROZKLADU LU i WEG
    ///STOSUJEMY TU ROZKLAD LU DLA MACIERZY PA GDZIE P ZWRACA POWYZSZA METODA
    MacierzKwadratowa rozklad_HausholderaR();///ROZKLAD QR ZWRACA MACIERZ R
    MacierzKwadratowa rozklad_HausholderaQ();/// ZWRACA MACIERZ Q
    void Gram_Schmidt();///ROZKLAD QR METODA GRAMA-SCHMIDTA
    void rozwiaz_ukladQR(complex<double>*);///ROZWIAZANIE UKLADU KORZYSTAJAC Z ROZKLADU QR
    MacierzKwadratowa postac_Hessenberga();
    complex<double> algorytm_Hymana();///OBLICZNIE WYZNACZNIKA KORZYSTAJAC Z POSTACI HESSENBERGA
    void wyznacznikM();///WYPISUJE WYZNACZNIK OBLICZONY ROZNYMI SPOSOBAMI
    void ciag_Sturma();///PODAJE PRZEDZIAL W KTORYM ZNAJDUJE SIE PODANA WARTOSC WLASNA, DLA MACIERZY SYMETRYCZNYCH
    double ciag_Sturma(int);///ZWRACA PRZYBLIZONA WARTOSC WLASNA
    double lokalizacja_Gerszgorina(int);///PODAJE PRZEDZIAL W KTORYM ZNAJDUJA SIE WSZYSTKIE WARTOSCI WLASNE
    MacierzKwadratowa metodaQR();///ZNAJDOWANIE WSZYSTKICH WARTOSCI WLASNYCH MACIERZY
    void metoda_potegowa();///OBLICZA WEKTOR WLASNY DOMINUJACEJ WARTOSCI WLASNEJ DLA MAC SYMETRYCZNEJ Z DOMINUJACA WARTOSCIA WLASNA
    void metoda_Wielandta();///OBLICZA WEKTORY WLASNE DLA MACIERZY SYMETRYCZNEJ
    float norma_druga();

};

#endif // MacierzKwadratowa_h
