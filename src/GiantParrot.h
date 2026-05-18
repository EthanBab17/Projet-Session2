//
// Created by babin on 2026-05-08.
//

#ifndef CMAKESFMLPROJECT_GIANTPARROT_H
#define CMAKESFMLPROJECT_GIANTPARROT_H
#include "Entities.h"
#include "Monster.h"
#include <iostream>
#include <cmath>
#include <list>

class GiantParrot : public Monster{
public:
    GiantParrot();
    void attack(int moveIndex, Monster& target) override;
    std::string getAttackName(int moveIndex) override;
    std::string getType() const override;
    void realScale() override;
    void realFightPosition() override;
};


#endif //CMAKESFMLPROJECT_GIANTPARROT_H