#pragma once
#include <iostream>
#include <conio.h>
#include "SpisTresci.h"
#include "loging.h"
#include "quiz_mrowki.h"
#include <windows.h>
#include "symulacjaA.h"
#include "obrazy.h"
#include <direct.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "klasa_zmianowa.h"

using namespace std;

enum Wybor {lista_mrowek = '1', dodawanie_gatunku = '2', usuwanie_gatunku = '3', informacje = '4', gra = '5', quiz = '6', symulacja = '7', zdjecia = '8', wyjscie = '0'};

class Glowna_klasa : public Loging
{
  private:
     Wybor choice;
     SpisTresc spis;
     const string green = "\033[32m";
     const string red = "\033[31m";
     const string yellow = "\033[33m";
     const string reset = "\033[0m";
     const string turkus = "\033[1;96m";

  public:
     Glowna_klasa() : Loging()
     {
         logowanie("INFO", "=== START PROGRAMU ===");
     }

     ~Glowna_klasa()
     {
         logowanie("INFO", "=== ZAMKNIECIE PROGRAMU ===");
     }

     void displaySpecies()
 {
     system("cls");
     logowanie("INFO", "Wyswietlenie listy gatunkow mrowek");
     spis.wyswietlGatunki_mrowek();
     cout<<"Aby kontynuowac wcisnij dowolny przycisk!"<<endl;
     getch();

 }
void addSpecies()
 {
     system("cls");
     logowanie("INFO", "Dodawanie nowego gatunku mrowek");
     spis.dodajNowyGatunek_mrowek();
     cout<<"Aby kontynuowac wcisnij dowolny przycisk!"<<endl;
     getch();


 }
void removeSpecies()
 {
     system("cls");
     spis.wyswietlGatunki_mrowek();
     int numer_do_usuniecia;
     cout<<"Podaj numer gatunku, ktory zostanie usuniety z bazy danych: "<<endl;
     cin>>numer_do_usuniecia;
     system("cls");
     if(spis.usunIstniejacyGatunek(numer_do_usuniecia - 1))
        {
            cout<<"Gatunek zostal pomyslnie usuniety z bazy danych"<<endl;
            logowanie("INFO", "Usuwanie istniejacego gatunku mrowek z listy");
        }
     else
        {
            cout<<red<<"Niepoprawny numer gatunku"<<reset<<endl;
            logowanie("Critical Error", "Usuwanie istniejacego gatunku mrowek z listy nie powiodlo sie");
        }
    cout<<"Aby kontynuowac wcisnij dowolny przycisk!"<<endl;
    getch();

 }
void showInfo()
 {
     system("cls");
     logowanie("INFO", "Wyswietlnie szczegolowych informacji o wybranym gatunku mrowek");
     spis.wyswietlGatunki_mrowek();
     cout<<"Wpisz numer gatunku, aby wyswietlic szczegolowe informacje o nim: "<<endl;
     int wybrany, typ;
     cin>>wybrany;
     system("cls");
     cout<<"Wybierz typ mrowki, na ktorej chcesz uzuskac wiecej informacji: "<<endl;
     cout<<green<<"[1]"<<reset<<" <-- Krolowa"<<endl;
     cout<<green<<"[2]"<<reset<<" <-- Zolnierz"<<endl;
     cout<<green<<"[3]"<<reset<<" <-- Robotnica"<<endl;
     cin>>typ;
     system("cls");
     switch(typ)
     {
         case 1:
            {
                logowanie("INFO", "Wybrano krolowa");
                spis.wyswietlSzczegolyGatunku(wybrany-1, "Krolowa");
                break;
            }
         case 2:
             {
                logowanie("INFO", "Wybrano zolnierza");
                spis.wyswietlSzczegolyGatunku(wybrany-1, "Zolnierz");
                break;
             }
         case 3:
             {
                logowanie("INFO", "Wybrano robotnice");
                spis.wyswietlSzczegolyGatunku(wybrany -1, "Robotnica");
                break;
             }

         default:
             {
               logowanie("Critical Error", "Wybrano nie istniejaca opcje typu mrowki(Krolowa/Zolnierz/Robotnica)");
               cout<<red<<"Niepoprawny numer"<<reset<<endl;
               break;
             }
       }
   cout<<"Aby kontynuowac wcisnij dowolny przycisk!"<<endl;
   getch();

 }
void startQuiz()
  {
      system("cls");
      logowanie("INFO", "Uruchomienie quizu o mrowkach");
           {
              QuizMrowki quiz("quiz.txt");
              quiz.uruchomQuiz();
           }
      PlaySound(TEXT("klaskanie.wav"), NULL, SND_ASYNC | SND_ASYNC);
      cout<<"Aby kontynuowac wcisnij dowolny przycisk!"<<endl;
      getch();

  }
void startGame1()
  {
      system("cls");
      logowanie("INFO", "Rozpoczeto mini-gre");
      string imie1, imie2;
      cout<<turkus<<"Podaj nick pierwszego gracza: "<<reset;
      cin>>imie1;
      system("cls");
      cout<<turkus<<"Podaj nick drugiego gracza: "<<reset;
      cin>>imie2;
      system("cls");
      spis.wyswietlGatunki_mrowek();
      cout<<turkus<<imie1<<" wybiera gatunek: "<<reset;
      int gat1, gat2;
      cin>>gat1;
      system("cls");
      spis.wyswietlGatunki_mrowek();
      cout<<turkus<<imie2<<" wybiera gatunek: "<<reset;
      cin>>gat2;
      system("cls");
      spis.walka(imie1, imie2, gat1-1, gat2-1);
      PlaySound(TEXT("game.wav"), NULL, SND_ASYNC | SND_ASYNC);
//
//
       cout<<"Aby wyswietlic szczegolowe informacje na temat walki wcisnij: [K]"<<endl;
       cout<<"Aby kontynuowac wcisnij dowolny przycisk (Z wyjatkiem k lub K)"<<endl;
       char special;
       special = _getch();
       if(special == 'k' || special == 'K')
           {
               system("cls");
               ifstream file("zapis_wyniku.txt");
       if (!file)
            {
               cerr <<red<<"Nie udalo sie otworzyc pliku!"<<reset<< endl;
            }

       string line;
       while (getline(file, line))
            {
               cout << line << endl;
            }

               file.close();
            }


  }
void runSimulation()
  {
       system("cls");
       cout<<"Trwa symulacja..."<<endl;
       AntSimulation simulation;
       simulation.run();

  }
void startGame2()
  {
    std::cout << "[AKCJA] Gra 2 startuje...\n";
  }
void showImage()
  {
      system("cls");
      const int numerZdjecia = 9;
      string tablicaZdjec[numerZdjecia] = {
        "z1.jpg",
        "z2.jpg",
        "z3.jpg",
        "z4.jpg",
        "z5.jpg",
        "z6.jpg",
        "z7.jpg",
        "z8.jpg",
        "z9.jpg"
         };

      while (true)
        {
             wyborZdjecia();
             int choice;


             if (!(cin>>choice))
                  {
                       cout << "Niepoprawne dane. Wprowadz liczbe calkowita." << endl;
                       cin.clear();
                       cin.ignore(numeric_limits<streamsize>::max(), '\n');
                       continue;
                  }

             if (choice == 0)
                  {
                      break;
                  }

             if (choice >= 1 && choice <= numerZdjecia)
                   {
                       Obraz().WyswietlObraz(tablicaZdjec[choice - 1]);
                       cout<<"Czy ustawic te zdjecie na tapete?"<<endl;
                       cout<<"[T] <-- Tak"<<endl;
                       cout<<"[N] <-- Nie"<<endl;
                       char potwierdzenie;
                       cin>>potwierdzenie;
                       if(potwierdzenie == 'T')
                            {
                                 system("cls");
                                 char tablica[1024];
                                 getcwd(tablica, 1024);
                                 string sciezka_do_plika = tablica;
                                 sciezka_do_plika = sciezka_do_plika + "\\z"+to_string(choice)+ ".jpg";
                                 SystemParametersInfo(SPI_SETDESKWALLPAPER, 0,(PVOID)sciezka_do_plika.c_str(), SPIF_UPDATEINIFILE);
                                 cout<<"Tapeta zmieniona pomyslnie!"<<endl;
                            }

                       }
              else
             {
               cout << "Niepoprawny numer. Wprowadz liczbe od 1 do 9." << endl;
               system("cls");
          }
         }
  }

// === STRUKTURA PRZYCISKU ===

struct CapsuleButton
{
    sf::RectangleShape body;
    sf::CircleShape leftCap, rightCap;
    sf::RectangleShape shadowRect;
    sf::CircleShape shadowLeft, shadowRight;
    sf::Text label;

    sf::Color baseColor;
    float x, y, width, height, radius;

    bool hidden = false;
    sf::Clock hideClock;

    void setup(float _x, float _y, float _width, float _height, const sf::Font& font, const std::string& text, sf::Color color)
    {
        x = _x; y = _y; width = _width; height = _height;
        radius = height / 2.f;
        baseColor = color;

        sf::Vector2f offset(4.f, 4.f);
        shadowRect.setSize(sf::Vector2f(width - 2 * radius, height));
        shadowRect.setFillColor(sf::Color(50, 50, 50, 100));
        shadowRect.setPosition(x - width / 2.f + radius + offset.x, y - height / 2.f + offset.y);

        shadowLeft.setRadius(radius);
        shadowLeft.setFillColor(sf::Color(50, 50, 50, 100));
        shadowLeft.setPosition(x - width / 2.f + offset.x, y - height / 2.f + offset.y);

        shadowRight.setRadius(radius);
        shadowRight.setFillColor(sf::Color(50, 50, 50, 100));
        shadowRight.setPosition(x + width / 2.f - 2 * radius + offset.x, y - height / 2.f + offset.y);

        body.setSize(sf::Vector2f(width - 2 * radius, height));
        body.setFillColor(baseColor);
        body.setPosition(x - width / 2.f + radius, y - height / 2.f);

        leftCap.setRadius(radius);
        leftCap.setFillColor(baseColor);
        leftCap.setPosition(x - width / 2.f, y - height / 2.f);

        rightCap.setRadius(radius);
        rightCap.setFillColor(baseColor);
        rightCap.setPosition(x + width / 2.f - 2 * radius, y - height / 2.f);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(24);
        label.setFillColor(sf::Color::Black);

        sf::FloatRect bounds=label.getLocalBounds();
        label.setPosition(x - bounds.width / 2.f - bounds.left, y - bounds.height / 2.f - bounds.top);
    }

    void draw(sf::RenderWindow& window)
    {
        if(hidden)return;
        window.draw(shadowRect);
        window.draw(shadowLeft);
        window.draw(shadowRight);
        window.draw(body);
        window.draw(leftCap);
        window.draw(rightCap);
        window.draw(label);
    }

    bool contains(sf::Vector2f point)const
    {
        if(hidden)return false;
        sf::FloatRect bounds(x - width / 2.f, y - height / 2.f, width, height);
        return bounds.contains(point);
    }

    void setColor(sf::Color color)
    {
        baseColor = color;
        body.setFillColor(color);
        leftCap.setFillColor(color);
        rightCap.setFillColor(color);
    }
};


// === DRUGIE OKNO ===
void runSecondWindow() {
    const int windowWidth = 1536, windowHeight = 1024;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "World of Ants - Gra");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("tlo2.png")) {
        std::cerr<<red<<"Nie mozna zaladowac tla (tlo2.png)!\n"<<reset;
        return;
    }
    sf::Sprite background(backgroundTexture);

    sf::Font font;
    if (!font.loadFromFile("Arial-ItalicMT.ttf")) {
        std::cerr << "Nie mozna zaladowac czcionki!\n";
        return;
    }

    std::vector<std::string> buttonLabels = {
        "Wyswietl gatunki", "Dodaj gatunek", "Usun gatunek", "Wyswielt informacje",
        "Quiz", "Gra 1", "Symulacja", "Gra 2", "Obraz", "Wyjdz z programu"
    };

    std::vector<CapsuleButton> buttons(10);

    const float buttonWidth = 300, buttonHeight = 60, hSpacing = 100, vSpacing = 40;
    float gridStartX = (windowWidth - (3 * buttonWidth + 2 * hSpacing)) / 2.f;
    float gridStartY = 320.f;

    for (int i = 0; i < 9; ++i) {
        int row = i / 3, col = i % 3;
        float x = gridStartX + col * (buttonWidth + hSpacing) + buttonWidth / 2.f;
        float y = gridStartY + row * (buttonHeight + vSpacing) + buttonHeight / 2.f;
        buttons[i].setup(x, y, buttonWidth, buttonHeight, font, buttonLabels[i], sf::Color(0, 180, 0));
    }

    float lastRowY = gridStartY + 2 * (buttonHeight + vSpacing);
    float button10Y = lastRowY + buttonHeight + vSpacing + buttonHeight / 2.f;
    buttons[9].setup(windowWidth / 2.f, button10Y, buttonWidth, buttonHeight, font, buttonLabels[9], sf::Color(200, 50, 50));

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for(int i=0;i<10;++i)
                {
                    if(buttons[i].contains(mousePos))
                    {
                        std::cout<<"Kliknieto: "<<buttonLabels[i]<<std::endl;

                        buttons[i].hidden = true;
                        buttons[i].hideClock.restart();

                        window.close();

                        switch(i)
                        {
                            case 0: displaySpecies(); break;
                            case 1: addSpecies(); break;
                            case 2: removeSpecies(); break;
                            case 3: showInfo(); break;
                            case 4: startQuiz(); break;
                            case 5: startGame1(); break;
                            case 6: runSimulation(); break;
                            case 7: startGame2(); break;
                            case 8: showImage(); break;
                            case 9:
                                return;
                        }

                        runSecondWindow();
                        return;
                    }
                }
            }
        }

        // Automatyczne pokazywanie ukrytych przycisków po 1 sekundzie
        for(auto& button : buttons){if(button.hidden && button.hideClock.getElapsedTime().asSeconds() >= 1.0f){button.hidden = false;}}

        // Efekt uniesienia przycisku pod kursorem
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        for(int i = 0; i < buttons.size(); ++i)
        {
            if(buttons[i].hidden) continue;

            if(buttons[i].contains(mousePos)){buttons[i].setColor(sf::Color::White);}
            else
            {
                if(i == 9){buttons[i].setColor(sf::Color(200, 50, 50));}
                else{buttons[i].setColor(sf::Color(0, 180, 0));}
            }
        }

        window.clear();
        window.draw(background);
        for (auto& button : buttons){button.draw(window);}
        window.display();
    }
}



    // === GŁÓWNA FUNKCJA APLIKACJI ===

    void startApp()
    {
        const int windowWidth = 1536;
        const int windowHeight = 1024;
        const int buttonWidth = 400;
        const int buttonHeight = 60;
        const int spacing = 50;

        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "World of Ants - Menu");
        window.setFramerateLimit(60);

        sf::Texture backgroundTexture;
        if(!backgroundTexture.loadFromFile("tlo.png"))
        {
            std::cerr<<red<<"Nie mozna zaladowac tla (tlo.png)!"<<reset<<std::endl;
            return;
        }
        sf::Sprite background(backgroundTexture);

        sf::Font font;
        if(!font.loadFromFile("Arial-ItalicMT.ttf"))
        {
            std::cerr<<red<<"Nie mozna zaladowac czcionki!"<<reset<<std::endl;
            return;
        }

        float totalWidth = buttonWidth * 2 + spacing;
        float leftOffset = (windowWidth - totalWidth) / 2.f;
        float buttonY = (windowHeight - buttonHeight) / 2.f + 100;

        sf::RectangleShape startButton(sf::Vector2f(buttonWidth, buttonHeight));
        startButton.setFillColor(sf::Color(0, 180, 0));
        startButton.setPosition(leftOffset, buttonY);

        sf::Text startLabel("Start", font, 28);
        startLabel.setFillColor(sf::Color::White);
        sf::FloatRect startBounds = startLabel.getLocalBounds();
        startLabel.setPosition(
        startButton.getPosition().x + (buttonWidth - startBounds.width) / 2 - startBounds.left,
        startButton.getPosition().y + (buttonHeight - startBounds.height) / 2 - startBounds.top
        );

        sf::RectangleShape quitButton(sf::Vector2f(buttonWidth, buttonHeight));
        quitButton.setFillColor(sf::Color(200, 50, 50));
        quitButton.setPosition(leftOffset + buttonWidth + spacing, buttonY);

        sf::Text quitLabel("Zakoncz program", font, 28);
        quitLabel.setFillColor(sf::Color::White);
        sf::FloatRect quitBounds = quitLabel.getLocalBounds();
        quitLabel.setPosition(
        quitButton.getPosition().x + (buttonWidth - quitBounds.width) / 2 - quitBounds.left,
        quitButton.getPosition().y + (buttonHeight - quitBounds.height) / 2 - quitBounds.top
        );

        while(window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                window.close();

                if(event.type == sf::Event::MouseButtonPressed &&event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    if(startButton.getGlobalBounds().contains(mousePos))
                    {
                        std::cout << "Kliknieto: Start" << std::endl;
                        window.close();
                        runSecondWindow();
                    }

                    if(quitButton.getGlobalBounds().contains(mousePos))
                    {
                        std::cout << "Kliknieto: Zakoncz program" << std::endl;
                        window.close();
                    }
                }
            }

            window.clear();
            window.draw(background);
            window.draw(startButton);
            window.draw(startLabel);
            window.draw(quitButton);
            window.draw(quitLabel);
            window.display();
        }
    }

    void wyborZdjecia()
    {
        cout<<"Wybierz gatunek ktorego, zdjecie chcesz wyswietlic: "<<endl;
        cout<<turkus<<"[1]"<<reset<<" <-- Camponotus Maculatus Subnodus"<<endl;
        cout<<turkus<<"[2]"<<reset<<" <-- Camponotus barbaricus"<<endl;
        cout<<turkus<<"[3]"<<reset<<" <-- Lasius Niger"<<endl;
        cout<<turkus<<"[4]"<<reset<<" <-- Lasius Flavus"<<endl;
        cout<<turkus<<"[5]"<<reset<<" <-- Formica Sanguinea"<<endl;
        cout<<turkus<<"[6]"<<reset<<" <-- Formica Fusca"<<endl;
        cout<<turkus<<"[7]"<<reset<<" <-- Pheidole Megacephala"<<endl;
        cout<<turkus<<"[8]"<<reset<<" <-- Camponotus Pilicornis"<<endl;
        cout<<turkus<<"[9]"<<reset<<" <-- Messor Barbarus"<<endl;
        cout<<yellow<<"[0]"<<reset<<" <-- Powrot do Menu Glownego"<<endl;
    }
};
