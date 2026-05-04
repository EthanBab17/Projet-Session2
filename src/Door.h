//
// Created by babin on 2026-05-04.
//

#ifndef CMAKESFMLPROJECT_DOOR_H
#define CMAKESFMLPROJECT_DOOR_H
#include <SFML/Graphics.hpp>

class Door {
    public:
    std::vector<sf::FloatRect> mhitboxes;
    Door();
};


#endif //CMAKESFMLPROJECT_DOOR_H