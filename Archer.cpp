#include "Archer.h"

Archer::Archer(sf::RenderWindow* window) {
    loadCharacter("lucznik1a.png", {static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2});
}

void Archer::poruszanie(float deltaTime) {
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sprite.move(0, -speed * deltaTime);
        lastDirection = Direction::Up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sprite.move(0, speed * deltaTime);
        lastDirection = Direction::Down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * deltaTime, 0);
        sprite.setScale(-0.15f, 0.15f);
        lastDirection = Direction::Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * deltaTime, 0);
        sprite.setScale(0.15f, 0.15f);
        lastDirection = Direction::Right;
    }
    clampToWindow();
}

void Archer::update() {}

sf::Drawable& Archer::getDrawable() { return sprite; }
sf::Sprite& Archer::getSprite() { return sprite; }
Direction Archer::getLastDirection() const { return lastDirection; }
void Archer::setWindow(sf::RenderWindow* win) { CharacterLoader::setWindow(win); }

