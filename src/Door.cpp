//
// Created by babin on 2026-05-04.
//

#include "Door.h"

Door::Door() {
    mhitboxes.clear();
    mhitboxes.push_back(sf::FloatRect({1200, 657}, {100, 15}));
    mhitboxes.push_back(sf::FloatRect({749, 1133}, {470, 100}));
}
