#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <stdexcept>

class CharacterLoader {
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RenderWindow* windowPtr = nullptr;

    void loadCharacter(const std::string& filename, sf::Vector2f startPos, sf::Vector2f scale = {0.15f, 0.15f});
    void clampToWindow();

public:
    sf::Sprite& getSprite();
    void setWindow(sf::RenderWindow* win);
    void clampPosition();
};
