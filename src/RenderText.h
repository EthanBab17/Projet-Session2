//
// Created by babin on 2026-05-05.
//

#ifndef CMAKESFMLPROJECT_RENDERTEXT_H
#define CMAKESFMLPROJECT_RENDERTEXT_H
#include <SFML/Graphics.hpp>
#include <iostream>

class RenderText {
private:
    sf::Font mFont;
public:
    RenderText();
    void CombatText(float x, float y, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
};


#endif //CMAKESFMLPROJECT_RENDERTEXT_H