//
// Created by babin on 2026-05-05.
//

#include "Fight.h"

Fight::Fight() : mSprite(mTexture){
    mSprite.setOrigin({0.f, 0.f});
    mSprite.setScale({1.62f, 1.35f});
    mSourceRect = sf::IntRect({0, 0}, {1195, 896});
    if (!mFont.openFromFile("../../src/RetroText.ttf")) {
        std::cerr << "ERREUR : Police introuvable !" << std::endl;
    }
    mRect.setPosition({0,700});
    mRect.setSize({1980,480});
    mRect.setFillColor(sf::Color(100,100,100,200));
    mRect.setOutlineColor(sf::Color::Red);
    mRect.setOutlineThickness(20);
    mRect2.setFillColor(sf::Color::White);
    mRect2.setPosition({1100,700});
    mRect2.setSize({820,480});

}

void Fight::CombatLoadTexture(const std::string &filename) {
    if (mTexture.loadFromFile(filename)) {
        mSprite.setTexture(mTexture);
        mSprite.setTextureRect(mSourceRect);
    } else {
        std::cout << "Erreur de chargement de : " << filename << std::endl;
    }
}

void Fight::draw(sf::RenderWindow &window, Rhaegal &playerDragon, Rhaegal &enemyDragon) {
    window.draw(mSprite);
    window.draw(playerDragon.mSprite);
    if (enemyDragon.getPv() > 0) {
        window.draw(enemyDragon.mSprite);
    }

    sf::Text pv(mFont, "Niv." + std::to_string(playerDragon.getLevel()) +"\n HP: " + std::to_string(playerDragon.getPv()), 20);
    pv.setFillColor(sf::Color::Green);
    pv.setPosition({50.f, 780.f});
    sf::Text pv2(mFont, "HP: " + std::to_string(enemyDragon.getPv()), 20);
    pv2.setFillColor(sf::Color::Red); // pv2 ici
    pv2.setPosition({1000.f, 50.f});  // pv2 ici

    window.draw(mRect);
    window.draw(pv);
    window.draw(pv2);
    window.draw(mRect2);
    for (size_t i = 0; i < mButtons.size(); ++i) {
        if (i == mCurrentFightIndex) {
            mButtons[i].setOutlineColor(sf::Color::Green);
            mButtons[i].setOutlineThickness(4);
            mText[i].setFillColor(sf::Color::Green);
        }
        else {
            mButtons[i].setOutlineColor(sf::Color::Red);
            mButtons[i].setOutlineThickness(2);
            mText[i].setFillColor(sf::Color::Red);
        }
        window.draw(mButtons[i]);
        window.draw(mText[i]);
    }
}

void Fight::menuFight(const std::vector<std::string>& options) {
    mButtons.clear();
    mText.clear();
    mString = options;
    mMaxFightOptions = mString.size();
    mCurrentFightIndex = 0; // On reset l'index à chaque changement de menu
    for (size_t i = 0; i < mString.size(); ++i) {
        sf::RectangleShape buttons({250.f, 60.f});
        buttons.setFillColor(sf::Color(50, 50, 50, 200));
        buttons.setOrigin({buttons.getSize().x / 2.f, buttons.getSize().y / 2.f});
        float posX = mRect2.getPosition().x + (mRect2.getSize().x / 2.f);
        float posY = (mRect2.getPosition().y + 50.f) + (i * 100.f);
        buttons.setPosition({posX, posY});
        mButtons.push_back(buttons);

        sf::Text txt(mFont, mString[i], 20);
        txt.setFillColor(sf::Color::Black);
        sf::FloatRect bounds = txt.getLocalBounds();
        txt.setOrigin({bounds.position.x + bounds.size.x /2.f,
                       bounds.position.y + bounds.size.y / 2.f});
        txt.setPosition({posX, posY});
        mText.push_back(txt);
    }
}