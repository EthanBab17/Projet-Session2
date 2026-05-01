//
// Created by babin on 2026-04-27.
//

#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H
#include <SFML/Graphics.hpp>
#include "DeltaTime.h"
#include <iostream>
#include "Entities.h"

class Player : public Entities{
public:
    Player();
    void setDirection(int index);
    void move(sf::Vector2f direction, float deltaTime);
};


#endif //CMAKESFMLPROJECT_PLAYER_H