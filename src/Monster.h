//
// Created by babin on 2026-05-06.
//

#ifndef CMAKESFMLPROJECT_MONSTER_H
#define CMAKESFMLPROJECT_MONSTER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <list>
#include "Entities.h"

class Monster : public Entities{
protected:
    std::string mName;
    int actualPv;
    int pv;
    int actualAtk;
    int atk;
    int level;
    int currentExp;
    int damageTaken;
    std::list<std::string> mAttackNames;
public:
    Monster();
    virtual ~Monster() = default;
    virtual void attack(int moveIndex, Monster& target) = 0;
    void gainExp(int exp);
    void takeDamage(int damage);
    int getPv() const;
    int getActualPv() const;
    void resetPv();
    std::string getName() const;
    void setLevel(int level);
    int getLevel() const;
    void setCurrentExp(int exp);
    int getCurrentExp()const;
    virtual std::string getAttackName(int moveIndex) = 0;
    void resetAtk();
};


#endif //CMAKESFMLPROJECT_MONSTER_H