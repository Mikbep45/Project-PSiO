#include "HealthBar.h"

HealthBar::HealthBar(float width, float height) {
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(50, 50, 50));  // Ciemne t³o dla paska zdrowia

    bar.setSize(sf::Vector2f(width, height));
    bar.setFillColor(sf::Color::Green);  // Kolor paska zdrowia (zielony)
}

void HealthBar::update(float healthPercentage) {
    bar.setSize(sf::Vector2f(background.getSize().x * healthPercentage, background.getSize().y));
}

void HealthBar::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    background.setPosition(position);
    bar.setPosition(position);
    window.draw(background);
    window.draw(bar);
}
