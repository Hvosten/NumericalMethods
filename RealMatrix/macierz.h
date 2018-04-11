#include <iostream>

using namespace std;


class Macierz
{
    float **M;
    int rozmiar;
    float det;

    void permutacja(int,int*,int*);///POTRZEBNE DO WYZNACZNIKA
    int znak_permutacji(int*);///POTRZEBNE DO WYZNACZNIKA
    float dopelnienie_algebraiczne(int,int);///POTRZEBNE DO MACIERZY ODWROTNEJ
    float Knorma2_wektora(int,int);///POTRZEBNE DO HAUSHOLDERA kwadrat normy(od ktorego elementu,ktora kolumna)
    void zamien_na_jednostkowa();
    void wyznacznik();
    void subtract_to_element_macierzy(int,int,float);///MODYFIKACJA MACIERZY
    void zamien_wiersze_macierzy(int,int);///POTRZEBNE DO LU Z WEG
    int zwroc_wiersz(int);///ZWRACA NUMER WIERSZA W KTORYM JEST NAJWIEKSZY ELEMENT W DANEJ KOLUMNIE
    float Hyman_podzadanie(int,int);///JEZELI ELEMENT PODPRZEKATNIOWY 0 TO ZADANIE ROZBIJA SIE NA 2 NIEZALEZNE
    float Hyman_symetryczna(int);///JEZELI MACIERZ SYMETRYCZNA TO MAMY MACIERZ TROJDIAGONALNA I INNY ALGORYTM OBLICZENIA DET
    Macierz odejmij_na_przekatnej(float);
public:
    Macierz();
    Macierz(int);
    Macierz(const Macierz&);///KONSTRUKTOR KOPIUJACY
    ~Macierz();
    void pobierz_macierz();
    void wyswietl_macierz(char option = 'p');///d - diagonal , n - normal , p - with precision
    float get_det(){wyznacznik();return det;}
    int get_rozmiar() const {return rozmiar;}
    float get_element_macierzy(int,int)const;
    void set_element_macierzy(int,int,float);///ZMIANA ELEMENTOW MACIERZY
    Macierz operator*(const Macierz&);
    float* operator*(float*);///MNOZENIE MACIERZY PRZEZ WEKTOR
    Macierz& operator=(const Macierz&);
    Macierz operator-();///MACIERZ ODWROTNA
    Macierz odwrotnaLU();///ZWRACA MACIERZ ODWRORNA, KTORA LICZY KORZYSTAJAC Z ROZKLADU LU
    Macierz operator*();///MACIERZ TRANSPONOWANA
    bool operator==(const Macierz&);///POROWNYWANIE MACIERZY
    Macierz eliminacja_Gaussa(int);///ROZKLAD LU 0-ZWRACA MACIERZ L, pozstale - zwraca U
    void rozwiaz_ukladLU(float*);///ROZWIAZANIE UKLADU KORZYSTAJAC Z ROZKLADU LU
    Macierz eliminacja_GaussaWEG();///ROZKLAD LU Z CZESCIOWYM WYBOREM ELEMENTU GLOWNEGO
    ///ZWRACA MACIERZ 0-1 KTORA MA 1 ZGODNE Z PERMUTACJA
    void rozwiaz_ukladLUzWEG(float*);///ROZWIAZANIE UKLADU KORZYSTAJAC Z ROZKLADU LU i WEG
    ///STOSUJEMY TU ROZKLAD LU DLA MACIERZY PA GDZIE P ZWRACA POWYZSZA METODA
    Macierz rozklad_HausholderaR();///ROZKLAD QR ZWRACA MACIERZ R
    Macierz rozklad_HausholderaQ();/// ZWRACA MACIERZ Q
    void Gram_Schmidt();///ROZKLAD QR METODA GRAMA-SCHMIDTA
    void rozwiaz_ukladQR(float*);///ROZWIAZANIE UKLADU KORZYSTAJAC Z ROZKLADU QR
    Macierz postac_Hessenberga();
    float algorytm_Hymana();///OBLICZNIE WYZNACZNIKA KORZYSTAJAC Z POSTACI HESSENBERGA
    void wyznacznikM();///WYPISUJE WYZNACZNIK OBLICZONY ROZNYMI SPOSOBAMI
    void ciag_Stuma();///PODAJE PRZEDZIAL W KTORYM ZNAJDUJE SIE PODANA WARTOSC WLASNA, DLA MACIERZY SYMETRYCZNYCH
    float ciag_Stuma(int);///ZWRACA PRZYBLIZONA WARTOSC WLASNA
    float lokalizacja_Gerszgorina(int);///PODAJE PRZEDZIAL W KTORYM ZNAJDUJA SIE WSZYSTKIE WARTOSCI WLASNE
    Macierz metodaQR();///ZNAJDOWANIE WSZYSTKICH WARTOSCI WLASNYCH MACIERZY
    void metoda_potegowa();///OBLICZA WEKTOR WLASNY DOMINUJACEJ WARTOSCI WLASNEJ DLA MAC SYMETRYCZNEJ Z DOMINUJACA WARTOSCIA WLASNA
    void metoda_Wielandta();///OBLICZA WEKTORY WLASNE DLA MACIERZY SYMETRYCZNEJ
    float norma_pierwsza();///MAKSIMUM PO KOLUMNACH
    float norma_nieskonczonosc();///MAKSIMUM PO WIERSZACH
    float norma_druga();///NAJWIEKSZA WARTOSC WLASNA MACIERZY AT*A
    float norma_frobeniusa();///SPIERWIASTKOWANA SUMA KWADRATOW WSZYSTKICH ELEMENTOW MACIERZY


};
