//
// Created by babin on 2026-05-01.
//

#include "Entities.h"


void Entities::loadTexture(const std::string &filename) {
    if (mTexture.loadFromFile(filename)) {
        mSprite.setTexture(mTexture, true);
        mSprite.setTextureRect(mSourceRect);
    } else {
        std::cout << "Erreur de chargement de : " << filename << std::endl;
    }
}
void Entities::draw(sf::RenderWindow &window) {
    window.draw(mSprite);
}
void Entities::setPosition(sf::Vector2f position) {
    mSprite.setPosition(position);
}
sf::Vector2f Entities::getPosition() {
    return mSprite.getPosition();
}
void Entities::setSprite(sf::Sprite sprite) {
    this->mSprite = sprite;
}

sf::Sprite Entities::getSprite() {
    return mSprite;
}
