#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Projectile {
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    float speed = 500.f;
    Direction dir;

public:
    Projectile(std::shared_ptr<sf::Texture> tex, sf::Vector2f startPos, Direction direction);
    void update(float deltaTime);
    sf::Drawable& getDrawable();
    sf::FloatRect getBounds() const;
};
