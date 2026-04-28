//
// Created by babin on 2026-04-28.
//

#ifndef CMAKESFMLPROJECT_DELTATIME_H
#define CMAKESFMLPROJECT_DELTATIME_H
#include <SFML/System/Vector2.hpp>

class DeltaTime {
public:
    static sf::Vector2f normalize(const sf::Vector2f& vitesse);

};


#endif //CMAKESFMLPROJECT_DELTATIME_H