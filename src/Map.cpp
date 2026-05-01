//
// Created by babin on 2026-04-29.
//

#include "Map.h"
Map::Map()
    : mapSprite(mapTexture)
    {
    mapSprite.setOrigin({0.f, 0.f});
    mapSprite.setScale({2.1f, 2.4f});
    mapSourceRect = sf::IntRect({0, 0}, {900, 507});
    mapTexture.setSmooth(false);
    }

void Map::loadTexture(const std::string &filename) {
    if (mapTexture.loadFromFile(filename)) {
        mapSprite.setTexture(mapTexture);
        mapSprite.setTextureRect(mapSourceRect);
    } else {
        std::cout << "Erreur de chargement de : " << filename << std::endl;
    }
}


void Map::draw(sf::RenderWindow& window) {
    window.draw(mapSprite);
}

void Map::setPosition(sf::Vector2f position) {
    mapSprite.setPosition(position);
}