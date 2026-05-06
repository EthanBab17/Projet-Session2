//
// Created by babin on 2026-05-04.
//

#include "Pnj.h"

Pnj::Pnj() {
    mSprite.setOrigin({32.f, 32.f});
    mSourceRect = sf::IntRect({0, 0}, {425, 625});
    mSprite.setScale({0.40f, 0.40f});
    mhitboxes.push_back(sf::FloatRect({0, 0}, {70, 110}));
    mhitboxes.push_back(sf::FloatRect({0, 10}, {70, 55}));
    mPnjHitboxes.push_back(mhitboxes);
    mhitboxes.clear();

    mhitboxes.push_back(sf::FloatRect({0, 0}, {0, 0}));
    mPnjHitboxes.push_back(mhitboxes);
}
void Pnj::initPnj(int currentPnj) {
    mPnjHitboxes[currentPnj][0].position.x = (mSprite.getPosition().x);
    mPnjHitboxes[currentPnj][0].position.y = (mSprite.getPosition().y);
    mPnjHitboxes[currentPnj][1].position.x = (mSprite.getPosition().x);
    mPnjHitboxes[currentPnj][1].position.y = (mSprite.getPosition().y + 100);
}