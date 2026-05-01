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
    Map();
    void setPosition(sf::Vector2f position);
};


#endif //CMAKESFMLPROJECT_MAP_H