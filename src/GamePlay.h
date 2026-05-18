//
// Created by babin on 2026-04-27.
//

#ifndef CMAKESFMLPROJECT_GAMEPLAY_H
#define CMAKESFMLPROJECT_GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "Door.h"
#include "Pnj.h"
#include "Monster.h"
#include "Rhaegal.h"
#include "GiantParrot.h"
#include "Snake.h"
#include "Tarrasque.h"
#include "RenderText.h"
#include "Fight.h"

class GamePlay {
private:
    sf::RenderWindow mWindow;
    float windowlength = static_cast<float>(mWindow.getSize().x);
    float windowHeight = static_cast<float>(mWindow.getSize().y);
    Player mPlayer;
    Pnj mPnj;
    std::vector<Monster*> mPlayerTeam;
    Monster* mWildEnemy = nullptr;
    int mActiveMonsterIndex = 0;
    Rhaegal mRhaegal;
    Map mMap;
    RenderText mRenderText;
    sf::Font mFont;
    Menu mMenu;
    bool inMenu;
    Fight mFight;
    bool bossFight;
    bool inMenuFight;
    bool playerTurn = true;
    bool storageDraw = false;
    sf::Clock mTurnClock;
    Door mDoor;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool collisionDetected;
    std::map<int, Monster*> mStorage;
    std::vector<sf::RectangleShape> mRectangle;
    int mStorageIndex = 0;
    int maxStorageIndex = 0;
    sf::Clock stepClock;
public:
    GamePlay();
    ~GamePlay();
    void run();
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
    void inMemory();
    void loadGame();
    void checkGrassCollision();
    void captureMonster(Monster* wildMonster);
    void startWildFight();
    Monster* generateWildMonster();
    void bossFightMenu();
    void wildFightMenu();
    void switchMonster(size_t teamIndex, int storageKey);
    void drawStorage(sf::RenderWindow& window);
};


#endif //CMAKESFMLPROJECT_GAMEPLAY_H