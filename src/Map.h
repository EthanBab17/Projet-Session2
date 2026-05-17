//
// Created by babin on 2026-04-29.
//

#ifndef CMAKESFMLPROJECT_MAP_H
#define CMAKESFMLPROJECT_MAP_H
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Entities.h"

class Map : public Entities{
private:
    std::vector<std::vector<sf::FloatRect>> mMapsHitboxes;
    int mCurrentMapIndex;
    std::vector<sf::FloatRect> spawnZones;

    sf::Clock stepClock;
public:
    Map();
    int getCurrentMapIndex();
    void setCurrentMapIndex(int index);
    std::vector<std::vector<sf::FloatRect>> getHitboxes();
    std::vector<std::vector<sf::FloatRect>> mMapsSpawnZones;
    void addTallGrass(sf::FloatRect rect);
    const std::vector<sf::FloatRect>& getTallGrass() const;
    void clearZones();
};


#endif //CMAKESFMLPROJECT_MAP_H