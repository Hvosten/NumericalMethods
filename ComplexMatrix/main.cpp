#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "MacierzProstokatna.h"
#include "MacierzKwadratowa.h"


using namespace std;
extern HANDLE uchwyt;

vector<MacierzKwadratowa> SquareMatrices;
void dodajMacierz(ifstream&);

void pobierz_dane_z_pliku()
{
    ifstream plik;
    plik.open("ComplexMatrix.txt");
    if(!plik.good())
    {
        cout<<"Blad otwarcia pliku!"<<endl;
        exit(0);
    }

    while(!plik.eof())
        dodajMacierz(plik);
    plik.close();
}

void dodajMacierz(ifstream &input)
{
    float number;
    complex<double> z;
    int miejsce = 0,rzad = -1;
    input>>number;
    int r = number;
    MacierzKwadratowa pom(r);
    for(int i = 0 ; i < r*r && !input.eof(); ++i)
    {
        input>>z.real();
        input>>z.imag();
        if(!miejsce)
            ++rzad;
        pom.set_element_macierzy(rzad,miejsce,z);
        miejsce = (miejsce+1)%r;
    }
    pom.wyswietl_macierz();
    SquareMatrices.push_back(pom);
    cout<<"*"<<endl;
}




int main()
{
    int wybor;
    while(1)
    {
        SetConsoleTextAttribute(uchwyt,15);
        system("cls");
        cout<<"OPERACJE Z MACIERZAMI"<<endl;
        cout<<"W bazie znajduje sie "<<SquareMatrices.size()<<" macierzy"<<endl;
        cout<<"MENU"<<endl;
        cout<<"1 - Dodaj macierz"<<endl;
        cout<<"2 - Wczytaj macierze z pliku"<<endl;
        cout<<"3 - Wyswietl macierz"<<endl;
        cout<<"4 - Usun macierz"<<endl;
        cout<<"5 - Rozwiaz uklad rownan"<<endl;
        cout<<"6 - Macierz odwrotna, rozklad LU i QR"<<endl;
        cout<<"7 - Przyklad macierzy zle uwarunkowanej"<<endl;
        cout<<"8 - Wyznacznik mcierzy"<<endl;
        cout<<"9 - Lokalizacja wartosci wlasnych macierzy symetrycznej"<<endl;
        cout<<"10 - Znajdz wartosci wlasne macierzy metoda QR"<<endl;
        cout<<"11 - Norma macierzy"<<endl;
        cout<<"12 - Metoda potegowa(oblicza wektor wlasny dominujacej wartosci wlasnej)"<<endl;
        cout<<"13 - Metoda Wielandta(oblicza wektory wlasne macierzy symetrycznej)"<<endl;
        cout<<"14 - Koniec programu"<<endl;
        cout<<"Twoj wybor: ";
        cin>>wybor;
        system("cls");

        switch(wybor)
        {
        case 1:
        {
            MacierzKwadratowa *P = new MacierzKwadratowa;
            P->pobierz_macierz();
            SquareMatrices.push_back(*P);
            delete P;
            break;
        }
        case 2:
        {
            pobierz_dane_z_pliku();
            break;
        }
        case 3:
        {
            for( size_t i = 0; i < SquareMatrices.size(); i++ )
            {
                system("cls");
                cout<<"Macierz numer "<<i+1<<endl;
                SquareMatrices[i].wyswietl_macierz();
                system("pause");
            }
            break;
        }
        case 4:
        {
            int wybor2;
            cout<<"Ktora macierz z "<<SquareMatrices.size()<<" chcesz usunac:"<<endl;
            cout<<"1 - Podaj numer macierzy"<<endl;
            cout<<"2 - Usun wszystkie"<<endl;
            cout<<"Twoj wybor to:";
            cin>>wybor2;
            switch(wybor2)
            {
            case 1:
                    {
                        unsigned pozycja;
                        cout<<"Ktora macierz chcesz usunac :";
                        cin>>pozycja;
                        if(pozycja > SquareMatrices.size())
                        {
                            cout<<"Nie ma takiej macierzy!"<<endl;
                            system("pause");
                        }
                        else
                            SquareMatrices.erase(SquareMatrices.begin()+pozycja-1);
                        break;
                    }
            case 2:
                    {
                         SquareMatrices.clear();
                         break;
                    }
            default:
                    {
                        cout<<"Nie ma takiej opcji!"<<endl;
                        system("pause");
                    }
            }
            break;
        }
        case 5:
        {
            unsigned pozycja;
            cout<<"Dla ktorej macierzy chcesz podac macierz wspolczynnikow :";
            cin>>pozycja;
            if(pozycja > SquareMatrices.size())
                cout<<"Nie ma takiej macierzy!"<<endl;
            else
            {
                complex<double> *b = new complex<double>[SquareMatrices[pozycja-1].get_rozmiar()];
                cout<<"Podaj "<<SquareMatrices[pozycja-1].get_rozmiar()<<" wspolczynnikow"<<endl;
                for(int i = 0 ; i < SquareMatrices[pozycja-1].get_rozmiar() ; ++i)
                {
                    cin>>b[i].real();
                    cin>>b[i].imag();
                }
                SquareMatrices[pozycja-1].rozwiaz_ukladQR(b);
                SquareMatrices[pozycja-1].rozwiaz_ukladLU(b);
                SquareMatrices[pozycja-1].rozwiaz_ukladLUzWEG(b);
                delete [] b;
            }
            system("pause");
            break;
        }
        case 6:
        {
              for( size_t i = 0; i < SquareMatrices.size(); i++ )
              {
                     SquareMatrices[i].wyswietl_macierz();
                     cout<<"Macierz odwrotna "<<endl;
                     (-SquareMatrices[i]).wyswietl_macierz();
                     //(SquareMatrices[i].odwrotnaLU()).wyswietl_macierz();
                     cout<<"Rozklad LU macierzy"<<endl;
                     (SquareMatrices[i].eliminacja_Gaussa(0)).wyswietl_macierz();
                     (SquareMatrices[i].eliminacja_Gaussa(1)).wyswietl_macierz();
                     cout<<"Rozklad QR macierzy"<<endl;
                     (SquareMatrices[i].rozklad_HausholderaQ()).wyswietl_macierz();
                     (SquareMatrices[i].rozklad_HausholderaR()).wyswietl_macierz();
                     cout<<"----------------------------------------------"<<endl;
              }
              system("pause");
              break;
        }
        case 7:
        {
            int n;
            cout<<"Podaj rozmiar :";
            cin>>n;
            system("cls");
            MacierzKwadratowa H(n);
            complex<double> *b = new complex<double>[n];
            for(int i = 0 ; i < n ; ++i)
                for(int j = 0 ; j < n ; ++j)
                    H.set_element_macierzy(i,j,1.0/(i+j+1));

            for(int i = 0 ; i < n ; ++i)
            {
                b[i] = 0;
                for(int j = 0 ; j < n ; ++j)
                    b[i] += H.get_element_macierzy(i,j);
            }
            cout<<"Macierz Hilberta"<<endl;
            H.wyswietl_macierz();
            cout<<"Macierz odwrotna"<<endl;
            (-H).wyswietl_macierz();
            //(H.odwrotnaLU()).wyswietl_macierz();
            //((H.odwrotnaLU())*H).wyswietl_macierz();
            cout<<"Iloczyn macierzy  Hilberta i do niej odwrotnej"<<endl;
            ((-H)*H).wyswietl_macierz();
            cout<<"Rozklad LU"<<endl;
            (H.eliminacja_Gaussa(0)).wyswietl_macierz();
            (H.eliminacja_Gaussa(1)).wyswietl_macierz();
            cout<<"Iloczyn LU"<<endl;
            (H.eliminacja_Gaussa(0)*H.eliminacja_Gaussa(1)).wyswietl_macierz();
            cout<<"Rozklad QR"<<endl;
            (H.rozklad_HausholderaQ()).wyswietl_macierz();
            (H.rozklad_HausholderaR()).wyswietl_macierz();
            cout<<"Iloczyn QR"<<endl;
            (H.rozklad_HausholderaQ()*H.rozklad_HausholderaR()).wyswietl_macierz();
            cout<<"Rozwiazanie ukladu ze wspolczynnikami"<<endl;
            for(int i = 0 ; i < n ; ++i)
                cout<<b[i]<<" ";
            cout<<endl;
            cout<<"(powinny byc same 1) wynosi :"<<endl;
            H.rozwiaz_ukladLU(b);
            H.rozwiaz_ukladQR(b);
            delete [] b;
            system("pause");
            break;
        }
        case 8:
        {
            for( size_t i = 0; i < SquareMatrices.size(); i++ )
            {
                SquareMatrices[i].wyswietl_macierz();
                SquareMatrices[i].wyznacznikM();
                cout<<"----------------------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 9:
        {
            for( size_t i = 0; i < SquareMatrices.size(); i++ )
            {
                SquareMatrices[i].wyswietl_macierz();
                SquareMatrices[i].ciag_Sturma();
                cout<<"----------------------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 10:
        {
            cout<<"Wartosci wlasne macierzy sa liczbami na przekatnej"<<endl;
            for( size_t i = 0; i < SquareMatrices.size(); i++ )
            {
                SquareMatrices[i].wyswietl_macierz();
                (SquareMatrices[i].metodaQR()).wyswietl_macierz('d');
                cout<<"-----------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 11:
        {
            for( size_t i = 0; i < SquareMatrices.size(); i++ )
            {
                SquareMatrices[i].wyswietl_macierz();
                cout<<"Norma pierwsza macierzy wynosi: "<<SquareMatrices[i].norma_pierwsza()<<endl;
                cout<<"Norma druga macierzy wynosi: "<<SquareMatrices[i].norma_druga()<<endl;
                cout<<"Norma nieskonczonosc macierzy wynosi: "<<SquareMatrices[i].norma_nieskonczonosc()<<endl;
                cout<<"Norma frobeniusa macierzy wynosi: "<<SquareMatrices[i].norma_frobeniusa()<<endl;
                cout<<"-----------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 12:
        {
                for( size_t i = 0; i < SquareMatrices.size(); i++ )
                {
                    SquareMatrices[i].wyswietl_macierz();
                    SquareMatrices[i].metoda_potegowa();
                    cout<<"-----------------------------------------------"<<endl;
                }
                system("pause");
                break;
        }
        case 13:
        {
                for( size_t i = 0; i < SquareMatrices.size(); i++ )
                {
                    SquareMatrices[i].wyswietl_macierz();
                    SquareMatrices[i].metoda_Wielandta();
                    cout<<"------------------------------------------------"<<endl;
                }
                system("pause");
                break;
        }
        case 14:
        {
            exit(0);
        }
        default:
        {
            cout<<"Nie ma takiej opcji!";
            system("pause");
        }
        }
    }
    return 0;
}

