//
// Created by babin on 2026-05-04.
//

#include "Rhaegal.h"
Rhaegal::Rhaegal() {
    mSprite.setOrigin({32.f, 32.f});
    mSourceRect = sf::IntRect({0, 0}, {928, 1142});
    mSprite.setScale({0.30f, 0.30f});
    mhitbox = sf::FloatRect({0, 0}, {70, 55});
    atk = 10;
    pv = 100;
    level = 1;
    currentExp = 0;
    mAttackName.push_back("FireBall");
    mAttackName.push_back("WingSlash");
    mAttackName.push_back("DracoMeteore");
    mAttacks.clear();
    fireBall();
    wingSlash();
    dracoMeteore();
}

int Rhaegal::fireBall() {
    int damages = 0;
    damages= atk * level;
    return damages;
}
int Rhaegal::wingSlash() {
    int damages = 0;
    damages= atk * level + 5;
    return damages;
}
int Rhaegal::dracoMeteore() {
    int damages = 0;
    damages= 2 * atk + level;
    return damages;
}
void Rhaegal::gainExp(double exp) {
    currentExp += exp;
    if (currentExp >= (100 * std::pow(level, 2))) {
        level++;
        std::cout << "Rhaegal level (" << level << ")" << std::endl;
    }
}
int Rhaegal::getPv() {
    return pv;
}
void Rhaegal::takeDamage(int damage) {
    this->pv = (pv- damage);
}
void Rhaegal::resetPv() {
    pv = 100;
}
void Rhaegal::setLevel(int level) {
    this->level = level;
}

int Rhaegal::getLevel() {
    return level;
}
int Rhaegal::getCurrentExp() {
    return currentExp;
}
void Rhaegal::setCurrentExp(int exp) {
    this-> currentExp = exp;
}