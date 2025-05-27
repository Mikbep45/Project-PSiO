#include "obrazy.h"
#include <iostream>

void Obraz::WyswietlObraz(const std::string& plikObraz)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zdjecie mrowki:");
    sf::Texture texture;


    if (!texture.loadFromFile(plikObraz))
      {
        std::cerr << "Blad: nie znaleziono takiego zdjecia! " << plikObraz << std::endl;
        return;
      }

    sf::Sprite sprite;
    sprite.setTexture(texture);


    sf::Vector2u textureSize = texture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    float scale = std::min(scaleX, scaleY);
    sprite.setScale(scale, scale);


    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sprite.setPosition((windowSize.x - spriteBounds.width) / 2, (windowSize.y - spriteBounds.height) / 2);

    while (window.isOpen())
     {
        sf::Event event;
        while (window.pollEvent(event))
          {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                window.close();
          }

        window.clear();
        window.draw(sprite);
        window.display();
     }
}

