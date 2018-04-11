#include <iostream>
#include "macierz.h"
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <math.h>


using namespace std;
HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);

vector<Macierz> Matrices;

void pobierz_dane_z_pliku()
{
    fstream plik;
    plik.open("proba.txt",ios::in);
    if(!plik.good())
    {
        cout<<"Blad otwarcia pliku!"<<endl;
        exit(0);
    }
    float number;
    int miejsce,rzad,r;
    while(!plik.eof())
    {
        plik>>number;
        Macierz *wsk = new Macierz(number);
        miejsce = 0;
        rzad = -1;
        r = number;
        for(int i = 0 ; i < r*r ; ++i)
        {
            plik>>number;
            if(!miejsce)
                ++rzad;
            wsk->set_element_macierzy(rzad,miejsce,number);
            miejsce = (miejsce+1)%r;
        }
        Matrices.push_back(*wsk);
        delete wsk;
    }
    plik.close();
}


int main()
{
    int wybor;
    while(1)
    {
        SetConsoleTextAttribute(uchwyt,15);
        system("cls");
        cout<<"OPERACJE Z MACIERZAMI"<<endl;
        cout<<"W bazie znajduje sie "<<Matrices.size()<<" macierzy"<<endl;
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
        cout<<"14 - Rozklad QR metoda Grama-Schmidta"<<endl;
        cout<<"15 - Koniec programu"<<endl;
        cout<<"Twoj wybor: ";
        cin>>wybor;
        system("cls");

        switch(wybor)
        {
        case 1:
        {
            Macierz *P = new Macierz;
            P->pobierz_macierz();
            Matrices.push_back(*P);
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
            for( size_t i = 0; i < Matrices.size(); i++ )
            {
                system("cls");
                cout<<"Macierz numer "<<i+1<<endl;
                Matrices[i].wyswietl_macierz();
                system("pause");
            }
            break;
        }
        case 4:
        {
            int wybor2;
            cout<<"Ktora macierz z "<<Matrices.size()<<" chcesz usunac:"<<endl;
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
                        if(pozycja > Matrices.size())
                        {
                            cout<<"Nie ma takiej macierzy!"<<endl;
                            system("pause");
                        }
                        else
                            Matrices.erase(Matrices.begin()+pozycja-1);
                        break;
                    }
            case 2:
                    {
                         Matrices.clear();
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
            if(pozycja > Matrices.size())
                cout<<"Nie ma takiej macierzy!"<<endl;
            else
            {
                float *b = new float[Matrices[pozycja-1].get_rozmiar()];
                cout<<"Podaj "<<Matrices[pozycja-1].get_rozmiar()<<" wspolczynnikow"<<endl;
                for(int i = 0 ; i < Matrices[pozycja-1].get_rozmiar() ; ++i)
                    cin>>b[i];
                Matrices[pozycja-1].rozwiaz_ukladQR(b);
                Matrices[pozycja-1].rozwiaz_ukladLU(b);
                Matrices[pozycja-1].rozwiaz_ukladLUzWEG(b);
                delete [] b;
            }
            system("pause");
            break;
        }
        case 6:
        {
              for( size_t i = 0; i < Matrices.size(); i++ )
              {
                     Matrices[i].wyswietl_macierz();
                     cout<<"Macierz odwrotna "<<endl;
                     (-Matrices[i]).wyswietl_macierz();
                     //(Matrices[i].odwrotnaLU()).wyswietl_macierz();
                     cout<<"Rozklad LU macierzy"<<endl;
                     (Matrices[i].eliminacja_Gaussa(0)).wyswietl_macierz();
                     (Matrices[i].eliminacja_Gaussa(1)).wyswietl_macierz();
                     cout<<"Rozklad QR macierzy"<<endl;
                     (Matrices[i].rozklad_HausholderaQ()).wyswietl_macierz();
                     (Matrices[i].rozklad_HausholderaR()).wyswietl_macierz();
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
            Macierz H(n);
            float *b = new float[n];
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
            for( size_t i = 0; i < Matrices.size(); i++ )
            {
                Matrices[i].wyswietl_macierz();
                Matrices[i].wyznacznikM();
                cout<<"----------------------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 9:
        {
            for( size_t i = 0; i < Matrices.size(); i++ )
            {
                Matrices[i].wyswietl_macierz();
                Matrices[i].ciag_Stuma();
                cout<<"----------------------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 10:
        {
            cout<<"(Rzeczywiste) Wartosci wlasne macierzy sa liczbami na przekatnej"<<endl;
            for( size_t i = 0; i < Matrices.size(); i++ )
            {
                Matrices[i].wyswietl_macierz();
                (Matrices[i].metodaQR()).wyswietl_macierz('d');
                cout<<"-----------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 11:
        {
            for( size_t i = 0; i < Matrices.size(); i++ )
            {
                Matrices[i].wyswietl_macierz();
                cout<<"Norma pierwsza macierzy wynosi: "<<Matrices[i].norma_pierwsza()<<endl;
                cout<<"Norma druga macierzy wynosi: "<<Matrices[i].norma_druga()<<endl;
                cout<<"Norma nieskonczonosc macierzy wynosi: "<<Matrices[i].norma_nieskonczonosc()<<endl;
                cout<<"Norma frobeniusa macierzy wynosi: "<<Matrices[i].norma_frobeniusa()<<endl;
                cout<<"-----------------------------------"<<endl;
            }
            system("pause");
            break;
        }
        case 12:
        {
                for( size_t i = 0; i < Matrices.size(); i++ )
                {
                    Matrices[i].wyswietl_macierz();
                    Matrices[i].metoda_potegowa();
                    cout<<"-----------------------------------------------"<<endl;
                }
                system("pause");
                break;
        }
        case 13:
        {
                for( size_t i = 0; i < Matrices.size(); i++ )
                {
                    Matrices[i].wyswietl_macierz();
                    Matrices[i].metoda_Wielandta();
                    cout<<"------------------------------------------------"<<endl;
                }
                system("pause");
                break;
        }
        case 14:
        {
                for( size_t i = 0; i < Matrices.size(); i++ )
                {
                    Matrices[i].wyswietl_macierz();
                    cout<<"Rozklad QR metoda Grama-Schmidta"<<endl;
                    Matrices[i].Gram_Schmidt();
                    cout<<"------------------------------------------------"<<endl;
                }
                system("pause");
                break;
        }
        case 15:
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
