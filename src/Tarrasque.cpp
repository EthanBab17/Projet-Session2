//
// Created by babin on 2026-05-09.
//

#include "Tarrasque.h"
Tarrasque::Tarrasque() : Monster(){
    mName = "Tarrasque";
    pv = 150;
    actualPv = pv;
    level = 1;
    atk = 15;
    actualAtk = atk;
    mAttackNames = {"Annihilation", "Scratch", "Doom"};
    mSourceRect = sf::IntRect({0, 0}, {1024, 1024});
    loadTexture("../../src/Sprite/Tarrasque.png");
    damageTaken = 0;
}


void Tarrasque::attack(int moveIndex, Monster& target) {
    int damage = 0;

    switch (moveIndex) {
        case 0: //Annihilation
            damage = (atk * level);
            std::cout << mName << "Use Annihilation!" << std::endl;
            break;

        case 1: // Scratch
            damage = atk;
            std::cout << mName << " Claw swipe!" << std::endl;
            break;

        case 2: // Doom
            damage = atk * std::pow(level, 2);
            std::cout << mName << " Good luck!" << std::endl;
            break;
        default:
            damage = 0;
            break;
    }
    target.takeDamage(damage);
}
std::string Tarrasque::getAttackName(int moveIndex) {
    switch (moveIndex) {
        case 0:
            return "Annihilation";
        case 1:
            return "Scratch";
        case 2:
            return "Doom";
    }
    return "";
}
std::string Tarrasque::getType() const {
    return "Tarrasque";
}
void Tarrasque::realScale() {
    mSprite.setScale({0.8f, 0.8f});
}
void Tarrasque::realFightPosition() {
    sf::FloatRect boundsEntitie = mSprite.getLocalBounds();
    mSprite.setOrigin({
        boundsEntitie.position.x + boundsEntitie.size.x / 2.f,
        boundsEntitie.position.y + boundsEntitie.size.y / 2.f
    });
    mSprite.setPosition({550.f, 500.f});
}