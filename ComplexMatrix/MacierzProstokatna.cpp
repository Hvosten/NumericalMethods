#include "MacierzProstokatna.h"
#include "MacierzKwadratowa.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);

MacierzProstokatna::MacierzProstokatna()
{
    w = k = 0;
    M = NULL;
}

MacierzProstokatna::MacierzProstokatna(int l_wierszy,int l_kolumn)
{
    w = l_wierszy;
    k = l_kolumn;

    M = new complex<double> *[w];
    for(int i = 0 ; i < w ; ++i)
    {
        M[i] = new complex<double> [k];

        for(int j = 0 ; j < k ; ++j)
        {
            M[i][j].real(0);
            M[i][j].imag(0);
        }
    }
}

MacierzProstokatna::MacierzProstokatna(const MacierzProstokatna& A)
{
    w = A.get_l_wierszy();
    k = A.get_l_kolumn();
    M = new complex<double> *[w];
    for(int i = 0 ; i < w ; ++i)
    {
        M[i] = new complex<double> [k];

        for(int j = 0 ; j < k ; ++j)
           M[i][j] = A.get_element_macierzy(i,j);
    }
}

MacierzProstokatna::~MacierzProstokatna()
{
    for(int i = 0 ; i < k ; ++i)
        delete [] M[i];
    delete [] M;
}

complex<double> MacierzProstokatna::get_element_macierzy(int i,int j)const
{
    if(i < w || j < k)
        return M[i][j];
    return 0;
}

void MacierzProstokatna::set_element_macierzy(int i,int j,complex<double> e)
{
    if(i < w && j < k)
        M[i][j] = e;
}

void MacierzProstokatna::wyswietl_macierz(char option,int precision)
{
    ///WYPISYWANIE TABLICY
    cout<<endl;

    if(option == 'p')
        for(int i = 0 ; i < w ; ++i , cout<<endl)
            for(int j = 0 ; j < k ; ++j)
            {
                cout<<fixed<<setw( 2*precision+9 )<<setprecision( precision );
                if(!M[i][j].imag())
                    cout<<M[i][j].real()<<" ";
                else
                    cout<<M[i][j]<<" ";
            }

    if(option == 'd')
        for(int i = 0 ; i < w ; ++i , cout<<endl)
            for(int j = 0 ; j < k ; ++j)
            {
                if(i == j)
                {
                    SetConsoleTextAttribute(uchwyt,10);
                    cout<<fixed<<setw( 2*precision+9 )<<setprecision( precision )<<M[i][j]<<" ";
                    SetConsoleTextAttribute(uchwyt,15);
                }
                else
                    cout<<fixed<<setw( 2*precision+9 )<<setprecision( precision )<<M[i][j]<<" ";
            }

    if(option == 'n')
        for(int i = 0 ; i < w ; ++i , cout<<endl)
            for(int j = 0 ; j < k ; ++j)
            {
                cout.width( 2*precision+9 );
                cout<<right<<M[i][j];
            }

    cout<<endl;
}

void MacierzProstokatna::pobierz_macierz()
{
    for(int i = 0 ; i < k ; ++i)
        delete [] M[i];
    delete [] M;


    cout << "Podaj rozmiary macierzy(wiersz, kolumna): " << endl;
    cin >> w >> k;

    M = new complex<double> *[w];
    for(int i = 0 ; i < w ; ++i)
    {
        M[i] = new complex<double> [k];

        for(int j = 0 ; j < k ; ++j)
            M[i][j] = 0;
    }

    cout << "Podaj elemnty macierzy wierszami(najpierw czesc rzeczywista, potem zespolona): " << endl;

    for(int i = 0 ; i < w ; ++i)
        for(int j = 0 ; j < k ; ++j)
            cin>>M[i][j].real()>>M[i][j].imag();
}

MacierzProstokatna MacierzProstokatna::operator*(const MacierzProstokatna& B)
{
    if( k != B.get_l_wierszy())
    {
        cout<<"Nie mozna mnozyc tych macierzy!"<<endl;
        return *this;
    }
    MacierzProstokatna C(w,B.get_l_kolumn());

    complex<double> pom;

    for(int i = 0 ; i < w ; ++i)
        for(int j = 0 ; j < B.get_l_kolumn() ; ++j)
        {
            pom = 0;
            for(int s = 0 ; s < k ; ++s)
                pom += get_element_macierzy(i,s)*B.get_element_macierzy(s,j);
            C.set_element_macierzy(i,j,pom);
        }

    return C;
}

complex<double>* MacierzProstokatna::operator*(complex<double> *x)
{
    complex<double> *y = new complex<double>[w];
    for(int i = 0 ; i < w ; ++i)
    {
        y[i] = 0;
        for(int j = 0 ; j < k ; ++j)
            y[i] += M[i][j]*x[j];
    }
    return y;
}

MacierzProstokatna&  MacierzProstokatna::operator=(const MacierzProstokatna& A)
{
    ///NISZCZENIE ZAWARTOSCI
    for(int i = 0 ; i < k ; ++i)
        delete [] M[i];
    delete [] M;

    ///ALOKOWANIE NOWEJ I KOPIOWANIE
    w = A.get_l_wierszy();
    k = A.get_l_kolumn();
    M = new complex<double> *[w];
    for(int i = 0 ; i < w ; ++i)
    {
        M[i] = new complex<double> [k];

        for(int j = 0 ; j < k ; ++j)
            M[i][j] = A.get_element_macierzy(i,j);
    }
    return *this;
}

MacierzProstokatna MacierzProstokatna::operator~()
{
    MacierzProstokatna T(k,w);
    for(int i = 0 ; i < k ; ++i)
        for(int j = 0 ; j < w ; ++j)
            T.set_element_macierzy(i,j,conj(M[j][i]));
    return T;
}

bool MacierzProstokatna::operator==(const MacierzProstokatna& A)
{
   if(w != A.get_l_wierszy() || k != A.get_l_kolumn())
        return false;

   for(int i = 0 ; i < w ; ++i)
        for(int j = 0 ; j < k ; ++j)
            if(M[i][j] != A.get_element_macierzy(i,j))
                return false;
   return true;
}

float MacierzProstokatna::norma_pierwsza()
{
    float maks = 0 , pom;

    for(int i  = 0 ; i < k ; ++i)
    {
        pom = 0;
        for(int j = 0 ; j < w ; ++j)
            pom += abs(M[j][i]);

        if(pom > maks)
            maks = pom;
    }
    return maks;
}

float MacierzProstokatna::norma_nieskonczonosc()
{
    float maks = 0 , pom;

    for(int i  = 0 ; i < w ; ++i)
    {
        pom = 0;
        for(int j = 0 ; j < k ; ++j)
            pom += abs(M[i][j]);

        if(pom > maks)
            maks = pom;
    }
    return maks;
}

float MacierzProstokatna::norma_druga()
{
    MacierzProstokatna B = ((~(*this))*(*this));
    MacierzKwadratowa A,P;
    A = B;
    P = A.metodaQR();
    float maks = 0;
    for(int i = 0 ; i < w ; ++i)
        if(abs(P.get_element_macierzy(i,i)) > maks)
            maks = abs(P.get_element_macierzy(i,i));

    return sqrt(maks);
}

float MacierzProstokatna::norma_frobeniusa()
{
    float pom = 0;
    for(int i = 0 ; i < w ; ++i)
        for(int j = 0 ; j < k ; ++j)
            pom += pow(abs(M[i][j]),2);

    return sqrt(pom);
}

