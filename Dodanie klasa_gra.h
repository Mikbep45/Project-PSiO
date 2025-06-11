#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>


#include "CharacterLoader.h"
//#include "CharacterLoader.cpp"
#include "Character.h"
#include "Mage.h"
//#include "Mage.cpp"
//#include "Archer.cpp"
#include "Archer.h"
//#include "Projectile.cpp"
#include "Projectile.h"
//#include "HealthBar.cpp"
#include "HealthBar.h"
//#include "Heart.cpp"
#include "Heart.h"
//#include "Ant.cpp"
#include "Ant.h"



class Gra2
{
private:

        void playBackgroundMusic(const std::string& filename, bool stopCurrent = false) {
    if (stopCurrent) {
        PlaySound(NULL, NULL, 0);  // Zatrzymanie obecnej muzyki
    }
    PlaySound(TEXT(filename.c_str()), NULL, SND_ASYNC | SND_LOOP);  // Odtwarzanie w tle w pêtli
}

bool allHeartsGray(const std::vector<Heart>& hearts) {
    for (const auto& heart : hearts) {
        if (!heart.isGray) {  // Jeœli przynajmniej jedno serce nie jest szare
            return false;
        }
    }
    return true;
}

bool allAntsDead(const std::vector<Ant>& ants) {
    return ants.empty(); // Zwraca true, jeœli lista mrówek jest pusta
}

bool checkGameOver(sf::RenderWindow& window, const std::vector<Heart>& mageHearts, const std::vector<Heart>& archerHearts)
{
    if (allHeartsGray(mageHearts) || allHeartsGray(archerHearts)) {
        window.close();

        playBackgroundMusic("background_music.wav", true);
        PlaySound(TEXT("game.wav"), NULL, SND_ASYNC);

        sf::RenderWindow endWindow(sf::VideoMode(1536, 1024), "Game Over");
        sf::Texture endTexture;
        if (!endTexture.loadFromFile("koniec.png")) return false;
        sf::Sprite endBackground(endTexture);

        while (endWindow.isOpen()) {
            sf::Event endEvent;
            while (endWindow.pollEvent(endEvent)) {
                if (endEvent.type == sf::Event::Closed) endWindow.close();
            }


            endWindow.clear();
            endWindow.draw(endBackground);
            endWindow.display();
        }

        return true;
    }
    return false;
}


public:
    int startGame();


};
