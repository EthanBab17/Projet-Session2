//
// Created by babin on 2026-05-02.
//

#include "Menu.h"

Menu::Menu() : mSprite(mTexture){
    mSprite.setOrigin({0.f, 0.f});
    mSprite.setScale({2.15f, 2.4f});
    mSourceRect = sf::IntRect({0, 0}, {900, 507});
    mCurrentMenuIndex = 0;
    if (!mFont.openFromFile("../../src/RetroText.ttf")) {
        std::cerr << "ERREUR : Police introuvable !" << std::endl;
    }
    mString.push_back("Play");
    mString.push_back("Load Game");
    mString.push_back("Save Game");
    mString.push_back("Quit");
}

void Menu::init(float x, float y) {
    mButtons.clear();
    mMenuOptions.clear();

    for (size_t i = 0; i < mString.size(); ++i) {
        sf::RectangleShape rect({300.f, 75.f});
        rect.setFillColor(sf::Color(50, 50, 50, 200));
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::White);
        float posX = x - (rect.getSize().x / 2.f);
        float posY = y + (i * 100.f);
        rect.setPosition({posX, posY});
        mButtons.push_back(rect);

        sf::Text txt(mFont, mString[i], 30);
        txt.setFillColor(sf::Color::White);

        sf::FloatRect bounds = txt.getLocalBounds();
        txt.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                       bounds.position.y + bounds.size.y / 2.f});
        txt.setPosition({rect.getPosition().x + (rect.getSize().x / 2.f),
                         rect.getPosition().y + (rect.getSize().y / 2.f)});

        mMenuOptions.push_back(txt);
    }
}


void Menu::draw(sf::RenderWindow &window) {
    window.draw(mSprite);
    for (size_t i = 0; i < mButtons.size(); ++i) {
        if (i == mCurrentMenuIndex) {
            mButtons[i].setOutlineColor(sf::Color::Green);
            mButtons[i].setOutlineThickness(4);
            mMenuOptions[i].setFillColor(sf::Color::Green);
        }
        else {
            mButtons[i].setOutlineColor(sf::Color::White);
            mButtons[i].setOutlineThickness(2);
            mMenuOptions[i].setFillColor(sf::Color::White);
        }

        window.draw(mButtons[i]);
        window.draw(mMenuOptions[i]);
    }
}

void Menu::menuLoadTexture(const std::string &filename) {
    if (mTexture.loadFromFile(filename)) {
        mSprite.setTexture(mTexture);
        mSprite.setTextureRect(mSourceRect);
    } else {
        std::cout << "Erreur de chargement de : " << filename << std::endl;
    }
}

void Menu::setPosition(sf::Vector2f position) {
    mSprite.setPosition(position);
}

void Menu::setOptions() {
    // sf::Font m_font;
    // mMenuOptions.push_back("Jouer");
    // mMenuOptions.push_back("Quitter");
}