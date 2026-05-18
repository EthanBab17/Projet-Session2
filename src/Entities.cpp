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
sf::Vector2f Entities::getSpritePosition() {
    return mSprite.getPosition();
}
void Entities::setSpriteScale(sf::Vector2f scale) {
    mSprite.setScale(scale);
}
sf::Vector2f Entities::getSpriteScale() {
    return mSprite.getScale();
}
void Entities::setOrigin(sf::Vector2f origin) {
    mSprite.setOrigin(origin);

}
sf::FloatRect Entities::getBounds() {
    return mSprite.getLocalBounds();
}

sf::FloatRect Entities::getHitbox() {
    return mhitbox;
}
void Entities::setHitboxPos(sf::Vector2f hitboxPos) {
    this->mhitbox.position.x = (hitboxPos.x + 20);
    this->mhitbox.position.y = (hitboxPos.y + 100);
}