#include "CharacterLoader.h"

// Implementacja metody loadCharacter
void CharacterLoader::loadCharacter(const std::string& filename, sf::Vector2f startPos, sf::Vector2f scale) {
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    sprite.setTexture(texture);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, 0); // ustawienie œrodka w poziomie
    sprite.setScale(scale);
    sprite.setPosition(startPos);
}

// Implementacja metody clampToWindow
void CharacterLoader::clampToWindow() {
    if (!windowPtr) return;
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();

    float minX = bounds.width / 2;
    float maxX = windowPtr->getSize().x - bounds.width / 2;
    float minY = 0;
    float maxY = windowPtr->getSize().y - bounds.height;

    pos.x = std::max(minX, std::min(maxX, pos.x));
    pos.y = std::max(minY, std::min(maxY, pos.y));
    sprite.setPosition(pos);
}

// Implementacja metody setWindow
void CharacterLoader::setWindow(sf::RenderWindow* win) {
    windowPtr = win;
}
