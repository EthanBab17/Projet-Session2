//
// Created by babin on 2026-05-01.
//

#ifndef CMAKESFMLPROJECT_ENTITIES_H
#define CMAKESFMLPROJECT_ENTITIES_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Entities {
public:
    sf::Sprite mSprite;
    sf::IntRect mSourceRect;
    sf::Texture mTexture;
    Entities() : mSprite(mTexture){};
    void loadTexture(const std::string &filename);
    void draw(sf::RenderWindow &window);
};


#endif //CMAKESFMLPROJECT_ENTITIES_H