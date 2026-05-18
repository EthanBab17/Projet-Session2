//
// Created by babin on 2026-05-08.
//

#include "GiantParrot.h"
GiantParrot::GiantParrot() : Monster(){
    mName = "GiantParrot";
    pv = 80;
    actualPv = pv;
    level = 1;
    atk = 8;
    actualAtk = atk;
    mAttackNames = {"Intimidate", "WingSlash", "FeatherArrow"};
    mSourceRect = sf::IntRect({0, 0}, {928, 1142});
    loadTexture("../../src/Sprite/Parrot.png");
    damageTaken = 0;
}


void GiantParrot::attack(int moveIndex, Monster& target) {
    int damage = 0;

    switch (moveIndex) {
        case 0: //Intimidate
            this->actualAtk = actualAtk + 3;
            std::cout << mName << "Increase attack!" << std::endl;
            break;

        case 1: // WingSlash
            damage = (actualAtk * level) + 5;
            std::cout << mName << " Use Wingslash !" << std::endl;
            break;

        case 2: // FeatherArrow
            damage = actualAtk + (level * 2);
            std::cout << mName << " throw a feather!" << std::endl;
            break;
        default:
            damage = 0;
            break;
    }
    target.takeDamage(damage);
}
std::string GiantParrot::getAttackName(int moveIndex) {
    switch (moveIndex) {
        case 0:
            return "Intimidate";
        case 1:
            return "Wingslash";
        case 2:
            return "FeatherArrow";
    }
    return "";
}
std::string GiantParrot::getType() const {
    return "GiantParrot";
}
