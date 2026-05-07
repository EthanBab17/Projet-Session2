//
// Created by babin on 2026-05-06.
//

#ifndef CMAKESFMLPROJECT_MONSTER_H
#define CMAKESFMLPROJECT_MONSTER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Entities.h"

class Monster : public Entities{
protected:
    std::string mName;
    int pv;
    int atk;
    int level;
    int currentExp;
    std::vector<std::string> mAttackNames;
public:
    Monster();
    virtual ~Monster() = default;
    virtual void attack(int moveIndex, Monster& target) = 0;
    void gainExp(int exp);
    void takeDamage(int damge);
    int getPv() const;
    void setPv(int newPv);
    std::string getName() const;
    void setLevel(int level);
    int getLevel() const;
    void setCurrentExp(int exp);
    int getCurrentExp()const;
};


#endif //CMAKESFMLPROJECT_MONSTER_H