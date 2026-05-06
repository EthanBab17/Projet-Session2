//
// Created by babin on 2026-05-04.
//

#ifndef CMAKESFMLPROJECT_MONSTERMASTER_H
#define CMAKESFMLPROJECT_MONSTERMASTER_H
#include "Entities.h"

class Pnj : public Entities{
    public:
    std::vector<std::vector<sf::FloatRect>> mPnjHitboxes;
    Pnj();
    void initPnj(int currentPnj);
};


#endif //CMAKESFMLPROJECT_MONSTERMASTER_H