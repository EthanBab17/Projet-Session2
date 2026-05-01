//
// Created by babin on 2026-05-01.
//

#include "Entities.h"

void Entities::loadTexture(const std::string &filename) {
    if (mTexture.loadFromFile(filename)) {
        mSprite.setTexture(mTexture);
        mSprite.setTextureRect(mSourceRect);
    } else {
        std::cout << "Erreur de chargement de : " << filename << std::endl;
    }
}
void Entities::draw(sf::RenderWindow &window) {
    window.draw(mSprite);

    sf::RectangleShape rect({mhitbox.size.x, mhitbox.size.y});
    rect.setPosition(mhitbox.position);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1.f);
    window.draw(rect);

    for (size_t i = 0; i < mhitboxes.size(); i++) {
        sf::RectangleShape debugRect;

        // On donne au rectangle la taille et la position de la FloatRect
        debugRect.setSize({mhitboxes[i].size.x, mhitboxes[i].size.y});
        debugRect.setPosition(mhitboxes[i].position);

        // On le rend visible (rouge transparent par exemple)
        debugRect.setFillColor(sf::Color::Transparent); // Rouge avec 100 d'opacité
        debugRect.setOutlineColor(sf::Color::Red);
        debugRect.setOutlineThickness(1.f);
        window.draw(debugRect);
    }
}
void Entities::setPosition(sf::Vector2f position) {
    mSprite.setPosition(position);
}
sf::Vector2f Entities::getPosition() {
    return mSprite.getPosition();
}