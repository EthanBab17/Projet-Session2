//
// Created by babin on 2026-05-08.
//

#include "Snake.h"
Snake::Snake() : Monster() {
    mName = "Snake";
    pv = 90;
    actualPv = pv;
    level = 1;
    atk = 12;
    mAttackNames = {"Bite", "TailSlash", "PoisonSpit"};
    mSourceRect = sf::IntRect({0, 0}, {928, 1142});
    loadTexture("../../src/Sprite/Snake.png");
    damageTaken = 0;
}

void Snake::attack(int moveIndex, Monster& target) {
    int damage = 0;

    switch (moveIndex) {
        case 0: // Bite
            damage = atk * level;
            std::cout << mName << " Bite the enemy!" << std::endl;
            break;

        case 1: // TailSlash
            damage = (atk / 2) * level;
            std::cout << mName << " Use TailSlash !" << std::endl;
            break;

        case 2: // PoisonSpit
            damage = (atk + level) * 2;
            std::cout << mName << " Throw poison !" << std::endl;
            break;
        default:
            damage = 0;
            break;
    }
    target.takeDamage(damage);
}
std::string Snake::getAttackName(int moveIndex){
    switch (moveIndex) {
        case 0:
            return "Bite";
        case 1:
            return "TailSlash";
        case 2:
            return "PoisonSpit";
    }
    return "";
}
std::string Snake::getType() const {
    return "Snake";
}
void Snake::realScale() {
    mSprite.setScale({0.7f, 0.7f});
}
void Snake::realFightPosition() {
    sf::FloatRect boundsEntitie = mSprite.getLocalBounds();
    mSprite.setOrigin({
        boundsEntitie.position.x + boundsEntitie.size.x / 2.f,
        boundsEntitie.position.y + boundsEntitie.size.y / 2.f
    });
    mSprite.setPosition({500.f, 600.f});
}