//
// Created by babin on 2026-04-27.
//

#include "Player.h"

Player::Player(){
    mSprite.setOrigin({32.f, 32.f});
    mSourceRect = sf::IntRect({0, 0}, {425, 625});
    mSprite.setScale({0.30f, 0.30f});
    mhitbox = sf::FloatRect({0, 0}, {70, 55});
}

void Player::setDirection(int index) {
    // index 0: Face, 1: Droite, 2: Arrière, 3: Gauche
    int column = index % 2;
    int row = index / 2;

    mSourceRect.position.x = static_cast<float>(column * 425);
    mSourceRect.position.y = static_cast<float>(row * 625);

    mSprite.setTextureRect(mSourceRect);
}

void Player::move(sf::Vector2f direction, float deltaTime) {
    float speed = 3.f;
    sf::Vector2f velocity = DeltaTime::normalize(direction);

    mSprite.move(velocity * speed * deltaTime);

    mhitbox.position.x = (mSprite.getPosition().x + 20);
    mhitbox.position.y = (mSprite.getPosition().y + 100);
}