#pragma once

#include <SFML/Graphics.hpp>

enum class Direction { Left, Right, Up, Down };

class Character {
public:
    virtual void poruszanie(float deltaTime) = 0;
    virtual void update() = 0;
    virtual sf::Drawable& getDrawable() = 0;
    virtual sf::Sprite& getSprite() = 0;
    virtual void setWindow(sf::RenderWindow* win) = 0;
    virtual ~Character() {}
};
