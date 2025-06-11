#include "Heart.h"

Heart::Heart(sf::Texture& texture, sf::Vector2f pos) {
    sprite.setTexture(texture);
    sprite.setScale(0.05f, 0.05f);  // Zwiêkszenie skali serca
    sprite.setPosition(pos);
}

sf::Drawable& Heart::getDrawable() {
    return sprite;
}

void Heart::changeToGray(sf::Texture& grayTexture) {
    if (!isGray) {
        sprite.setTexture(grayTexture);
        isGray = true;
    }
}
