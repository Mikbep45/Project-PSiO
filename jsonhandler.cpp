#include "jsonhandler.h"

Json_handler::Json_handler()
{
    std::ifstream plik(nazwa_pliku_json);
    plik >> dane;
}


std::vector<std::string> Json_handler::pobierz_gatunki_mrowek()
{
    std::vector <std::string> gatunki;
    for (auto it = dane.begin(); it != dane.end(); it++)
    {
        gatunki.push_back(it.key());
    }
    return gatunki;

}

void Json_handler::dodaj(json nowy_gatunek, std::string nazwa)
{
    dane[nazwa] = nowy_gatunek;
    zapisz();
}

void Json_handler::zapisz()
{
    std::ofstream plik(nazwa_pliku_json, std::ios::trunc);
    plik.clear();
    plik<<std::setw(4)<<dane;
}


json Json_handler::operator[](const std::string& gatunek)
{
  return dane[gatunek];
}

void operator-= ( Json_handler& j,const std::string& nazwa)
{
j.dane.erase(nazwa);
    j.zapisz();
}
