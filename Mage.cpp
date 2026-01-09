#include "Mage.h"

Mage::Mage(sf::RenderWindow* window) {
    loadCharacter("mag1.png", {static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2});
}

void Mage::poruszanie(float deltaTime) {
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move(0, -speed * deltaTime);
        lastDirection = Direction::Up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0, speed * deltaTime);
        lastDirection = Direction::Down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move(-speed * deltaTime, 0);
        sprite.setScale(0.15f, 0.15f);
        lastDirection = Direction::Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(speed * deltaTime, 0);
        sprite.setScale(-0.15f, 0.15f);
        lastDirection = Direction::Right;
    }
    clampToWindow();
}

void Mage::update() {}

sf::Drawable& Mage::getDrawable() { return sprite; }
sf::Sprite& Mage::getSprite() { return sprite; }
Direction Mage::getLastDirection() const { return lastDirection; }
void Mage::setWindow(sf::RenderWindow* win) { CharacterLoader::setWindow(win); }

