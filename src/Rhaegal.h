//
// Created by babin on 2026-05-04.
//

#ifndef CMAKESFMLPROJECT_RHAEGAL_H
#define CMAKESFMLPROJECT_RHAEGAL_H
#include "Entities.h"
#include <cmath>

class Rhaegal : public Entities{
private:
    int level;
    int currentExp;
    int atk;
    int pv;
    public:
    Rhaegal();
    int FireBall();
    int wingSlash();
    int DracoMeteore();
    void GainExp(double exp);
};


#endif //CMAKESFMLPROJECT_RHAEGAL_H