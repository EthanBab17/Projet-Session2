//
// Created by babin on 2026-04-29.
//

#include "Map.h"
Map::Map()
    : mCurrentMapIndex(0){
    mSprite.setOrigin({0.f, 0.f});
    mSprite.setScale({2.15f, 2.4f});
    mSourceRect = sf::IntRect({0, 0}, {900, 507});
    mhitboxes.push_back(sf::FloatRect({1065, 0}, {855, 625}));
    mhitboxes.push_back(sf::FloatRect({0, 0}, {760, 420}));
    mhitboxes.push_back(sf::FloatRect({0, 420}, {190, 220}));
    mhitboxes.push_back(sf::FloatRect({0, 640}, {750, 558}));
    mhitboxes.push_back(sf::FloatRect({750, 973}, {1000, 250}));
    mhitboxes.push_back(sf::FloatRect({0, 1200}, {2000, 10}));
    mMapsHitboxes.push_back(mhitboxes);
    mhitboxes.clear();

    mhitboxes.push_back(sf::FloatRect({0, 0}, {2000, 70}));
    mhitboxes.push_back(sf::FloatRect({0, 0}, {50, 1200}));
    mhitboxes.push_back(sf::FloatRect({1870, 0}, {50, 1200}));
    mhitboxes.push_back(sf::FloatRect({0, 1155}, {840, 80}));
    mhitboxes.push_back(sf::FloatRect({1060, 1155}, {840, 80}));
    mMapsHitboxes.push_back(mhitboxes);
    mhitboxes.clear();

    mhitboxes.push_back(sf::FloatRect({0, 0}, {2000, 95}));
    mhitboxes.push_back(sf::FloatRect({1730, 0}, {200,1500 }));
    mhitboxes.push_back(sf::FloatRect({0, 0}, {50, 700}));
    mhitboxes.push_back(sf::FloatRect({135, 628}, {250, 320}));
    mhitboxes.push_back(sf::FloatRect({185, 0}, {550, 635}));
    mhitboxes.push_back(sf::FloatRect({750, 500}, {100, 140}));
    mhitboxes.push_back(sf::FloatRect({850, 0}, {465, 655}));
    mhitboxes.push_back(sf::FloatRect({0, 1200}, {2000, 10}));
    mhitboxes.push_back(sf::FloatRect({725, 895}, {250, 320}));
    mMapsHitboxes.push_back(mhitboxes);
    mhitboxes.clear();
    }

void Map::draw(sf::RenderWindow &window) {
    window.draw(mSprite);

    for (size_t i = 0; i < mhitboxes.size(); i++) {
        sf::RectangleShape debugRect;

        // On donne au rectangle la taille et la position de la FloatRect
        debugRect.setSize(mMapsHitboxes[mCurrentMapIndex][i].size);
        debugRect.setPosition(mMapsHitboxes[mCurrentMapIndex][i].position);

        // On le rend visible (rouge transparent par exemple)
        debugRect.setFillColor(sf::Color::Transparent); // Rouge avec 100 d'opacité
        debugRect.setOutlineColor(sf::Color::Red);
        debugRect.setOutlineThickness(1.f);
        window.draw(debugRect);
    }
}
