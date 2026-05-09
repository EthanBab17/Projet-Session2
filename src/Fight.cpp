//
// Created by babin on 2026-05-05.
//

#include "Fight.h"

Fight::Fight() : mSprite(mTexture),mPv(mFont),mPv2(mFont){
    mSprite.setOrigin({0.f, 0.f});
    mSprite.setScale({1.62f, 1.35f});
    mSourceRect = sf::IntRect({0, 0}, {1195, 896});
    if (!mFont.openFromFile("../../src/RetroText.ttf")) {
        std::cerr << "ERREUR : Police introuvable !" << std::endl;
    }
    mPv.setFont(mFont);
    mPv.setCharacterSize(20);
    mPv2.setFont(mFont);
    mPv2.setCharacterSize(20);
    mRect.setPosition({0,700});
    mRect.setSize({1980,480});
    mRect.setFillColor(sf::Color(100,100,100,200));
    mRect.setOutlineColor(sf::Color::Red);
    mRect.setOutlineThickness(20);
    mRect2.setFillColor(sf::Color::White);
    mRect2.setPosition({1100,700});
    mRect2.setSize({820,480});
    mCurrentFightIndex = 0;
    mMaxFightOptions = 0;
}

void Fight::CombatLoadTexture(const std::string &filename) {
    if (mTexture.loadFromFile(filename)) {
        mSprite.setTexture(mTexture);
        mSprite.setTextureRect(mSourceRect);
    } else {
        std::cout << "Erreur de chargement de : " << filename << std::endl;
    }
}

void Fight::draw(sf::RenderWindow &window, Monster& monster, Rhaegal &enemyDragon) {
    window.draw(mSprite);
    monster.draw(window);
    if (enemyDragon.getActualPv() > 0) {
        enemyDragon.draw(window);
    }
    mPv.setString("LV." + std::to_string(monster.getLevel()) + "HP: "+ std::to_string(monster.getActualPv()));
    mPv.setFillColor(sf::Color::Green);
    mPv.setPosition({50.f, 780.f});
    mPv2.setString("HP: " + std::to_string(enemyDragon.getActualPv()));
    mPv2.setFillColor(sf::Color::Red);
    mPv2.setPosition({1000.f, 50.f});

    window.draw(mRect);
    window.draw(mPv);
    window.draw(mPv2);
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
    mCurrentFightIndex = 0;
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
void Fight::updateAnimation(Monster& monster) {
    if (animPhase == AnimPhase::None) return;

    float elapsed = animClock.getElapsedTime().asSeconds();

    if (animPhase == AnimPhase::Forward) {
        float t = elapsed / animDuration;
        if (t >= 1.0f) {
            animPhase = AnimPhase::Wait;
            animClock.restart();
        } else {
            monster.mSprite.setPosition(originalPos + t * (targetPos - originalPos));
        }
    }
    else if (animPhase == AnimPhase::Wait) {
        if (elapsed >= 0.1f) {
            animPhase = AnimPhase::Backward;
            animClock.restart();
        }
    }
    else if (animPhase == AnimPhase::Backward) {
        float t = elapsed / animDuration;
        if (t >= 1.0f) {
            monster.mSprite.setPosition(originalPos);
            animPhase = AnimPhase::None;
        } else {
            monster.mSprite.setPosition(targetPos + t * (originalPos - targetPos));
        }
    }
}
void Fight::startAttackAnim(Monster& monster) {
    originalPos = monster.mSprite.getPosition();
    targetPos = originalPos + sf::Vector2f(50.f, 0.f);
    animPhase = AnimPhase::Forward;
    animClock.restart();
}
AnimPhase Fight::getAnimPhase() const {
    return animPhase;
}
