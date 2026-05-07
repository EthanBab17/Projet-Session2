//
// Created by babin on 2026-05-04.
//

#ifndef CMAKESFMLPROJECT_RHAEGAL_H
#define CMAKESFMLPROJECT_RHAEGAL_H
#include "Monster.h"
#include <iostream>
#include <cmath>
#include <list>

class Rhaegal : public Monster{
    public:
    Rhaegal();

    void attack(int moveIndex, Monster& target) override;

    int damageTaken;
    std::list<std::string> mAttackName;
    std::list<int> mAttacks;

};


#endif //CMAKESFMLPROJECT_RHAEGAL_H