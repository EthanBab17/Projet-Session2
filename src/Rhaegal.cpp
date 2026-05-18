//
// Created by babin on 2026-05-04.
//

#include "Rhaegal.h"
Rhaegal::Rhaegal() : Monster() {
    mName = "Rhaegal";
    pv = 100;
    actualPv = pv;
    level = 1;
    atk = 10;
    actualAtk = atk;
    mAttackNames = {"FireBall", "WingSlash", "DracoMeteore"};
    mSourceRect = sf::IntRect({0, 0}, {928, 1142});
    loadTexture("../../src/Sprite/Rhaegal.png");
    damageTaken = 0;
}

void Rhaegal::attack(int moveIndex, Monster& target) {
    int damage = 0;

    switch (moveIndex) {
        case 0: // FireBall
            damage = atk * level;
            std::cout << mName << " Throw a fire ball!" << std::endl;
            break;

        case 1: // WingSlash
            damage = (atk * level) + 5;
            std::cout << mName << " Use WingSlash !" << std::endl;
            break;

        case 2: // DracoMeteore
            damage = (atk * 2) + level;
            std::cout << mName << " Makes it rain meteors !" << std::endl;
            break;
        default:
            damage = 0;
            break;
    }
    target.takeDamage(damage);
}
std::string Rhaegal::getAttackName(int moveIndex){
    switch (moveIndex) {
        case 0:
            return "FireBall";
        case 1:
            return "Wingslash";
        case 2:
            return "Dracometeore";
    }
    return "";
}
std::string Rhaegal::getType() const {
    return "Rhaegal";
}
