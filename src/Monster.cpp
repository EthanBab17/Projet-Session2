//
// Created by babin on 2026-05-06.
//

#include "Monster.h"
Monster::Monster() : Entities(), pv(10), atk(0), level(1), currentExp(0) {}

void Monster::takeDamage(int damage) {
    this->actualPv -= damage;
//     if (this->pv < 0) this->pv = 0;
//     std::cout << mName << " a perdu " << damage << " PV !" << std::endl;
}
void Monster::gainExp(int exp) {
    currentExp += exp;
    if (currentExp >= (100 * std::pow(level, 2))) {
        level++;
        std::cout << mName + " level (" << level << ")" << std::endl;
    }
}
int Monster::getPv() const {
    return pv;
}
int Monster::getActualPv() const {
    return actualPv;
}
void Monster::resetPv() {
    this->actualPv = pv;
}
void Monster::setLevel(int newlevel) {
    this->level = newlevel;
}

int Monster::getLevel() const{
    return level;
}
int Monster::getCurrentExp()const {
    return currentExp;
}
void Monster::setCurrentExp(int exp) {
    this-> currentExp = exp;
}
std::string Monster::getName() const {
    return mName;
}
void Monster::resetAtk() {
    this-> actualAtk = atk;
}
