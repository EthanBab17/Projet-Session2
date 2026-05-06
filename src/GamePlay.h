//
// Created by babin on 2026-04-27.
//

#ifndef CMAKESFMLPROJECT_GAMEPLAY_H
#define CMAKESFMLPROJECT_GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Player.h"
#include "Map.h"
#include <cmath>
#include "Menu.h"
#include "Door.h"
#include "Pnj.h"
#include "Rhaegal.h"
#include "RenderText.h"
#include "Fight.h"

class GamePlay {
private:
    sf::RenderWindow mWindow;
    Player mPlayer;
    Pnj mPnj;
    Rhaegal mRhaegal;
    Rhaegal mRhaegal2;
    Map mMap;
    RenderText mRenderText;
    Menu mMenu;
    bool inMenu;
    Fight mFight;
    bool inMenuFight;
    bool playerTurn = true;
    sf::Clock mTurnClock;
    Door mDoor;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool collisionDetected;
private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void map1Down();
    void map1Left();
    void map2();
    void map3();
    void HouseIn();
    void HouseOut();
public:
    GamePlay();
    void run();
};


#endif //CMAKESFMLPROJECT_GAMEPLAY_H