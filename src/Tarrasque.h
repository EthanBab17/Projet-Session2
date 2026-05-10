//
// Created by babin on 2026-05-09.
//

#ifndef CMAKESFMLPROJECT_TARRASQUE_H
#define CMAKESFMLPROJECT_TARRASQUE_H
#include "Entities.h"
#include "Monster.h"
#include <iostream>
#include <cmath>
#include <list>

class Tarrasque : public Monster{
public:
    Tarrasque();
    void attack(int moveIndex, Monster& target) override;
    std::string getAttackName(int moveIndex) override;
};


#endif //CMAKESFMLPROJECT_TARRASQUE_H