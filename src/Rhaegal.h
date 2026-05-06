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
    int damageTaken;
    std::list<std::string> mAttackName;
    std::list<int> mAttacks;

    Rhaegal();
    int fireBall();
    int wingSlash();
    int dracoMeteore();
    void gainExp(double exp);
    void takeDamage(int damge);
    int getPv();
    void resetPv();
    void setLevel(int level);
    int getLevel();
    void setCurrentExp(int exp);
    int getCurrentExp();
};


#endif //CMAKESFMLPROJECT_RHAEGAL_H