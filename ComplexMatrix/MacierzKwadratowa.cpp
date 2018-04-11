#include "MacierzKwadratowa.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;


MacierzKwadratowa::MacierzKwadratowa():MacierzProstokatna()
{
    rozmiar = 0;
}

MacierzKwadratowa::MacierzKwadratowa(int n):MacierzProstokatna(n,n)
{
    rozmiar = n;
}

MacierzKwadratowa::MacierzKwadratowa(const MacierzKwadratowa& A):MacierzProstokatna(A)
{
    rozmiar = A.get_rozmiar();
    wyznacznik();
}

MacierzKwadratowa::~MacierzKwadratowa()
{
}

MacierzKwadratowa MacierzKwadratowa::operator*(const MacierzKwadratowa& B)
{
    MacierzKwadratowa C(rozmiar);
    if(rozmiar == B.rozmiar)
    {
        complex<double> pom;

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

MacierzKwadratowa&  MacierzKwadratowa::operator=(const MacierzKwadratowa& A)
{
    ///NISZCZENIE ZAWARTOSCI
    for(int i = 0 ; i < rozmiar ; ++i)
        delete [] M[i];
    delete [] M;

    ///ALOKOWANIE NOWEJ I KOPIOWANIE
    rozmiar = A.get_rozmiar();
    M = new complex<double> *[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        M[i] = new complex<double> [rozmiar];

        for(int j = 0 ; j < rozmiar ; ++j)
            M[i][j] = A.get_element_macierzy(i,j);
    }
    return *this;
}

MacierzKwadratowa& MacierzKwadratowa::operator=(const MacierzProstokatna& A)
{
    if(A.get_l_kolumn() != A.get_l_wierszy())
    {
        cout<<"Nie jest to macierz kwadratowa!"<<endl;
        return *this;
    }
    ///NISZCZENIE ZAWARTOSCI
    if(rozmiar > 0)
    {
        for(int i = 0 ; i < rozmiar ; ++i)
            delete [] M[i];
        delete [] M;
    }

    ///ALOKOWANIE NOWEJ I KOPIOWANIE
    rozmiar = A.get_l_kolumn();
    ustaw_w(rozmiar);
    ustaw_k(rozmiar);
    M = new complex<double> *[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        M[i] = new complex<double> [rozmiar];

        for(int j = 0 ; j < rozmiar ; ++j)
            M[i][j] = A.get_element_macierzy(i,j);
    }
    return *this;
}


void MacierzKwadratowa::pobierz_macierz()
{
    cout << "Podaj rozmiar macierzy: " << endl;
    cin >> rozmiar;
    ustaw_k(rozmiar);
    ustaw_w(rozmiar);

    M = new complex<double> *[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        M[i] = new complex<double> [rozmiar];

        for(int j = 0 ; j < rozmiar ; ++j)
            M[i][j] = 0;
    }

    cout << "Podaj elemnty macierzy wierszami(najpierw czesc rzeczywista, potem zespolona): " << endl;

    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            cin>>M[i][j].real()>>M[i][j].imag();

    wyznacznik();
}

MacierzKwadratowa MacierzKwadratowa::operator~()
{
    MacierzKwadratowa T(rozmiar);
    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            T.set_element_macierzy(i,j,conj(M[j][i]));
    return T;
}

int MacierzKwadratowa::znak_permutacji(int *perm)
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

void MacierzKwadratowa::permutacja(int m,int *perm,int *wolny)
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
                complex<double> czynnik = 1;
                for(int j = 0 ; j < rozmiar ; ++j)
                    czynnik *= M[j][perm[j]];
                czynnik *= znak_permutacji(perm);
                det += czynnik;
            }
            wolny[i] = 1;
        }
}

complex<double>* MacierzKwadratowa::operator*(complex<double> *x)
{
    complex<double> *y = new complex<double>[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        y[i] = 0;
        for(int j = 0 ; j < rozmiar ; ++j)
            y[i] += M[i][j]*x[j];
    }
    return y;
}

void MacierzKwadratowa::wyznacznik()
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

complex<double> MacierzKwadratowa::dopelnienie_algebraiczne(int m,int n)
{
    MacierzKwadratowa D(rozmiar-1);
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

    complex<double> w = D.get_det();
    return ((n+m)%2 ? -w : w);
}

MacierzKwadratowa MacierzKwadratowa::operator-()
{
    MacierzKwadratowa O(rozmiar);
    if(abs(this->get_det()))
    {
        complex<double> jedynka(1,0);
        for(int i = 0 ; i < rozmiar ; ++i)
            for(int j = 0 ; j < rozmiar ; ++j)
                O.set_element_macierzy(i,j,jedynka/det*dopelnienie_algebraiczne(j,i));
    }
    else
    {
        cout<<"Macierz odwrotna nie istnieje!"<<endl;
        system("pause");
    }
    return O;
}

void MacierzKwadratowa::subtract_to_element_macierzy(int i,int j,complex<double> l)
{
    if(i < rozmiar && j < rozmiar)
        M[i][j] -= l;
}

MacierzKwadratowa MacierzKwadratowa::eliminacja_Gaussa(int co_zwracamy)
{
    MacierzKwadratowa L(rozmiar),U(*this);
    if(!abs(get_det()))
    {
        cout<<"Macierz jest osobliwa!"<<endl;
        return U;
    }

    for(int i = 0 ; i < rozmiar ; ++i)
        L.set_element_macierzy(i,i,1);///MACIERZ L MA NA PRZEKATNEJ ZAWSZE 1

    for(int k = 0 ; k < rozmiar ; ++k)
        for(int i = k+1 ; i < rozmiar ; ++i)
        {
            if(!abs(U.get_element_macierzy(k,k)))
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

void MacierzKwadratowa::zamien_wiersze_macierzy(int k, int l)
{
    complex<double> pom;
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        pom = M[k][i];
        M[k][i] = M[l][i];
        M[l][i] = pom;
    }
}

int MacierzKwadratowa::zwroc_wiersz(int k)
{
    float maks = abs(M[k][k]);
    int numer = k;
    for(int i = k+1 ; i < rozmiar ; ++i)
    {
        if(abs(M[i][k]) > maks)
        {
            maks = abs(M[i][k]);
            numer = i;
        }
    }
    return numer;
}

MacierzKwadratowa MacierzKwadratowa::eliminacja_GaussaWEG()
{
    MacierzKwadratowa L(rozmiar),U(*this);
    if(!abs(get_det()))
    {
        cout<<"Macierz jest osobliwa!"<<endl;
        return U;
    }
    float *p = new float[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
        p[i] = i;

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

    MacierzKwadratowa P(rozmiar);
    for(int i = 0 ; i < rozmiar ; ++i)
        P.set_element_macierzy(i,p[i],1);
    delete [] p;
    return P;
}

float MacierzKwadratowa::Knorma2_wektora(int i,int k)
{
    float l = 0;
    for(int j = i ; j < rozmiar ; ++j)
        l += pow(abs(get_element_macierzy(j,k)),2);
    return l;
}


MacierzKwadratowa MacierzKwadratowa::rozklad_HausholderaR()
{
    MacierzKwadratowa R(*this);
    complex<double> *u = new complex<double>[rozmiar];
    complex<double> v;

    for(int i = 0 ; i < rozmiar-1 ; ++i)
    {
        complex<double> znak = R.get_element_macierzy(i,i)/abs(R.get_element_macierzy(i,i));
        double norma = sqrt(R.Knorma2_wektora(i,i));
        double q = norma*(norma+abs(R.get_element_macierzy(i,i)));
        u[i] = znak*(abs(R.get_element_macierzy(i,i))+norma);
        for(int j = i+1 ; j < rozmiar ; ++j)
            u[j] = R.get_element_macierzy(j,i);

        for(int n = i ; n < rozmiar ; ++n)///kolumna
        {
            v = 0;
            for(int j = i ; j < rozmiar ; ++j)
                v += conj(u[j])*R.get_element_macierzy(j,n);
            v /= q;
            for(int m = i ; m < rozmiar ; ++m)
                R.subtract_to_element_macierzy(m,n,v*u[m]);
        }
    }
    delete [] u;
    return R;
}

void MacierzKwadratowa::zamien_na_jednostkowa()
{
    for(int i = 0 ; i < rozmiar ; ++i)
        for(int j = 0 ; j < rozmiar ; ++j)
            if(i == j)
                M[i][j] = 1;
            else
                M[i][j] = 0;
}

MacierzKwadratowa MacierzKwadratowa::rozklad_HausholderaQ()
{
    MacierzKwadratowa R(*this);
    MacierzKwadratowa Q(rozmiar);
    Q.zamien_na_jednostkowa();
    MacierzKwadratowa P(rozmiar);
    complex<double> *u = new complex<double>[rozmiar];

    for(int i = 0 ; i < rozmiar-1 ; ++i)
    {
        complex<double> znak = R.get_element_macierzy(i,i)/abs(R.get_element_macierzy(i,i));
        double norma = sqrt(R.Knorma2_wektora(i,i));
        double q = norma*(norma+abs(R.get_element_macierzy(i,i)));
        u[i] = znak*(abs(R.get_element_macierzy(i,i))+norma);
        for(int j = i+1 ; j < rozmiar ; ++j)
            u[j] = R.get_element_macierzy(j,i);

        P.zamien_na_jednostkowa();
        for(int j = i ; j < rozmiar ; ++j)
            for(int k = i ; k < rozmiar ; ++k)
                P.subtract_to_element_macierzy(j,k,(u[j]*conj(u[k]))/q);

        Q = Q*P;
        R = P*R;
        u[i] = 0;
    }
    delete [] u;
    return Q;
}

void MacierzKwadratowa::rozwiaz_ukladLU(complex<double> *b)
{
    if(!abs(get_det()))
    {
        cout<<"Wyznacznik macierzy wynosi 0!"<<endl;
        return;
    }
    complex<double> *y = new complex<double>[rozmiar];
    complex<double> *x = new complex<double>[rozmiar];
    MacierzKwadratowa L = eliminacja_Gaussa(0);
    MacierzKwadratowa U = eliminacja_Gaussa(1);

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

void MacierzKwadratowa::rozwiaz_ukladLUzWEG(complex<double> *b)
{
    if(!abs(get_det()))
    {
        cout<<"Wyznacznik macierzy wynosi 0!"<<endl;
        return;
    }
    complex<double> *y = new complex<double>[rozmiar];
    complex<double> *x = new complex<double>[rozmiar];

    MacierzKwadratowa P = eliminacja_GaussaWEG();
    MacierzKwadratowa A = P*(*this);
    MacierzKwadratowa L = A.eliminacja_Gaussa(0);
    MacierzKwadratowa U = A.eliminacja_Gaussa(1);
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

MacierzKwadratowa MacierzKwadratowa::odwrotnaLU()
{
    if(!abs(get_det()))
    {
        cout<<"Macierz osobliwa!"<<endl;
        return *this;
    }
    MacierzKwadratowa P = (*this).eliminacja_GaussaWEG();
    MacierzKwadratowa A = P*(*this);
    MacierzKwadratowa L = A.eliminacja_Gaussa(0);
    MacierzKwadratowa U = A.eliminacja_Gaussa(1);
    MacierzKwadratowa O(rozmiar);

    complex<double> *b = new complex<double>[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)
        b[i] = 0;

    complex<double> *x = new complex<double>[rozmiar];
    complex<double> *y = new complex<double>[rozmiar];

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

void MacierzKwadratowa::rozwiaz_ukladQR(complex<double> *b)///Ax=b ; QRx=b ; Qy=b ; Rx=y
{
    complex<double> *y = new complex<double>[rozmiar];
    complex<double> *x = new complex<double>[rozmiar];
    MacierzKwadratowa Q = rozklad_HausholderaQ();
    y = (~Q)*b;
    MacierzKwadratowa R = rozklad_HausholderaR();

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

MacierzKwadratowa MacierzKwadratowa::postac_Hessenberga()
{
    MacierzKwadratowa A(*this);
    MacierzKwadratowa P(rozmiar);
    complex<double> *u = new complex<double>[rozmiar];
    complex<double> q;
    u[0] = 0;

    for(int i = 0 ; i < rozmiar-2 ; ++i)
    {
        complex<double> znak = A.get_element_macierzy(i+1,i)/abs(A.get_element_macierzy(i+1,i));
        double norma = sqrt(A.Knorma2_wektora(i+1,i));
        double q = norma*(norma+abs(A.get_element_macierzy(i+1,i)));
        u[i+1] = znak*(abs(A.get_element_macierzy(i+1,i))+norma);
        for(int j = i+2 ; j < rozmiar ; ++j)
            u[j] = A.get_element_macierzy(j,i);
        if(abs(q))
        {
            P.zamien_na_jednostkowa();
            for(int j = i+1 ; j < rozmiar ; ++j)
                for(int k = i+1 ; k < rozmiar ; ++k)
                    P.subtract_to_element_macierzy(j,k,u[j]*conj(u[k])/q);
            A=P*A;
            A=A*P;
        }
        u[i] = 0;
    }
    delete [] u;
    return A;
}

complex<double> MacierzKwadratowa::algorytm_Hymana()///MOZE BYC PRZYPADEK ZE TRZEBA ROZBIC NA PODZADANIA
{
    complex<double> w=1;
    if((*this) == (~(*this)))
        w = Hyman_symetryczna(rozmiar-1);
    else
    {
        int p = 0;
        for(int i = 0 ; i < rozmiar-2 ; ++i)
        {
            if(!abs(M[i+1][i]))
            {
                w *= Hyman_podzadanie(p,i+1-p);
                p = i+1;
            }
        }
        w *= Hyman_podzadanie(p,rozmiar-p);
    }
    return w;
}

complex<double> MacierzKwadratowa::Hyman_podzadanie(int p,int d)///(poczatek,wielkosc macierzy)
{
    complex<double> *x = new complex<double>[d];
    for(int i = 0 ; i < d ; ++i)
        x[i] = 0;

    x[0] = 1;
    for(int i = 1 ; i < d ; ++i)
    {
        for(int j = 0 ; j < i ; ++j)
            x[i] += x[j]*M[p+j][p+i-1];
        x[i] /= -M[p+i][p+i-1];
    }

    complex<double> pom = M[p][p+d-1] , w = 1;
    for(int i = 1 ; i < d ; ++i)
    {
        pom += x[i]*M[p+i][p+d-1];
        w *= M[p+i][p+i-1];
    }
    w *= pom;
    delete [] x;

    return ((d+1)%2) ? -w : w;
}

complex<double> MacierzKwadratowa::Hyman_symetryczna(int i)
{
    if(i == -1)
        return 1;
    if(i == 0)
        return M[0][0];
    return M[i][i]*Hyman_symetryczna(i-1)-pow(abs(M[i-1][i]),2)*Hyman_symetryczna(i-2);
}

void MacierzKwadratowa::wyznacznikM()
{
    complex<double> detLU=1,detQR=1;
    int *p = new int[rozmiar];
    MacierzKwadratowa P = (*this).eliminacja_GaussaWEG();
    for(int i = 0 ; i < rozmiar ; ++i)///ODTWARZAMY PERMUTACJE ZEBY OBLICZYC ZNAK PRZY WYZNACZNIKU
        for(int j = 0 ; j < rozmiar ; ++j)
            if(abs(P.get_element_macierzy(i,j)))
            {
                p[i] = j;
                break;
            }

    MacierzKwadratowa U = (P*(*this)).eliminacja_Gaussa(1);
    MacierzKwadratowa R = (*this).rozklad_HausholderaR();
    MacierzKwadratowa Q = (*this).rozklad_HausholderaQ();
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        detLU *= U.get_element_macierzy(i,i);
        detQR *= R.get_element_macierzy(i,i);
    }
    detLU *= znak_permutacji(p);
    detQR *= (Q.get_det().real()>0) ? 1 : -1;///WYZNACZNIK MACIERZY ORTOGONALNEJ TO 1 LUB -1

    cout<<"Wyznacznik macierzy wynosi:"<<endl;
    cout<<"korzystajac z definicji: "<<get_det()<<endl;
    cout<<"korzystajac z rozkladu LU: "<<detLU<<endl;
    cout<<"korzystajac z rozkladu QR: "<<detQR<<endl;
    cout<<"korzystajac z macierzy Hessenberga: "<<((*this).postac_Hessenberga()).algorytm_Hymana()<<endl;
}

MacierzKwadratowa MacierzKwadratowa::odejmij_na_przekatnej(complex<double> lambda)
{
    MacierzKwadratowa A(*this);
    for(int i = 0 ; i < rozmiar ; ++i)
        A.subtract_to_element_macierzy(i,i,lambda);
    return A;
}

void MacierzKwadratowa::ciag_Sturma()
{
    if(((*this) == (~(*this))) == false)///MACIERZ NIE JEST HERMITOWSKA
    {
        cout<<"Ten algorytm dziala poprawnie tylko dla macierzy hermitowskich!"<<endl;
        cout<<"Dana macierz nie jest hermitowska!"<<endl;
        return;
    }
    int s,poprz_s = rozmiar;
    MacierzKwadratowa A = (*this).postac_Hessenberga();
    double a = (*this).lokalizacja_Gerszgorina(0),b=(*this).lokalizacja_Gerszgorina(1);
    double krok = 0.05, c = a;
    complex<double> pom;
    do
    {
        s = 0;
        for(int i = 0 ; i < rozmiar ; ++i)
        {
            MacierzKwadratowa P = A.odejmij_na_przekatnej(c);
            pom = P.Hyman_symetryczna(i-1)*P.Hyman_symetryczna(i);
            if(pom.real() >= 0)
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

double MacierzKwadratowa::ciag_Sturma(int ktora)
{
    if(ktora > rozmiar)
        return 0;

    int s,poprz_s = rozmiar;
    MacierzKwadratowa A = (*this).postac_Hessenberga();
    double a = (*this).lokalizacja_Gerszgorina(0),b=(*this).lokalizacja_Gerszgorina(1);
    double krok = 0.05, c = a;
    complex<double> pom;
    do
    {
        s = 0;
        for(int i = 0 ; i < rozmiar ; ++i)
        {
            MacierzKwadratowa P = A.odejmij_na_przekatnej(c);
            pom = P.Hyman_symetryczna(i-1)*P.Hyman_symetryczna(i);
            if(pom.real() >= 0)
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

double MacierzKwadratowa::lokalizacja_Gerszgorina(int w)///KTORY KRANIEC ZWROCIC 0 lewy , 1 prawy
{
    double lewy,prawy,promien;
    double srodek;
    for(int i = 0 ; i < rozmiar ; ++i)
    {
        promien = 0;
        srodek = M[i][i].real();
        for(int j = 0 ; j < rozmiar ; ++j)
            if(j != i)
                promien += abs(M[i][j]);

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

MacierzKwadratowa MacierzKwadratowa::metodaQR()
{
    wyznacznik();
    if(!abs(det))
    {
        cout<<"Wyznacznik macierzy wynosi zero!"<<endl;
        return *this;
    }
    MacierzKwadratowa P = (*this).postac_Hessenberga();///SPROWADZENIE DO POSTACI HESSENBERGA PRZYSPIESZA PROCES
    MacierzKwadratowa Q = P.rozklad_HausholderaQ();
    MacierzKwadratowa R = P.rozklad_HausholderaR();
    P = R*Q;
    for(int i = 1 ; i < 100 ; ++i)
    {
        Q = P.rozklad_HausholderaQ();
        R = P.rozklad_HausholderaR();
        P = R*Q;
    }

    complex<double> sigma = 0;
    for(int i = 1 ; i < rozmiar ; ++i)
    {
        if(abs(P.get_element_macierzy(i,i-1))>0.01)
        {
            sigma = P.przesuniecie(i,i-1);
            P.set_element_macierzy(i,i-1,0);
            P.set_element_macierzy(i-1,i-1,sigma);
            P.set_element_macierzy(i,i,conj(sigma));
        }
    }
    return P;
}

void MacierzKwadratowa::metoda_potegowa()
{/*
    if(((*this) == (~(*this))) == false)///MACIERZ NIE JEST HERMITOWSKA
    {
        cout<<"Ta metoda dziala poprawnie tylko dla macierzy hermitowskich z dominujaca wartoscia wlasna!"<<endl;
        return;
    }*/
    complex<double> *z = new complex<double>[rozmiar];
    for(int i = 0 ; i < rozmiar ; ++i)///NORMA WEKTORA POCZATKOWEGO MUSI WYNOSIC 1
        z[i] = 1/sqrt(rozmiar);

    complex<double> *y = new complex<double>[rozmiar];
    complex<double> pom;

    for(int i = 0 ; i < 100 ; ++i)
    {
        z = (*this)*z;
        pom = 0;
        for(int i = 0 ; i < rozmiar ; ++i)
            pom += pow(abs(z[i]),2);
        pom = sqrt(pom);
        for(int i = 0 ; i < rozmiar ; ++i)
            z[i] /= pom;
    }

    y = (*this)*z;
    pom = 0;
    for(int i = 0 ; i < rozmiar ; ++i)
        pom += y[i]*conj(z[i]);///CIAG RAYLEIGHA

    cout<<"Wektor wlasny dominujacej wartosci wlasnej "<<pom<<" wynosi: "<<endl;
    for(int i = 0 ; i < rozmiar ; ++i)
        cout<<z[i]<<" ";
    cout<<endl;

    delete [] z;
    delete [] y;

}

void MacierzKwadratowa::metoda_Wielandta()
{
    if(((*this) == (~(*this))) == false)///MACIERZ NIE JEST HERMITOWSKA
    {
        cout<<"Ta metoda dziala poprawnie tylko dla macierzy hermitowskich!"<<endl;
        return;
    }
    complex<double> *z = new complex<double>[rozmiar];
    for(int j = 1 ; j <= rozmiar ; ++j)
    {
        float lambda = (*this).ciag_Sturma(j);
        MacierzKwadratowa A = ((*this).odejmij_na_przekatnej(lambda)).odwrotnaLU();


        for(int i = 0 ; i < rozmiar ; ++i)///NORMA WEKTORA POCZATKOWEGO MUSI WYNOSIC 1
            z[i] = 1/sqrt(rozmiar);
        float pom;

        for(int i = 0 ; i < 2 ; ++i)
        {
            z = A*z;
            pom = 0;
            for(int k = 0 ; k < rozmiar ; ++k)
                pom += pow(abs(z[k]),2);
            pom = sqrt(pom);
            for(int k = 0 ; k < rozmiar ; ++k)
                z[k] /= pom;
        }

        cout<<"Wektor wlasny wartosci wlasnej "<<lambda<<" wynosi: "<<endl;
        for(int i = 0 ; i < rozmiar ; ++i)
            cout<<z[i]<<" ";
        cout<<endl;
        cout<<endl;

    }
    delete [] z;
}

complex<double> MacierzKwadratowa::przesuniecie(int i,int j)
{
    complex<double> a,b,c,d,delta,x,pom;
    a = M[i-1][j];
    b = M[i-1][j+1];
    c = M[i][j];
    d = M[i][j+1];

    delta = pow(a+d,2);
    pom = (a*d-b*c);
    pom *= 4;
    delta -= pom;
    delta = sqrt(delta);
    x = delta + a + d;
    x /= 2;
    return x;
}

float MacierzKwadratowa::norma_druga()
{
    MacierzKwadratowa A = ((~(*this))*(*this)).metodaQR();
    float maks = 0;
    for(int i = 0 ; i < rozmiar ; ++i)
        if(abs(A.get_element_macierzy(i,i)) > maks)
            maks = abs(A.get_element_macierzy(i,i));

    return sqrt(maks);
}

