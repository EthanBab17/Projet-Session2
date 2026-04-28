//
// Created by babin on 2026-04-28.
//

#include "../src/DeltaTime.h"

sf::Vector2f DeltaTime::normalize(const sf::Vector2f &vitesse) {
    float magnitude = std::hypot(vitesse.x, vitesse.y);
    if (magnitude != 0.0f) {
        return vitesse/magnitude;
    }
    return vitesse;
}