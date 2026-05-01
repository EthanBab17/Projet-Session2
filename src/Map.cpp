//
// Created by babin on 2026-04-29.
//

#include "Map.h"
Map::Map()
    {
    mSprite.setOrigin({0.f, 0.f});
    mSprite.setScale({2.15f, 2.4f});
    mSourceRect = sf::IntRect({0, 0}, {900, 507});
    mTexture.setSmooth(false);
    }

void Map::setPosition(sf::Vector2f position) {
    mSprite.setPosition(position);
}