#include "quiz_mrowki.h"
#include <iostream>
#include <fstream>

void QuizMrowki::wczytajPytaniaZPliku(const string& nazwaPliku)
{
    ifstream plik(nazwaPliku);
    if (!plik.is_open())
      {
        cerr << "Nie udalo sie otworzyc pliku: " << nazwaPliku << endl;
        return;
      }

    liczba_pytan = 0;
    while (plik.good() && liczba_pytan < MAX_PYTAN)
      {
        getline(plik, pytania[liczba_pytan]);
        getline(plik, odpowiedzi[liczba_pytan]);
        liczba_pytan++;
      }

    plik.close();
}



QuizMrowki::QuizMrowki(const string& nazwaPliku)
{
    wczytajPytaniaZPliku(nazwaPliku);
}



void QuizMrowki::uruchomQuiz()
{
    int poprawne = 0;
    string odpowiedzUzytkownika;

    for (int i = 0; i < liczba_pytan; ++i)
       {
        cout <<rozowy<<"Pytanie " << (i + 1) << ": " << pytania[i] <<reset<< endl;
        cout << "Twoja odpowiedz: ";
        getline(cin, odpowiedzUzytkownika);
        system("cls");

        if (odpowiedzUzytkownika == odpowiedzi[i])
         {
            cout << "Poprawna odpowiedz!\n";
            poprawne++;
         }
        else
         {
            cout << "Niepoprawna. Poprawna odpowiedz to: " << odpowiedzi[i] << "\n";
         }
       }

    cout <<jasny_zielen<< "\nKoniec quizu! Poprawnych odpowiedzi: " << poprawne << "/" << liczba_pytan <<reset<< endl;
        if(poprawne <3)
    {
        cout<<jasny_zielen<<"Widac ze dopiero zaczynasz swoja przygode z mrowkami :D"<<reset<<endl;
    }
        if(poprawne >=3 && poprawne<6)
    {
        cout<<jasny_zielen<<"Cos niecos potrafisz :D"<<reset<<endl;
    }
        if(poprawne >=6 && poprawne<9)
    {
        cout<<jasny_zielen<<"Jestes naprawde obeznany w srodowisku mrowek!"<<reset<<endl;
    }
        if(poprawne >=9)
    {
        cout<<jasny_zielen<<"Zacznij wykladac lepiej wiedze mrowkowa!"<<reset<<endl;
    }
}
