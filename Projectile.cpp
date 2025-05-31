#include "Projectile.h"

Projectile::Projectile(std::shared_ptr<sf::Texture> tex, sf::Vector2f startPos, Direction direction)
    : texture(std::move(tex)), dir(direction) {
    sprite.setTexture(*texture);
    sprite.setScale(0.1f, 0.1f);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(startPos);

    switch (dir) {
        case Direction::Right: sprite.setRotation(0.f); break;
        case Direction::Left:  sprite.setRotation(180.f); break;
        case Direction::Up:    sprite.setRotation(270.f); break;
        case Direction::Down:  sprite.setRotation(90.f); break;
    }
}

void Projectile::update(float deltaTime) {
    switch (dir) {
        case Direction::Right: sprite.move(speed * deltaTime, 0); break;
        case Direction::Left:  sprite.move(-speed * deltaTime, 0); break;
        case Direction::Up:    sprite.move(0, -speed * deltaTime); break;
        case Direction::Down:  sprite.move(0, speed * deltaTime); break;
    }
}

sf::Drawable& Projectile::getDrawable() { return sprite; }
sf::FloatRect Projectile::getBounds() const { return sprite.getGlobalBounds(); }
