#ifndef MacierzProstokatna_h
#define MacierzProstokatna_h

#include <complex>

using namespace std;

class MacierzProstokatna
{
    int w,k;
protected:
    complex<double> **M;
    void ustaw_w(int w_){w=w_;}
    void ustaw_k(int k_){k=k_;}
public:
    MacierzProstokatna();
    MacierzProstokatna(int,int);
    MacierzProstokatna(const MacierzProstokatna&);///KONSTRUKTOR KOPIUJACY
    ~MacierzProstokatna();
    void wyswietl_macierz(char option = 'p',int precision = 3);///d - diagonal , n - normal , p - with precision
    void pobierz_macierz();
    int get_l_wierszy()const{return w;};
    int get_l_kolumn()const{return k;};
    complex<double> get_element_macierzy(int,int)const;
    void set_element_macierzy(int,int,complex<double>);///ZMIANA ELEMENTOW MACIERZY
    MacierzProstokatna operator*(const MacierzProstokatna&);///MNOZENIE MACIERZY
    complex<double>* operator*(complex<double>*);///MNOZENIE MACIERZY PRZEZ WEKTOR
    MacierzProstokatna& operator=(const MacierzProstokatna&);///OPERATOR PRZYPISANIA
    MacierzProstokatna operator~();///MACIERZ TRANSPONOWANA
    bool operator==(const MacierzProstokatna&);///POROWNYWANIE MACIERZY
    float norma_pierwsza();///MAKSIMUM PO KOLUMNACH
    float norma_nieskonczonosc();///MAKSIMUM PO WIERSZACH
    float norma_druga();///NAJWIEKSZA WARTOSC WLASNA MACIERZY AT*A
    float norma_frobeniusa();///SPIERWIASTKOWANA SUMA KWADRATOW WSZYSTKICH ELEMENTOW MACIERZY
};

#endif // MacierzProstokatna_h
