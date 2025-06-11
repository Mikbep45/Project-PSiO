#pragma once

#include "Character.h"
#include "CharacterLoader.h"

class Mage : public Character, public CharacterLoader {
    Direction lastDirection = Direction::Right;

public:
    Mage(sf::RenderWindow* window);
    void poruszanie(float deltaTime) override;
    void update() override;
    sf::Drawable& getDrawable() override;
    sf::Sprite& getSprite() override;
    Direction getLastDirection() const;
    void setWindow(sf::RenderWindow* win) override;
};
