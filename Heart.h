#pragma once

#include <SFML/Graphics.hpp>

class Heart {
public:
    sf::Sprite sprite;
    sf::Vector2f position;
    bool isGray = false;

    Heart(sf::Texture& texture, sf::Vector2f pos);
    sf::Drawable& getDrawable();
    void changeToGray(sf::Texture& grayTexture);
};
