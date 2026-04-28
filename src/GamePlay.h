//
// Created by babin on 2026-04-27.
//

#ifndef CMAKESFMLPROJECT_GAMEPLAY_H
#define CMAKESFMLPROJECT_GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include "Player.h"
class GamePlay {
private:
    sf::RenderWindow mWindow;
    Player mPlayer;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
public:
    GamePlay();
    void run();
};


#endif //CMAKESFMLPROJECT_GAMEPLAY_H