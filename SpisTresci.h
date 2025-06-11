#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "jsonhandler.h"
#include <algorithm>
#include "loging.h"
#include "historia_walk.h"
using namespace std;


class SpisTresc : public Loging, public HistoriaWalk
{
  private:
      static const int MAX_GATUNKI = 100;
      const string green = "\033[32m";
      const string red = "\033[31m";
      const string reset = "\033[0m";

     Json_handler* json_handler;
     string gatunki_mrowek[MAX_GATUNKI];
     int liczbaGatunkow_mrowek = 0;
  public:

     SpisTresc()
     {
         json_handler = new Json_handler;
     }
     void wyswietlGatunki_mrowek() const;

     void dodajNowyGatunek_mrowek();

     bool usunIstniejacyGatunek(int numer_gatunku);

     void wyswietlSzczegolyGatunku(int numerGatunku, const string typ_mrowki) const;

     void walka(const string imie1, const string imie2, const int mrowka1, const int mrowka2);
};
