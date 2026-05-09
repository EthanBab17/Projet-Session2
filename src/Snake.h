//
// Created by babin on 2026-05-08.
//

#ifndef CMAKESFMLPROJECT_SNAKE_H
#define CMAKESFMLPROJECT_SNAKE_H
#include "Entities.h"
#include "Monster.h"
#include <iostream>
#include <cmath>
#include <list>

class Snake : public Monster{
public:
    Snake();
    void attack(int moveIndex, Monster& target) override;
    std::string getAttackName(int moveIndex) override;
private:
    int damageTaken;
    std::list<std::string> mAttackName;
    std::list<int> mAttacks;
};


#endif //CMAKESFMLPROJECT_SNAKE_H