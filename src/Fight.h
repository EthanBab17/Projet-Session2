//
// Created by babin on 2026-05-05.
//

#ifndef CMAKESFMLPROJECT_COMBAT_H
#define CMAKESFMLPROJECT_COMBAT_H
#include <SFML/Graphics.hpp>
#include  <iostream>
#include "Entities.h"
#include "Monster.h"
#include "Rhaegal.h"
enum class FightState {
    MainMenu,
    SelectAttack,
    SelectTeam
};
enum class AnimPhase { None, Forward, Wait, Backward };
inline AnimPhase animPhase = AnimPhase::None;
inline sf::Clock animClock;
inline sf::Vector2f originalPos;
inline sf::Vector2f targetPos;
inline float animDuration = 0.3f;

class Fight {
private:
    sf::Sprite mSprite;
    sf::IntRect mSourceRect;
    sf::Texture mTexture;
    sf::Font mFont;
    sf::Text mPv;
    sf::Text mPv2;
    std::vector<sf::RectangleShape> mButtons;
    std::vector<sf::Text> mText;
    sf::RectangleShape mRect;
    sf::RectangleShape mRect2;
public:
    std::vector<std::string> mString;
    FightState m_currentFightState = FightState::MainMenu;
    int mCurrentFightIndex;
    int mMaxFightOptions;
    Fight();
    void CombatLoadTexture(const std::string &filename);
    void draw(sf::RenderWindow &window, Monster &monster, Rhaegal &enemyDragon); //
    void menuFight(const std::vector<std::string>& options);
    void updateAnimation(Monster& monster);
    void startAttackAnim(Monster& monster);
    AnimPhase getAnimPhase() const;
};


#endif //CMAKESFMLPROJECT_COMBAT_H