//
// Created by babin on 2026-04-27.
//

#include "GamePlay.h"

GamePlay::GamePlay()
    : mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()),"Game", sf::Style::None)
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false) {
    mPlayer.loadTexture("../../src/Sprite/Player.png");
    mPlayer.setPosition({860.f, 0.f});
    mPnj.loadTexture("../../src/Sprite/Master.png");
    mRhaegal.loadTexture("../../src/Sprite/Rhaegal.png");
    mRhaegal.setPosition({100.f, 50.f});
    mRhaegal.mSprite.setScale({1.f, 1.f});

    mRhaegal2.loadTexture("../../src/Sprite/Rhaegal.png");
    mRhaegal2.setPosition({1700.f, -120.f});
    mRhaegal2.mSprite.setScale({-0.7f, 0.7f});

    mWindow.setFramerateLimit(60);
    mMap.loadTexture("../../src/Sprite/Map1.png");
    mMap.mCurrentMapIndex = 0;
    mMap.setPosition({0.f,0.f});
    mFight.CombatLoadTexture("../../src/Sprite/FightSprite.png");
    mFight.menuFight({"Attacks","Team", "Run"});
    mMenu.menuLoadTexture("../../src/Sprite/Map2.png");
    float lenght = (static_cast<float>(mWindow.getSize().x)/2);
    float width = ((static_cast<float>(mWindow.getSize().y)/2)-100.f);
    mMenu.init(lenght,width);
    mMenu.setPosition({0.f, 0.f});
    inMenu = true;
    inMenuFight = false;
}


void GamePlay::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GamePlay::processEvents() {
    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            mWindow.close();
        }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    inMenu = true;
                    // mWindow.close();
                }
                handlePlayerInput(keyPressed->code, true);
            }
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                handlePlayerInput(keyReleased->code, false);
            }
        }
}
void GamePlay::update() {
    if (inMenu) {

    }else if(inMenuFight) {
            if (!playerTurn) {

                if (mTurnClock.getElapsedTime().asSeconds() > 1.5f) {

                    int damage = 10; // Remplace par une vraie fonction mEnemy.attack(
                    mRhaegal.takeDamage(damage);

                    std::cout << "L'ennemi attaque ! Vos PV : " << mRhaegal.getPv() << std::endl;
                    mFight.m_currentFightState = FightState::MainMenu;
                    mFight.menuFight({"Attacks", "Team", "Run"});
                    playerTurn = true;
                }
            }
        if (mRhaegal.getPv() < 0 || mRhaegal2.getPv() < 0) {
            inMenuFight = false;
            mRhaegal.resetPv();
            mRhaegal2.resetPv();
            if (mRhaegal.getPv() > 0) {
                mRhaegal.gainExp(100);
            }
        }
    }else {
        sf::Vector2f oldPosition = mPlayer.getPosition();
        sf::Vector2f movement(0.f, 0.f);
        if (mIsMovingUp) {
            movement.y -= 5.f;
            mPlayer.setDirection(2);
        }
        if (mIsMovingDown) {
            movement.y += 5.f;
            mPlayer.setDirection(0);
        }
        if (mIsMovingLeft) {
            movement.x -= 5.f;
            mPlayer.setDirection(3);
        }
        if (mIsMovingRight) {
            movement.x += 5.f ;
            mPlayer.setDirection(1);
        }
        mPlayer.move(movement, 3.f);

        if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
            for (const auto& wall : mMap.mMapsHitboxes[mMap.mCurrentMapIndex]) {
                collisionDetected = false;
                for (const auto& wall : mMap.mMapsHitboxes[mMap.mCurrentMapIndex]) {
                    if (mPlayer.mhitbox.findIntersection(wall)) {
                        collisionDetected = true;
                    }
                }
                if (collisionDetected) {
                    mPlayer.setPosition(oldPosition);
                    mPlayer.mhitbox.position.x = (oldPosition.x + 20);
                    mPlayer.mhitbox.position.y = (oldPosition.y + 100);
                }
            }
        }

        if (mPlayer.getPosition().y < -150.f && mMap.mCurrentMapIndex != 1) {
            map2();
        }
        if (mPlayer.getPosition().y > 1150.f && mMap.mCurrentMapIndex != 0 && mMap.mCurrentMapIndex != 3) {
            map1Down();
        }
        if (mPlayer.getPosition().x > 1900.f && mMap.mCurrentMapIndex != 2) {
            map3();
        }
        if (mPlayer.getPosition().x < -50.f && mMap.mCurrentMapIndex != 0) {
            map1Left();
        }
        if (mPlayer.mhitbox.findIntersection(mDoor.mhitboxes[0]) && mMap.mCurrentMapIndex == 2) {
            HouseIn();
        }
        if (mPlayer.mhitbox.findIntersection(mDoor.mhitboxes[1]) && mMap.mCurrentMapIndex == 3) {
            HouseOut();
        }
        if (mPlayer.mhitbox.findIntersection(mPnj.mPnjHitboxes[0][0]) && mMap.mCurrentMapIndex == 3) {
            collisionDetected = true;
            mPlayer.setPosition(oldPosition);
            mPlayer.mhitbox.position.x = (oldPosition.x + 20);
            mPlayer.mhitbox.position.y = (oldPosition.y + 100);
        }
        if (mPlayer.mhitbox.findIntersection(mPnj.mPnjHitboxes[0][1]) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && mMap.mCurrentMapIndex == 3){
            inMenuFight = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            inMenuFight = true;
        }
    }
}
void GamePlay::render() {
    mWindow.clear();
    if (inMenu) {
        mMenu.draw(mWindow);
    }else {
        if (inMenuFight) {
            // m_combatSystem.draw(mWindow);
            mFight.draw(mWindow, mRhaegal, mRhaegal2);
            // mWindow.clear(sf::Color::Red);
        }else {
            mMap.draw(mWindow);
            if (mMap.mCurrentMapIndex == 3) {
                mPnj.draw(mWindow);
            }
            if (mPlayer.mhitbox.findIntersection(mPnj.mhitboxes[1])) {
                float width = ((static_cast<float>(mWindow.getSize().y)-100.f));
                mRenderText.CombatText(0, width, mWindow);
            }
            mPlayer.draw(mWindow);
        // mRhaegal.draw(mWindow);
    }
    }
    mWindow.display();
}
void GamePlay::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (inMenu && isPressed) {
        if (key == sf::Keyboard::Key::Up) {
            mMenu.mCurrentMenuIndex = (mMenu.mCurrentMenuIndex - 1 + mMenu.mMaxMenuOptions) % mMenu.mMaxMenuOptions;
        }
        if (key == sf::Keyboard::Key::Down) {
            mMenu.mCurrentMenuIndex = (mMenu.mCurrentMenuIndex + 1) % mMenu.mMaxMenuOptions;
        }
        if (key == sf::Keyboard::Key::Enter) {
            if (mMenu.mCurrentMenuIndex == 0) {
                inMenu = false;
            }
            if (mMenu.mCurrentMenuIndex == 1) {
                mWindow.close();
                std::ofstream dataRecording("data.csv");
                if (dataRecording.is_open()) {
                    dataRecording << mMap.mCurrentMapIndex;
                    dataRecording << mRhaegal.getPv();
                }
            }
        }
    }
    if (!inMenu) {
        if (inMenuFight && isPressed && playerTurn) {
            if (key == sf::Keyboard::Key::Up) {
                mFight.mCurrentFightIndex = (mFight.mCurrentFightIndex - 1 + mFight.mMaxFightOptions) % mFight.mMaxFightOptions;
            }
            if (key == sf::Keyboard::Key::Down) {
                mFight.mCurrentFightIndex = (mFight.mCurrentFightIndex + 1) % mFight.mMaxFightOptions;
            }
            if (key == sf::Keyboard::Key::Enter) {
                if (mFight.m_currentFightState == FightState::MainMenu) {
                    if (mFight.mCurrentFightIndex == 0) {
                        mFight.m_currentFightState = FightState::SelectAttack;
                        mFight.menuFight({"FireBall", "wingSlash", "DracoMeteor", "Back"});
                    }
                    else if (mFight.mCurrentFightIndex == 1) {
                        // Logique pour le menu "Team"
                    }else if (mFight.mCurrentFightIndex == 2) {
                        inMenuFight = false;
                    }
                }
                else if (mFight.m_currentFightState == FightState::SelectAttack) {
                    if (mFight.mCurrentFightIndex == 0) {
                        mRhaegal2.takeDamage(mRhaegal.fireBall());
                        std::cout << mRhaegal2.getPv() << std::endl;
                        playerTurn = false;
                        mTurnClock.restart();
                    }
                    if (mFight.mCurrentFightIndex == 1) {
                        mRhaegal2.takeDamage(mRhaegal.wingSlash());
                        std::cout << mRhaegal2.getPv() << std::endl;
                        playerTurn = false;
                        mTurnClock.restart();
                    }
                    if (mFight.mCurrentFightIndex == 2) {
                        mRhaegal2.takeDamage(mRhaegal.dracoMeteore());
                        std::cout << mRhaegal2.getPv() << std::endl;
                        playerTurn = false;
                        mTurnClock.restart();
                    }
                    if (mFight.mString[mFight.mCurrentFightIndex] == "Back") {
                        mFight.m_currentFightState = FightState::MainMenu;
                        mFight.menuFight({"Attack", "Team", "Run"});
                        }
                    } else {
                        std::cout << "Lancement de l'attaque : " << mFight.mString[mFight.mCurrentFightIndex] << std::endl;
                    }
            }
        }
        if (key == sf::Keyboard::Key::W  || key == sf::Keyboard::Key::Up) {
            mIsMovingUp = isPressed;
        }else if (key == sf::Keyboard::Key::S || key == sf::Keyboard::Key::Down) {
            mIsMovingDown = isPressed;
        }else if (key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::Left) {
            mIsMovingLeft = isPressed;
        }else if (key == sf::Keyboard::Key::D || key == sf::Keyboard::Key::Right) {
            mIsMovingRight = isPressed;
        }
        if (key == sf::Keyboard::Key::P) {
            mRhaegal.gainExp(50);
        }
    }
}

void GamePlay::map1Down() {
    mMap.mCurrentMapIndex=0;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Sprite/Map1.png");
        float windowHeight = static_cast<float>(mWindow.getSize().y);
        mPlayer.setPosition({ mPlayer.getPosition().x,   windowHeight - 1200.f});
    }
}
void GamePlay::map1Left() {
    mMap.mCurrentMapIndex=0;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Sprite/Map1.png");
        float windowlength = static_cast<float>(mWindow.getSize().x);
        mPlayer.setPosition({windowlength - 70.f, mPlayer.getPosition().y});
    }
}
void GamePlay::map2() {
    mMap.mCurrentMapIndex=1;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Sprite/Map2.png");
        float windowHeight = static_cast<float>(mWindow.getSize().y);
        mPlayer.setPosition({ mPlayer.getPosition().x, windowHeight - 200.f });
    }
}
void GamePlay::map3() {
    mMap.mCurrentMapIndex=2;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Sprite/Map3.png");
        float windowlength = static_cast<float>(mWindow.getSize().x);
        mPlayer.setPosition({windowlength - 1890.f, mPlayer.getPosition().y});
    }
}
void GamePlay::HouseIn() {
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.mCurrentMapIndex=3;
        mMap.loadTexture("../../src/Sprite/House.png");
        mPnj.setPosition({950,600});
        mPnj.initPnj(0);
        float windowlength = static_cast<float>(mWindow.getSize().x);
        float windowwidth = static_cast<float>(mWindow.getSize().y);
        mPlayer.setPosition({windowlength /2, windowwidth - 250.f});
    }
}
void GamePlay::HouseOut() {
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.mCurrentMapIndex=2;
        mMap.loadTexture("../../src/Sprite/Map3.png");
        mPlayer.setPosition({1150, 565});
        mPnj.initPnj(1);

    }
}