//
// Created by babin on 2026-05-05.
//

#include "RenderText.h"

RenderText::RenderText() {
    if (!mFont.openFromFile("../../src/RetroText.ttf")) {
        std::cerr << "ERREUR : Police introuvable !" << std::endl;
    }

}

void RenderText::CombatText(float x, float y, sf::RenderWindow &window) {
    sf::RectangleShape rect({400.f, 100.f});
    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color::Black);
    float posX = x;
    float posY = y;
    rect.setPosition({posX, posY});
    sf::Text txt(mFont, "Press F to start the fight", 15);
    txt.setFillColor(sf::Color::Black);

    sf::FloatRect bounds = txt.getLocalBounds();
    txt.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                   bounds.position.y + bounds.size.y / 2.f});
    txt.setPosition({rect.getPosition().x + (rect.getSize().x / 2.f),
                     rect.getPosition().y + (rect.getSize().y / 2.f)});
    window.draw(rect);
    window.draw(txt);
}
