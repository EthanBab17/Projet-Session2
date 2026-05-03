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
        std::cerr << "ERREUR CRITIQUE : Impossible de trouver la police !" << std::endl;
        std::cerr << "Verifie que le fichier est bien dans src/fonts/arial.ttf" << std::endl;

        // 2. On ferme le programme proprement au lieu de laisser crash plus tard
        exit(1);
    }
    sf::Font m_font;
    mMenuOptions.push_back("Jouer");
    mMenuOptions.push_back("Quitter");
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(mSprite);
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