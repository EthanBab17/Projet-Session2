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

void Fight::draw(sf::RenderWindow &window) {
    window.draw(mSprite);
    window.draw(mRect);
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

void Fight::menuFight() {
    mMaxFightOptions = 3;
    mString.clear();
    mString.push_back("Attack");
    mString.push_back("Team");
    mString.push_back("Run");
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

void Fight::ChooseAction() {
    Rhaegal rhaegal;
    for (auto it = rhaegal.mAttacks.begin(); it != rhaegal.mAttacks.end(); ++it) {
        // mString.push_back(*it);
    }
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
