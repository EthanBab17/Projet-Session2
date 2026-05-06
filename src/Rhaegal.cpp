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
    mAttacks.clear();
    fireBall();
    wingSlash();
    dracoMeteore();
}

void Rhaegal::fireBall() {
    int damages = 0;
    damages= atk * level;
    mAttacks.push_back(damages);
}
void Rhaegal::wingSlash() {
    int damages = 0;
    damages= atk * level + 5;
    mAttacks.push_back(damages);
}
void Rhaegal::dracoMeteore() {
    int damages = 0;
    damages= 2 * atk + level;
    mAttacks.push_back(damages);
}
void Rhaegal::gainExp(double exp) {
    currentExp += exp;
    if (currentExp > (exp * std::pow(level, 2))) {
        level++;
        std::cout << "Rhaegal level (" << level << ")" << std::endl;
    }
}