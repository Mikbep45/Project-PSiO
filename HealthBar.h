#pragma once

#include <SFML/Graphics.hpp>

class HealthBar {
public:
    sf::RectangleShape background;
    sf::RectangleShape bar;

    HealthBar(float width, float height);
    void update(float healthPercentage);
    void draw(sf::RenderWindow& window, const sf::Vector2f& position);
};
