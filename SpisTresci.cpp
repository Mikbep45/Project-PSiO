#include "SpisTresci.h"

using namespace std;


void SpisTresc::wyswietlGatunki_mrowek() const
{
    cout<<"-------------------Spis Mrowek-------------------"<<endl;


    vector <string> gatunki = json_handler->pobierz_gatunki_mrowek();
    for(int i =0; i<gatunki.size(); i++)
    {
        cout<<green<<i+1<<reset<<". "<<gatunki[i]<<endl;
    }

    cout<<"-------------------------------------------------"<<endl;
}


void SpisTresc::dodajNowyGatunek_mrowek()
{
   string nazwa;
   cout<<"Wpisz pelna nazwe nowego gatunku w jezyku lacinskim: "<<endl;
   getline(cin, nazwa);
   system("cls");
   json nowyGatunek = json::parse(R"(
   {
     "Srodowisko" :  "",
     "Ciekawostka" : "",
     "Czy_jest_pod_ochrona" : "",
     "Krolowa" :
         {
           "Wielkosc": "",
           "Opis" : "",
           "Dzienna_ilosc_skladanych_jaj": ""
         },
     "Zolnierz" :
         {
             "Opis": "",
             "Zacisk szczek": "",
             "Ilosc zycia" : "",
             "Atak" : ""
         },
     "Robotnica" :
         {
           "Opis": "",
           "Obciazenie": ""
         }
   }
   )");
   string info;
   cout<<"Podaj srodowisko: "<<endl;
   getline(cin, info);
   nowyGatunek["Srodowisko"] = info;
   system("cls");

   cout<<"Podaj ciekawostke o gatunku: "<<endl;
   getline(cin, info);
   nowyGatunek["Ciekawostka"] = info;
   system("cls");

   cout<<"Podaj czy gatunke jest pod ochrona (Tak/Nie): "<<endl;
   getline(cin, info);
   nowyGatunek["Czy_jest_pod_ochrona"] = info;
   system("cls");

   cout<<"Podaj wielkosc krolowej(mm): "<<endl;
   getline(cin, info);
   nowyGatunek["Krolowa"]["Wielkosc"] = info;
   system("cls");

   cout<<"Podaj opis krolowej: "<<endl;
   getline(cin, info);
   nowyGatunek["Krolowa"]["Opis"] = info;
   system("cls");

   cout<<"Podaj ile jaj dziennie sklada krolowa: "<<endl;
   getline(cin, info);
   nowyGatunek["Krolowa"]["Dzienna_ilosc_skladanych_jaj"] = info;
   system("cls");

   cout<<"Podaj opis zolnierza: "<<endl;
   getline(cin, info);
   nowyGatunek["Zolnierz"]["Opis"] = info;
   system("cls");

   cout<<"Podaj zasisk szczek zolnierza (od 1 do 10):"<<endl;
   getline(cin, info);
   nowyGatunek["Zolnierz"]["Zacisk szczek"] = info;
   system("cls");

   cout<<"Podaj ilosc zycia zolnierza (od 1 do 100):"<<endl;
   getline(cin, info);
   nowyGatunek["Zolnierz"]["Ilosc zycia"] = info;
   system("cls");

   cout<<"Podaj atak zolnierza  (od 1 do 100):"<<endl;
   getline(cin, info);
   nowyGatunek["Zolnierz"]["Atak"] = info;
   system("cls");

   cout<<"Podaj opis robotnicy: "<<endl;
   getline(cin, info);
   nowyGatunek["Robotnica"]["Opis"] = info;
   system("cls");

   cout<<"Podaj jakie obciazenie jest w stanie uniesc robotnica(x razy wieksze od masy jej ciala): "<<endl;
   getline(cin, info);
   nowyGatunek["Robotnica"]["Obciazenie"] = info;
   system("cls");


   json_handler->dodaj(nowyGatunek, nazwa);

}


bool SpisTresc::usunIstniejacyGatunek(int numer_gatunku)
 {
     vector <string> lista_gatunkow = json_handler ->pobierz_gatunki_mrowek();
     (*json_handler)-=lista_gatunkow[numer_gatunku];
     return true;
 }



void SpisTresc::wyswietlSzczegolyGatunku(int numerGatunku, const string typ_mrowki) const
{
    vector <string> lista_gatunkow = json_handler ->pobierz_gatunki_mrowek();
    json info_szczegolowe = (*json_handler)[lista_gatunkow[numerGatunku]];



    cout<<green<<"Srodowisko: "<<reset<<info_szczegolowe["Srodowisko"].template get<string> ()<<endl;
    cout<<green<<"Ciekawostka: "<<reset<<info_szczegolowe["Ciekawostka"].template get<string> ()<<endl;
    cout<<green<<"Czy ten gatunek jest pod ochrona: "<<reset<<info_szczegolowe["Czy_jest_pod_ochrona"].template get<string> ()<<endl;

    cout<<green<<"Opis wybranej kasty: "<<reset<<info_szczegolowe[typ_mrowki]["Opis"].template get<string> ()<<endl;
    if(typ_mrowki == "Krolowa")
        {
            cout<<green<<"Dzienna ilosc skladanych jaj: "<<reset<<info_szczegolowe[typ_mrowki]["Dzienna_ilosc_skladanych_jaj"].template get<string> ()<<endl;
            cout<<green<<"Wielokosc(w mm): "<<reset<<info_szczegolowe[typ_mrowki]["Wielkosc"].template get<string> ()<<endl;
        }

    else if(typ_mrowki == "Zolnierz")
        {
            cout<<green<<"Zacisk szczek (od 1-10): "<<reset<<info_szczegolowe[typ_mrowki]["Zacisk szczek"].template get<string> ()<<" Strength"<< endl;
            cout<<green<<"Ilosc zycia zolnierza (od 1-100): "<<reset<<info_szczegolowe[typ_mrowki]["Ilosc zycia"].template get<string> ()<<" Health"<<endl;
            cout<<green<<"Atak zolnierza (od 1-100): "<<reset<<info_szczegolowe[typ_mrowki]["Atak"].template get<string> ()<<" Damage"<<endl;
        }

    else if(typ_mrowki == "Robotnica")
        {
            cout<<green<<"Obciazenie jakie moze przeniesc robotnica w odwolaniu do wlasnego ciala: "<<reset<<info_szczegolowe[typ_mrowki]["Obciazenie"].template get<string> ()<<endl;
        }
}

void SpisTresc::walka(const string imie1, const string imie2, const int mrowka1, const int mrowka2)
{
    json mrowka1_dane = (*json_handler)[json_handler->pobierz_gatunki_mrowek()[mrowka1]]["Zolnierz"];
    json mrowka2_dane = (*json_handler)[json_handler->pobierz_gatunki_mrowek()[mrowka2]]["Zolnierz"];
    int licznik1 = 0;
    int licznik2 = 0;
    int a1, a2, b1, b2, c1, c2;

    if(mrowka1_dane["Atak"] > mrowka2_dane["Atak"])
    {
        licznik1 ++;
        a1 = 1;
        a2 = 0;
    }
    else
    {
        licznik2 ++;
        a1 = 0;
        a2= 1;
    }

        if(mrowka1_dane["Ilosc zycia"] > mrowka2_dane["Ilosc zycia"])
    {
        licznik1 ++;
        b1= 1;
        b2 = 0;
    }
    else
    {
        licznik2 ++;
        b1 = 0;
        b2 = 1;
    }

        if(mrowka1_dane["Zacisk szczek"] > mrowka2_dane["Zacisk szczek"])
    {
        licznik1 ++;
        c1 = 1;
        c2 = 0;
    }
    else
    {
        licznik2 ++;
        c1 = 0;
        c2 = 1;
    }

    if(licznik1 > licznik2)
    {
        cout<<green<<"Wygral "<<imie1<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka1]<<" z wynikiem: "<<licznik1<<" : "<<licznik2<<reset<<endl;
        cout<<red<<"Przegral "<<imie2<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka2]<<" z wynikiem: "<<licznik2<<" : "<<licznik1<<reset<<endl;
    }
    else
    {
        cout<<green<<"Wygral "<<imie2<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka2]<<" z wynikiem: "<<licznik2<<" : "<<licznik1<<reset<<endl;
        cout<<red<<"Przegral "<<imie1<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka1]<<" z wynikiem: "<<licznik1<<" : "<<licznik2<<reset<<endl;
    }

    cout<<"<-------WYNIKI:------->"<<endl;
    cout<<imie1<<": "<<endl;
    if(a1 == 1)
    {
        cout<<"Atak: Wygral"<<endl;
    }
    else
    {
        cout<<"Atak: Przegral"<<endl;
    }
        if(b1 == 1)
    {
        cout<<"Ilosc zycia: Wygral"<<endl;
    }
    else
    {
        cout<<"Ilosc zycia: Przegral"<<endl;
    }
            if(c1 == 1)
    {
        cout<<"Zacisk szczek: Wygral"<<endl;
    }
    else
    {
        cout<<"Zacisk szczek: Przegral"<<endl;
    }
cout<<"-----------------------"<<endl;
cout<<imie2<<": "<<endl;
 if(a2 == 1)
    {
        cout<<"Atak: Wygral"<<endl;
    }
    else
    {
        cout<<"Atak: Przegral"<<endl;
    }
        if(b2 == 1)
    {
        cout<<"Ilosc zycia: Wygral"<<endl;
    }
    else
    {
        cout<<"Ilosc zycia: Przegral"<<endl;
    }
            if(c2 == 1)
    {
        cout<<"Zacisk szczek: Wygral"<<endl;
    }
    else
    {
        cout<<"Zacisk szczek: Przegral"<<endl;
    }
    cout<<"-----------------------"<<endl;
    ofstream zapis_wyniku("zapis_wyniku.txt");
    zapis_wyniku<<"<--------------------------->"<<endl;
    zapis_wyniku<<"=== Walka odbyla sie pomiedzy graczem: "<<imie1<<", a graczem: "<<imie2<<". ==="<<endl;
    zapis_wyniku<<endl;
    zapis_wyniku<<"Gracz: "<<imie1<<", wybral gatunek: "<<json_handler->pobierz_gatunki_mrowek()[mrowka1]<<endl;
    zapis_wyniku<<"Statystyki "<<json_handler->pobierz_gatunki_mrowek()[mrowka1]<<":"<<endl;
    zapis_wyniku<<"Atak: "<<mrowka1_dane["Atak"].template get<string> ()<<" Damage"<<endl;
    zapis_wyniku<<"Ilosc zycia: "<<mrowka1_dane["Ilosc zycia"].template get<string> ()<<" Health"<<endl;
    zapis_wyniku<<"Zacisk szczek: "<<mrowka1_dane["Zacisk szczek"].template get<string> ()<<" Strength"<<endl;
    zapis_wyniku<<endl;
    zapis_wyniku<<"Gracz: "<<imie2<<", wybral gatunek: "<<json_handler->pobierz_gatunki_mrowek()[mrowka2]<<endl;
    zapis_wyniku<<"Statystyki "<<json_handler->pobierz_gatunki_mrowek()[mrowka2]<<":"<<endl;
    zapis_wyniku<<"Atak: "<<mrowka2_dane["Atak"].template get<string> ()<<" Damage"<<endl;
    zapis_wyniku<<"Ilosc zycia: "<<mrowka2_dane["Ilosc zycia"].template get<string> ()<<" Health"<<endl;
    zapis_wyniku<<"Zacisk szczek: "<<mrowka2_dane["Zacisk szczek"].template get<string> ()<<" Strength"<<endl;
    zapis_wyniku<<endl;

    if(a1 == 1)
    {
        zapis_wyniku<<"Atak: Wygral gracz: "<<imie1<<endl;
    }
    else
    {
        zapis_wyniku<<"Atak: Wygral gracz: "<<imie2<<endl;
    }
        if(b1 == 1)
    {
        zapis_wyniku<<"Ilosc zycia: Wygral gracz: "<<imie1<<endl;
    }
    else
    {
        zapis_wyniku<<"Ilosc zycia: Wygral gracz: "<<imie2<<endl;
    }
            if(c1 == 1)
    {
        zapis_wyniku<<"Zacisk szczek: Wygral gracz: "<<imie1<<endl;
    }
    else
    {
        zapis_wyniku<<"Zacisk szczek: Wygral gracz: "<<imie2<<endl;
    }

    zapis_wyniku<<endl;

        if(licznik1 > licznik2)
    {
        zapis_wyniku<<"Wygral "<<imie1<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka1]<<" z wynikiem: "<<licznik1<<" : "<<licznik2<<endl;
        zapis_wyniku<<"Przegral "<<imie2<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka2]<<" z wynikiem: "<<licznik2<<" : "<<licznik1<<endl;
    }
    else
    {
        zapis_wyniku<<"Wygral "<<imie2<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka2]<<" z wynikiem: "<<licznik2<<" : "<<licznik1<<endl;
        zapis_wyniku<<"Przegral "<<imie1<<" grajacy mrowka z gatunku "<<json_handler->pobierz_gatunki_mrowek()[mrowka1]<<" z wynikiem: "<<licznik1<<" : "<<licznik2<<endl;
    }
    zapis_wyniku<<"<--------------------------->"<<endl;

    logowanie_walka("Walka zakonczyla sie");
    ZapiszWalkeDoHistori();

}
