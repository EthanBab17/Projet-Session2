//
// Created by babin on 2026-04-29.
//

#ifndef CMAKESFMLPROJECT_MAP_H
#define CMAKESFMLPROJECT_MAP_H
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Entities.h"

class Map : public Entities{
    public:
    std::vector<sf::FloatRect> mhitboxes;
    std::vector<std::vector<sf::FloatRect>> mMapsHitboxes;
    int mCurrentMapIndex;
    Map();
    void draw(sf::RenderWindow &window);
};


#endif //CMAKESFMLPROJECT_MAP_H