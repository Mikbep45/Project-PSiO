#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class Json_handler
{
  private:
     const std::string nazwa_pliku_json = "info_szczegolowe.json";
     json dane;
     void zapisz();

     friend void operator-= ( Json_handler& j, const std::string& nazwa);

  public:
     Json_handler();

     std::vector<std::string> pobierz_gatunki_mrowek();

     void dodaj(json nowy_gatunek, std::string nazwa);

     json operator[] (const std::string& gatunek);
};
