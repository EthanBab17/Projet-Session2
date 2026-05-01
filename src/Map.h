//
// Created by babin on 2026-04-29.
//

#ifndef CMAKESFMLPROJECT_MAP_H
#define CMAKESFMLPROJECT_MAP_H
#include<SFML/Graphics.hpp>
#include <iostream>

class Map{
    private:
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::IntRect mapSourceRect;

    public:
    Map();
    void loadTexture(const std::string &filename);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
};


#endif //CMAKESFMLPROJECT_MAP_H