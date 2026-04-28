//
// Created by babin on 2026-04-27.
//

#include "Player.h"

Player::Player()
    : mSprite(mTexture)
{
    mSprite.setOrigin({32.f, 32.f});
    mSourceRect = sf::IntRect({0, 0}, {425, 625});
    mSprite.setScale({0.25f, 0.25f});
}

void Player::loadTexture(const std::string &filename) {
    if (mTexture.loadFromFile(filename)) {
        mSprite.setTexture(mTexture);
        mSprite.setTextureRect(mSourceRect);
    } else {
        std::cout << "Erreur de chargement de : " << filename << std::endl;
    }
}
void Player::setDirection(int index) {
    // index 0: Face, 1: Droite, 2: Arrière, 3: Gauche
    int column = index % 2; // Donne 0 ou 1
    int row = index / 2;    // Donne 0 pour (0,1) et 1 pour (2,3)

    mSourceRect.position.x = static_cast<float>(column * 425);
    mSourceRect.position.y = static_cast<float>(row * 625);

    mSprite.setTextureRect(mSourceRect);
}
void Player::setPosition(sf::Vector2f position) {
    mSprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(mSprite);
}

void Player::move(sf::Vector2f direction, float deltaTime) {
    float speed = 3.f;
    sf::Vector2f velocity = DeltaTime::normalize(direction);

    mSprite.move(velocity * speed * deltaTime);
}