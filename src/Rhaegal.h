//
// Created by babin on 2026-05-04.
//

#ifndef CMAKESFMLPROJECT_RHAEGAL_H
#define CMAKESFMLPROJECT_RHAEGAL_H
#include "Entities.h"
#include <cmath>
#include <list>

class Rhaegal : public Entities{
private:
    int level;
    int currentExp;
    int atk;
    int pv;
    public:
    std::list<int> mAttacks;

    Rhaegal();
    void fireBall();
    void wingSlash();
    void dracoMeteore();
    void gainExp(double exp);
};


#endif //CMAKESFMLPROJECT_RHAEGAL_H