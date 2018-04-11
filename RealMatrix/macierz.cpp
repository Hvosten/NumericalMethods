#include <iostream>
#include "macierz.h"
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <windows.h>



using namespace std;
extern HANDLE uchwyt;

Macierz::Macierz()
{
    rozmiar = 0;
    M = NULL;
}
Macierz::Macierz(int n)
{
    rozmiar = n;

    M = new float *[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        M[i] = new float [rozmiar];

        for(int j = 0 ; j < rozmiar ; ++j)
            M[i][j] = 0;
    }
}

Macierz::Macierz(const Macierz& A)
{
    rozmiar = A.get_rozmiar();
    M = new float *[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        M[i] = new float [rozmiar];

        for(int j = 0 ; j < rozmiar ; ++j)
            M[i][j] = A.get_element_macierzy(i,j);
    }
}

Macierz::~Macierz()
{
    for(int i = 0 ; i < rozmiar ; ++i)
        delete [] M[i];
    delete [] M;
}

void Macierz::wyswietl_macierz(char option)
{
    ///WYPISYWANIE TABLICY
    cout<<endl;

    if(option == 'p')
        for(int i = 0 ; i < rozmiar ; ++i , cout<<endl)
            for(int j = 0 ; j < rozmiar ; ++j)
                cout<<fixed<<setw( 12 )<<setprecision( 5 )<<M[i][j]<<" ";

    if(option == 'd')
        for(int i = 0 ; i < rozmiar ; ++i , cout<<endl)
            for(int j = 0 ; j < rozmiar ; ++j)
            {
                if(i == j)
                {
                    SetConsoleTextAttribute(uchwyt,10);
                    cout<<fixed<<setw( 12 )<<setprecision( 5 )<<M[i][j]<<" ";
                    SetConsoleTextAttribute(uchwyt,15);
                }
                else
                    cout<<fixed<<setw( 12 )<<setprecision( 5 )<<M[i][j]<<" ";
            }

    if(option == 'n')
        for(int i = 0 ; i < rozmiar ; ++i , cout<<endl)
            for(int j = 0 ; j < rozmiar ; ++j)
            {
                cout.width( 14 );
                cout<<right<<M[i][j];
            }

    cout<<endl;
}

void Macierz::pobierz_macierz()
{
    cout << "Podaj rozmiar macierzy: " << endl;
    cin >> rozmiar;

    M = new float *[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        M[i] = new float [rozmiar];

        for(int j = 0 ; j < rozmiar ; ++j)
            M[i][j] = 0;
    }

    cout << "Podaj elemnty macierzy wierszami: " << endl;

    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            cin>>M[i][j];
}

int Macierz::znak_permutacji(int *perm)
{
    int l_inwersji = 0;
    for(int i = 1 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < i ; ++j)
            if(perm[j] > perm[i])
                ++l_inwersji;
    if(l_inwersji % 2)
        return -1;
    else
        return 1;
}

void Macierz::permutacja(int m,int *perm,int *wolny)
{
    for(int i = 0 ; i < rozmiar ; ++i)
        if(wolny[i] == 1)
        {
            perm[m] = i;
            wolny[i] = 0;
            if(m < rozmiar-1)
                permutacja(m+1,perm,wolny);
            else
            {
                float czynnik = 1;
                for(int j = 0 ; j < rozmiar ; ++j)
                    czynnik *= M[j][perm[j]];
                det += znak_permutacji(perm)*czynnik;
            }
            wolny[i] = 1;
        }
}

void Macierz::wyznacznik()
{
    int *wolny = new int [rozmiar];
    int *perm = new int [rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
        wolny[i] = 1;
    det = 0;
    permutacja(0,perm,wolny);

    delete [] wolny;
    delete [] perm;
}

float Macierz::get_element_macierzy(int i,int j)const
{
    if(i < rozmiar || j < rozmiar)
        return M[i][j];
    return 0;
}

void Macierz::set_element_macierzy(int i,int j,float e)
{
    if(i < rozmiar && j < rozmiar)
        M[i][j] = e;
}

Macierz Macierz::operator*(const Macierz& B)
{
    Macierz C(rozmiar);
    if(rozmiar == B.rozmiar)
    {
        float pom;

        for(int i = 0 ; i < rozmiar ; ++i)
            for(int j = 0 ; j < rozmiar ; ++j)
            {
                pom = 0;
                for(int s = 0 ; s < rozmiar ; ++s)
                    pom += get_element_macierzy(i,s)*B.get_element_macierzy(s,j);
                C.set_element_macierzy(i,j,pom);
            }
    }
    return C;
}

float* Macierz::operator*(float *x)
{
    float *y = new float[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        y[i] = 0;
        for(int j = 0 ; j < rozmiar ; ++j)
            y[i] += M[i][j]*x[j];
    }
    return y;
}

Macierz&  Macierz::operator=(const Macierz& A)
{
    ///NISZCZENIE ZAWARTOSCI
    for(int i = 0 ; i < rozmiar ; ++i)
        delete [] M[i];
    delete [] M;

    ///ALOKOWANIE NOWEJ I KOPIOWANIE
    rozmiar = A.get_rozmiar();
    M = new float *[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        M[i] = new float [rozmiar];

        for(int j = 0 ; j < rozmiar ; ++j)
            M[i][j] = A.get_element_macierzy(i,j);
    }
    return *this;
}

float Macierz::dopelnienie_algebraiczne(int m,int n)
{
    Macierz D(rozmiar-1);
    int miejsce = 0, rzad = -1;
    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
        {
            if(i != m && j != n)
            {
                if(!miejsce)
                    ++rzad;
                D.set_element_macierzy(rzad,miejsce,M[i][j]);
                miejsce = (miejsce+1)%(rozmiar-1);
            }
        }

    float w = D.get_det();
    return ((n+m)%2 ? -w : w);
}

Macierz Macierz::operator-()
{
    Macierz O(rozmiar);
    if(this->get_det())
    {
        for(int i = 0 ; i < rozmiar ; ++i)
            for(int j = 0 ; j < rozmiar ; ++j)
                O.set_element_macierzy(i,j,1/det*dopelnienie_algebraiczne(j,i));
    }
    else
    {
        cout<<"Macierz odwrotna nie istnieje!"<<endl;
        system("pause");
    }
    return O;
}

Macierz Macierz::operator*()
{
    Macierz T(rozmiar);
    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            T.set_element_macierzy(i,j,M[j][i]);
    return T;
}

bool Macierz::operator==(const Macierz& A)
{
   if(rozmiar != A.get_rozmiar())
        return false;

   for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            if(M[i][j] != A.get_element_macierzy(i,j))
                return false;
   return true;
}

void Macierz::subtract_to_element_macierzy(int i,int j,float l)
{
    if(i < rozmiar && j < rozmiar)
        M[i][j] -= l;
}

Macierz Macierz::eliminacja_Gaussa(int co_zwracamy)
{
    Macierz L(rozmiar),U(*this);
    if(!get_det())
    {
        cout<<"Macierz jest osobliwa!"<<endl;
        return U;
    }

    for(int i = 0 ; i < rozmiar ; ++i)
        L.set_element_macierzy(i,i,1);///MACIERZ L MA NA PRZEKATNEJ ZAWSZE 1

    for(int k = 0 ; k < rozmiar ; ++k)
        for(int i = k+1 ; i < rozmiar ; ++i)
        {
            if(!U.get_element_macierzy(k,k))
            {
                cout<<"Potrzebny wybor elementu glownego!"<<endl;
                return U;
            }
            L.set_element_macierzy(i,k,U.get_element_macierzy(i,k)/U.get_element_macierzy(k,k));
            U.set_element_macierzy(i,k,0);
            for(int j = k+1 ; j < rozmiar ; ++j)
                U.subtract_to_element_macierzy(i,j,L.get_element_macierzy(i,k)*U.get_element_macierzy(k,j));
        }
        if(co_zwracamy)
            return U;
        return L;

}

void Macierz::zamien_wiersze_macierzy(int k, int l)
{
    float pom;
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        pom = M[k][i];
        M[k][i] = M[l][i];
        M[l][i] = pom;
    }
}

int Macierz::zwroc_wiersz(int k)
{
    float maks = fabs(M[k][k]);
    int numer = k;
    for(int i = k+1 ; i < rozmiar ; ++i)
    {
        if(fabs(M[i][k]) > maks)
        {
            maks = fabs(M[i][k]);
            numer = i;
        }
    }
    return numer;
}

Macierz Macierz::eliminacja_GaussaWEG()
{
    Macierz L(rozmiar),U(*this);
    float *p = new float[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
        p[i] = i;

    if(!get_det())
    {
        cout<<"Macierz jest osobliwa!"<<endl;
        return U;
    }

    for(int i = 0 ; i < rozmiar ; ++i)
        L.set_element_macierzy(i,i,1);///MACIERZ L MA NA PRZEKATNEJ ZAWSZE 1

    int pom;
    for(int k = 0 ; k < rozmiar ; ++k)
        for(int i = k+1 ; i < rozmiar ; ++i)
        {
            pom = U.zwroc_wiersz(k);
            if(pom != k)
            {
                U.zamien_wiersze_macierzy(k,pom);
                int pom2 = p[k];
                p[k] = p[pom];
                p[pom] = pom2;
            }
            L.set_element_macierzy(i,k,U.get_element_macierzy(i,k)/U.get_element_macierzy(k,k));
            U.set_element_macierzy(i,k,0);
            for(int j = k+1 ; j < rozmiar ; ++j)
                U.subtract_to_element_macierzy(i,j,L.get_element_macierzy(i,k)*U.get_element_macierzy(k,j));
        }

    Macierz P(rozmiar);
    for(int i = 0 ; i < rozmiar ; ++i)
        P.set_element_macierzy(i,p[i],1);
    delete [] p;
    return P;
}

float Macierz::Knorma2_wektora(int i,int k)
{
    float l = 0;
    for(int j = i ; j < rozmiar ; ++j)
        l += pow(get_element_macierzy(j,k),2);
    return l;
}

Macierz Macierz::rozklad_HausholderaR()
{
    Macierz R(*this);
    float *u = new float[rozmiar];
    float v;
    float r;

    for(int i = 0 ; i < rozmiar-1 ; ++i)
    {
        int znak = (R.get_element_macierzy(i,i) > 0 ? 1 : -1);///ODPOWIEDNI WYBOR ZNAKU
        u[i] = R.get_element_macierzy(i,i)+znak*sqrt(R.Knorma2_wektora(i,i));
        for(int j = i+1 ; j < rozmiar ; ++j)
            u[j] = R.get_element_macierzy(j,i);
        r = R.Knorma2_wektora(i,i)+znak*R.get_element_macierzy(i,i)*sqrt(R.Knorma2_wektora(i,i));


        for(int n = i ; n < rozmiar ; ++n)///kolumna
        {
            v = 0;
            for(int j = i ; j < rozmiar ; ++j)
                v += u[j]*R.get_element_macierzy(j,n);
            v /= r;
            for(int m = i ; m < rozmiar ; ++m)
                R.subtract_to_element_macierzy(m,n,u[m]*v);
        }
    }
    delete [] u;
    return R;
}

void Macierz::zamien_na_jednostkowa()
{
    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            if(i == j)
                M[i][j] = 1;
            else
                M[i][j] = 0;
}

Macierz Macierz::rozklad_HausholderaQ()
{
    Macierz R(*this);
    Macierz Q(rozmiar);
    Q.zamien_na_jednostkowa();
    Macierz P(rozmiar);
    float *u = new float[rozmiar];
    float r;

    for(int i = 0 ; i < rozmiar-1 ; ++i)
    {
        int znak = (R.get_element_macierzy(i,i) > 0 ? 1 : -1);///ODPOWIEDNI WYBOR ZNAKU
        u[i] = R.get_element_macierzy(i,i)+znak*sqrt(R.Knorma2_wektora(i,i));
        for(int j = i+1 ; j < rozmiar ; ++j)
            u[j] = R.get_element_macierzy(j,i);
        r = R.Knorma2_wektora(i,i)+znak*R.get_element_macierzy(i,i)*sqrt(R.Knorma2_wektora(i,i));

        P.zamien_na_jednostkowa();
        for(int j = i ; j < rozmiar ; ++j)
            for(int k = i ; k < rozmiar ; ++k)
                P.subtract_to_element_macierzy(j,k,u[j]*u[k]/r);
        Q = Q*P;
        R = P*R;
        u[i] = 0;
    }
    delete [] u;
    return Q;
}

void Macierz::rozwiaz_ukladLU(float *b)
{
    if(!get_det())
    {
        cout<<"Wyznacznik macierzy wynosi 0!"<<endl;
        return;
    }
    float *y = new float[rozmiar];
    float *x = new float[rozmiar];
    Macierz L = eliminacja_Gaussa(0);
    Macierz U = eliminacja_Gaussa(1);

    for(int i = 0 ; i < rozmiar ; ++i)
    {
        y[i] = b[i];
        for(int j = 0 ; j < i ; ++j)
            y[i] -= L.get_element_macierzy(i,j)*y[j];
        y[i] /= L.get_element_macierzy(i,i);
    }

    for(int i = rozmiar-1 ; i >= 0 ; --i)
    {
        x[i] = y[i];
        for(int j = rozmiar-1 ; j > i  ; --j)
            x[i] -= U.get_element_macierzy(i,j)*x[j];
        x[i] /= U.get_element_macierzy(i,i);
    }

    cout<<"Rozwiazanie przy pomocy rozkladu LU:"<<endl;
    for(int i = 0 ; i < rozmiar ; ++i)
        cout<<x[i]<<" ";
    cout<<endl;
    delete [] y;
    delete [] x;
}

void Macierz::rozwiaz_ukladLUzWEG(float *b)
{
    if(!get_det())
    {
        cout<<"Wyznacznik macierzy wynosi 0!"<<endl;
        return;
    }
    float *y = new float[rozmiar];
    float *x = new float[rozmiar];

    Macierz P = eliminacja_GaussaWEG();
    Macierz A = P*(*this);
    Macierz L = A.eliminacja_Gaussa(0);
    Macierz U = A.eliminacja_Gaussa(1);
    b = P*b;
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        y[i] = b[i];
        for(int j = 0 ; j < i ; ++j)
            y[i] -= L.get_element_macierzy(i,j)*y[j];
        y[i] /= L.get_element_macierzy(i,i);
    }

    for(int i = rozmiar-1 ; i >= 0 ; --i)
    {
        x[i] = y[i];
        for(int j = rozmiar-1 ; j > i  ; --j)
            x[i] -= U.get_element_macierzy(i,j)*x[j];
        x[i] /= U.get_element_macierzy(i,i);
    }

    cout<<"Rozwiazanie przy pomocy rozkladu LU z WEG:"<<endl;
    for(int i = 0 ; i < rozmiar ; ++i)
        cout<<x[i]<<" ";
    cout<<endl;
    delete [] y;
    delete [] x;
}

Macierz Macierz::odwrotnaLU()
{
    if(!get_det())
    {
        cout<<"Macierz osobliwa!"<<endl;
        return *this;
    }
    Macierz P = (*this).eliminacja_GaussaWEG();
    Macierz A = P*(*this);
    Macierz L = A.eliminacja_Gaussa(0);
    Macierz U = A.eliminacja_Gaussa(1);
    Macierz O(rozmiar);

    float *b = new float[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
        b[i] = 0;

    float *x = new float[rozmiar];
    float *y = new float[rozmiar];

    for(int k = 0 ; k < rozmiar ; ++k)
    {
        b[k] = 1;
        b = P*b;
        for(int i = 0 ; i < rozmiar ; ++i)
        {
            y[i] = b[i];
            for(int j = 0 ; j < i ; ++j)
                y[i] -= L.get_element_macierzy(i,j)*y[j];
            y[i] /= L.get_element_macierzy(i,i);
        }

        for(int i = rozmiar-1 ; i >= 0 ; --i)
        {
            x[i] = y[i];
            for(int j = rozmiar-1 ; j > i  ; --j)
                x[i] -= U.get_element_macierzy(i,j)*x[j];
            x[i] /= U.get_element_macierzy(i,i);
        }
        for(int j = 0 ; j < rozmiar ; ++j)
        {
            O.set_element_macierzy(j,k,x[j]);
            b[j] = 0;
        }
    }

    delete [] b;
    delete [] x;
    delete [] y;
    return O;
}

void Macierz::rozwiaz_ukladQR(float *b)///Ax=b ; QRx=b ; Qy=b ; Rx=y
{
    float *y = new float[rozmiar];
    float *x = new float[rozmiar];
    Macierz Q = rozklad_HausholderaQ();
    y = (*Q)*b;
    Macierz R = rozklad_HausholderaR();

    for(int i = rozmiar-1 ; i >= 0 ; --i)
    {
        x[i] = y[i];
        for(int j = rozmiar-1 ; j > i  ; --j)
            x[i] -= R.get_element_macierzy(i,j)*x[j];
        x[i] /= R.get_element_macierzy(i,i);
    }

    cout<<"Rozwiazanie przy pomocy rozkladu QR:"<<endl;
    for(int i = 0 ; i < rozmiar ; ++i)
        cout<<x[i]<<" ";
    cout<<endl;
    delete [] y;
    delete [] x;
}


Macierz Macierz::postac_Hessenberga()
{
    Macierz A(*this);
    Macierz P(rozmiar);
    float *u = new float[rozmiar];
    float r;
    u[0] = 0;

    for(int i = 0 ; i < rozmiar-2 ; ++i)
    {
        int znak = (A.get_element_macierzy(i+1,i) > 0 ? 1 : -1);///ODPOWIEDNI WYBOR ZNAKU
        u[i+1] = A.get_element_macierzy(i+1,i)+znak*sqrt(A.Knorma2_wektora(i+1,i));
        for(int j = i+2 ; j < rozmiar ; ++j)
            u[j] = A.get_element_macierzy(j,i);
        r = A.Knorma2_wektora(i+1,i)+znak*A.get_element_macierzy(i+1,i)*sqrt(A.Knorma2_wektora(i+1,i));
        if(r)
        {
            P.zamien_na_jednostkowa();
            for(int j = i+1 ; j < rozmiar ; ++j)
                for(int k = i+1 ; k < rozmiar ; ++k)
                    P.subtract_to_element_macierzy(j,k,u[j]*u[k]/r);
            A=P*A;
            A=A*P;
        }
        u[i] = 0;
    }
    delete [] u;
    return A;
}

float Macierz::algorytm_Hymana()///MOZE BYC PRZYPADEK ZE TRZEBA ROZBIC NA PODZADANIA
{
    /*float *x = new float [rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
        x[i] = 0;

    x[0] = 1;
    for(int i = 1 ; i < rozmiar ; ++i)
    {
        for(int j = 0 ; j < i ; ++j)
            x[i] += x[j]*M[j][i-1];
        x[i] /= -M[i][i-1];
    }

    float pom = M[0][rozmiar-1] , w = 1;
    for(int i = 1 ; i < rozmiar ; ++i)
    {
        pom += x[i]*M[i][rozmiar-1];
        w *= M[i][i-1];
    }
    w *= pom;
    delete [] x;

    return ((rozmiar+1)%2) ? -w : w;*/
    float w=1;
    if((*this) == (*(*this)))
        w = Hyman_symetryczna(rozmiar-1);
    else
    {
        int p = 0;
        for(int i = 0 ; i < rozmiar-2 ; ++i)
        {
            if(!M[i+1][i])
            {
                w *= Hyman_podzadanie(p,i+1-p);
                p = i+1;
            }
        }
        w *= Hyman_podzadanie(p,rozmiar-p);
    }
    return w;
}

float Macierz::Hyman_podzadanie(int p,int d)///(poczatek,wielkosc macierzy)
{
    float *x = new float[d];
    for(int i = 0 ; i < d ; ++i)
        x[i] = 0;

    x[0] = 1;
    for(int i = 1 ; i < d ; ++i)
    {
        for(int j = 0 ; j < i ; ++j)
            x[i] += x[j]*M[p+j][p+i-1];
        x[i] /= -M[p+i][p+i-1];
    }

    float pom = M[p][p+d-1] , w = 1;
    for(int i = 1 ; i < d ; ++i)
    {
        pom += x[i]*M[p+i][p+d-1];
        w *= M[p+i][p+i-1];
    }
    w *= pom;
    delete [] x;

    return ((d+1)%2) ? -w : w;
}

float Macierz::Hyman_symetryczna(int i)
{
    if(i == -1)
        return 1;
    if(i == 0)
        return M[0][0];
    return M[i][i]*Hyman_symetryczna(i-1)-pow(M[i-1][i],2)*Hyman_symetryczna(i-2);
}

void Macierz::wyznacznikM()
{
    float detLU=1,detQR=1;
    int *p = new int[rozmiar];
    Macierz P = (*this).eliminacja_GaussaWEG();
    for(int i = 0 ; i < rozmiar ; ++i)///ODTWARZAMY PERMUTACJE ZEBY OBLICZYC ZNAK PRZY WYZNACZNIKU
        for(int j = 0 ; j < rozmiar ; ++j)
            if(P.get_element_macierzy(i,j))
            {
                p[i] = j;
                break;
            }

    Macierz U = (P*(*this)).eliminacja_Gaussa(1);
    Macierz R = (*this).rozklad_HausholderaR();
    Macierz Q = (*this).rozklad_HausholderaQ();
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        detLU *= U.get_element_macierzy(i,i);
        detQR *= R.get_element_macierzy(i,i);
    }
    detLU *= znak_permutacji(p);
    detQR *= (Q.get_det()>0) ? 1 : -1;///WYZNACZNIK MACIERZY ORTOGONALNEJ TO 1 LUB -1

    cout<<"Wyznacznik macierzy wynosi:"<<endl;
    cout<<"korzystajac z definicji: "<<get_det()<<endl;
    cout<<"korzystajac z rozkladu LU: "<<detLU<<endl;
    cout<<"korzystajac z rozkladu QR: "<<detQR<<endl;
    cout<<"korzystajac z macierzy Hessenberga: "<<((*this).postac_Hessenberga()).algorytm_Hymana()<<endl;
}

Macierz Macierz::odejmij_na_przekatnej(float lambda)
{
    Macierz A(*this);
    for(int i = 0 ; i < rozmiar ; ++i)
        A.subtract_to_element_macierzy(i,i,lambda);
    return A;
}

void Macierz::ciag_Stuma()
{
    if(((*this) == (*(*this))) == false)///MACIERZ NIE JEST SYMETRYCZNA
    {
        cout<<"Ten algorytm dziala poprawnie tylko dla macierzy symetrycznych!"<<endl;
        cout<<"Dana macierz nie jest symetryczna!"<<endl;
        return;
    }
    int s,poprz_s = rozmiar;
    Macierz A = (*this).postac_Hessenberga();
    float a = (*this).lokalizacja_Gerszgorina(0),b=(*this).lokalizacja_Gerszgorina(1);
    float krok = 0.5, pom, c = a;
    do
    {
        s = 0;
        for(int i = 0 ; i < rozmiar ; ++i)
        {
            Macierz P = A.odejmij_na_przekatnej(c);
            pom = P.Hyman_symetryczna(i-1)*P.Hyman_symetryczna(i);
            if(pom >= 0)
                ++s;
        }
        if(s < poprz_s)
        {
            cout<<rozmiar-s<<" wartosc wlasna znajduje sie w przedziale ["<<c-krok<<" ; "<<c<<"]"<<endl;
            poprz_s = s;
        }
        c += krok;
    }
    while(c < b && s != 0);
}

float Macierz::ciag_Stuma(int ktora)
{
    if(ktora > rozmiar)
        return 0;

    int s,poprz_s = rozmiar;
    Macierz A = (*this).postac_Hessenberga();
    float a = (*this).lokalizacja_Gerszgorina(0),b=(*this).lokalizacja_Gerszgorina(1);
    float krok = 0.05, pom, c = a;
    do
    {
        s = 0;
        for(int i = 0 ; i < rozmiar ; ++i)
        {
            Macierz P = A.odejmij_na_przekatnej(c);
            pom = P.Hyman_symetryczna(i-1)*P.Hyman_symetryczna(i);
            if(pom >= 0)
                ++s;
        }
        if(s < poprz_s)
        {
            if(rozmiar-s == ktora)
                return (c-krok+c)/2;
            poprz_s = s;
        }
        c += krok;
    }
    while(c < b && s != 0);
    return 0;
}

float Macierz::lokalizacja_Gerszgorina(int w)///KTORY KRANIEC ZWROCIC 0 lewy , 1 prawy
{
    float lewy,prawy,promien;
    float srodek;
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        promien = 0;
        srodek = M[i][i];
        for(int j = 0 ; j < rozmiar ; ++j)
            if(j != i)
                promien += fabs(M[i][j]);

        if(i == 0)
        {
            lewy = srodek - promien;
            prawy = srodek + promien;
        }
        else
        {
            if(lewy > srodek - promien)
                lewy = srodek - promien;
            if(prawy < srodek + promien)
                prawy = srodek + promien;
        }
    }
    if(!w)
        return lewy;
    else
        return prawy;

}

Macierz Macierz::metodaQR()
{
    Macierz P = (*this).postac_Hessenberga();///SPROWADZENIE DO POSTACI HESSENBERGA PRZYSPIESZA PROCES
    Macierz Q = P.rozklad_HausholderaQ();
    Macierz R = P.rozklad_HausholderaR();
    P = R*Q;
    for(int i = 1 ; i < 100 ; ++i)
    {
        Q = P.rozklad_HausholderaQ();
        R = P.rozklad_HausholderaR();
        P = R*Q;
    }
    return P;
}

void Macierz::metoda_potegowa()
{
    if(((*this) == (*(*this))) == false)///MACIERZ NIE JEST SYMETRYCZNA
    {
        cout<<"Ta metoda dziala poprawnie tylko dla macierzy symetrycznych z dominujaca wartoscia wlasna!"<<endl;
        return;
    }
    float *z = new float[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)///NORMA WEKTORA POCZATKOWEGO MUSI WYNOSIC 1
        z[i] = 1/sqrt(rozmiar);

    float *y = new float[rozmiar];
    float pom;

    for(int i = 0 ; i < 100 ; ++i)
    {
        z = (*this)*z;
        pom = 0;
        for(int i = 0 ; i < rozmiar ; ++i)
            pom += pow(z[i],2);
        pom = sqrt(pom);
        for(int i = 0 ; i < rozmiar ; ++i)
            z[i] /= pom;
    }

    y = (*this)*z;
    pom = 0;
    for(int i = 0 ; i < rozmiar ; ++i)
        pom += y[i]*z[i];///CIAG RAYLEIGHA

    cout<<"Wektor wlasny dominujacej wartosci wlasnej "<<pom<<" wynosi: "<<endl;
    for(int i = 0 ; i < rozmiar ; ++i)
        cout<<z[i]<<" ";
    cout<<endl;

    delete [] z;
    delete [] y;

}

void Macierz::metoda_Wielandta()
{
    if(((*this) == (*(*this))) == false)///MACIERZ NIE JEST SYMETRYCZNA
    {
        cout<<"Ta metoda dziala poprawnie tylko dla macierzy symetrycznych z dominujaca wartoscia wlasna!"<<endl;
        return;
    }
    float *z = new float[rozmiar];
    for(int i = 1 ; i <= rozmiar ; ++i)
    {
        float lambda = (*this).ciag_Stuma(i);
        Macierz A = ((*this).odejmij_na_przekatnej(lambda)).odwrotnaLU();


        for(int i = 0 ; i < rozmiar ; ++i)///NORMA WEKTORA POCZATKOWEGO MUSI WYNOSIC 1
            z[i] = 1/sqrt(rozmiar);


        float pom;

        for(int i = 0 ; i < 2 ; ++i)
        {
            z = A*z;
            pom = 0;
            for(int i = 0 ; i < rozmiar ; ++i)
                pom += pow(z[i],2);
            pom = sqrt(pom);
            for(int i = 0 ; i < rozmiar ; ++i)
                z[i] /= pom;
        }

        cout<<"Wektor wlasny wartosci wlasnej "<<lambda<<" wynosi: "<<endl;
        for(int i = 0 ; i < rozmiar ; ++i)
            cout<<z[i]<<" ";
        cout<<endl;
        cout<<endl;

    }
    delete [] z;
}


float Macierz::norma_pierwsza()
{
    float maks = 0 , pom;

    for(int i  = 0 ; i < rozmiar ; ++i)
    {
        pom = 0;
        for(int j = 0 ; j < rozmiar ; ++j)
            pom += fabs(M[j][i]);

        if(pom > maks)
            maks = pom;
    }
    return maks;
}

float Macierz::norma_nieskonczonosc()
{
    float maks = 0 , pom;

    for(int i  = 0 ; i < rozmiar ; ++i)
    {
        pom = 0;
        for(int j = 0 ; j < rozmiar ; ++j)
            pom += fabs(M[i][j]);

        if(pom > maks)
            maks = pom;
    }
    return maks;
}

float Macierz::norma_druga()
{
    Macierz A = ((*(*this))*(*this)).metodaQR();
    float maks = 0;
    for(int i = 0 ; i < rozmiar ; ++i)
        if(A.get_element_macierzy(i,i) > maks)
            maks = A.get_element_macierzy(i,i);

    return sqrt(maks);
}

float Macierz::norma_frobeniusa()
{
    float pom = 0;
    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            pom += pow(M[i][j],2);

    return sqrt(pom);
}

void Macierz::Gram_Schmidt()
{
    Macierz Q(*this);
    Macierz R(rozmiar);

    for(int i = 0 ; i < rozmiar ; ++i)
    {
        for(int j = 0 ; j < i ; ++j)
            for(int k = 0 ; k < rozmiar ; ++k)
                R.subtract_to_element_macierzy(j,i,-M[k][i]*Q.get_element_macierzy(k,j));

        for(int k = 0 ; k < rozmiar ; ++k)
            for(int j = 0 ; j < i ; ++j)
                Q.subtract_to_element_macierzy(k,i,R.get_element_macierzy(j,i)*Q.get_element_macierzy(k,j));

        for(int k = 0 ; k < rozmiar ; ++k)
            R.subtract_to_element_macierzy(i,i,-pow(Q.get_element_macierzy(k,i),2));
        R.set_element_macierzy(i,i,sqrt(R.get_element_macierzy(i,i)));

        for(int k = 0 ; k < rozmiar ; ++k)
            Q.set_element_macierzy(k,i,Q.get_element_macierzy(k,i)/R.get_element_macierzy(i,i));

    }
    Q.wyswietl_macierz();
    R.wyswietl_macierz();
}


