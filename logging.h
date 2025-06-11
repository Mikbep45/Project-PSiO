#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Loging
{
protected:
    ofstream plik;
    ofstream plik2;

    void logowanie(const string level, const string wiadomosc);
    void logowanie_walka(const string& wynikWalki);


public:
    Loging();


    virtual ~Loging();


    string aktualny_czas();
};
