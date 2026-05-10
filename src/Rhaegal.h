//
// Created by babin on 2026-05-04.
//

#ifndef CMAKESFMLPROJECT_RHAEGAL_H
#define CMAKESFMLPROJECT_RHAEGAL_H
#include "Entities.h"
#include "Monster.h"
#include <iostream>
#include <cmath>
#include <list>

class Rhaegal : public Monster{
    public:
    Rhaegal();
    void attack(int moveIndex, Monster& target) override;
    std::string getAttackName(int moveIndex) override;
};


#endif //CMAKESFMLPROJECT_RHAEGAL_H