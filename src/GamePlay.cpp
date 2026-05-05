//
// Created by babin on 2026-04-27.
//

#include "GamePlay.h"

GamePlay::GamePlay()
    : mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()),"Game", sf::Style::None)
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
    , mPlayer()
    ,mPnj()
    ,mRhaegal()
    , mMap()
    , mMenu()
    , mDoor()
{
    mPlayer.loadTexture("../../src/Player.png");
    mPlayer.setPosition({860.f, 0.f});
    mPnj.loadTexture("../../src/Master.png");
    // mRhaegal.loadTexture("../../src/Rhaegal.png");
    // mRhaegal.setPosition({860.f, 600.f});
    mWindow.setFramerateLimit(60);
    mMap.loadTexture("../../src/Map1.png");
    mMap.mCurrentMapIndex = 0;
    mMap.setPosition({0.f,0.f});
    mMenu.menuLoadTexture("../../src/Map2.png");
    float lenght = (static_cast<float>(mWindow.getSize().x)/2);
    float width = ((static_cast<float>(mWindow.getSize().y)/2)-100.f);
    mMenu.init(lenght,width);
    mMenu.setPosition({0.f, 0.f});
    inMenu = true;
    inCombat = false;
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

    }else {
        sf::Vector2f oldPosition = mPlayer.getPosition();
        std::cout << "Nombre de murs sur cette map : " << mMap.mMapsHitboxes[mMap.mCurrentMapIndex].size() << std::endl;
        std::cout << mPlayer.getPosition().x << " " << mPlayer.getPosition().y << std::endl;
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
        if (mPlayer.mhitbox.findIntersection(mPnj.mhitboxes[0])) {
            collisionDetected = true;
            mPlayer.setPosition(oldPosition);
            mPlayer.mhitbox.position.x = (oldPosition.x + 20);
            mPlayer.mhitbox.position.y = (oldPosition.y + 100);
        }
        if (mPlayer.mhitbox.findIntersection(mPnj.mhitboxes[1]) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
            inCombat = true;
        }
    }
}
void GamePlay::render() {
    mWindow.clear();
    if (inMenu) {
        mMenu.draw(mWindow);
    }else {
        if (inCombat) {
            // m_combatSystem.draw(mWindow);

            mWindow.clear(sf::Color::Red);
        }else {
            mMap.draw(mWindow);
            if (mMap.mCurrentMapIndex == 3) {
                mPnj.draw(mWindow);
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
            if (mMenu.mCurrentMenuIndex == 0) inMenu = false;
            if (mMenu.mCurrentMenuIndex == 1) mWindow.close();
        }
    }
    if (!inMenu) {
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
            mRhaegal.GainExp(50);
        }
    }
}

void GamePlay::map1Down() {
    mMap.mCurrentMapIndex=0;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Map1.png");
        float windowHeight = static_cast<float>(mWindow.getSize().y);
        mPlayer.setPosition({ mPlayer.getPosition().x,   windowHeight - 1200.f});
    }
}
void GamePlay::map1Left() {
    mMap.mCurrentMapIndex=0;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Map1.png");
        float windowlength = static_cast<float>(mWindow.getSize().x);
        mPlayer.setPosition({windowlength - 70.f, mPlayer.getPosition().y});
    }
}
void GamePlay::map2() {
    mMap.mCurrentMapIndex=1;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Map2.png");
        float windowHeight = static_cast<float>(mWindow.getSize().y);
        mPlayer.setPosition({ mPlayer.getPosition().x, windowHeight - 200.f });
    }
}
void GamePlay::map3() {
    mMap.mCurrentMapIndex=2;
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.loadTexture("../../src/Map3.png");
        float windowlength = static_cast<float>(mWindow.getSize().x);
        mPlayer.setPosition({windowlength - 1890.f, mPlayer.getPosition().y});
    }
}
void GamePlay::HouseIn() {
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.mCurrentMapIndex=3;
        mMap.loadTexture("../../src/House.png");
        mPnj.setPosition({1014,667});
        mPnj.initPnj();
        float windowlength = static_cast<float>(mWindow.getSize().x);
        float windowwidth = static_cast<float>(mWindow.getSize().y);
        mPlayer.setPosition({windowlength /2, windowwidth - 250.f});
    }
}
void GamePlay::HouseOut() {
    if (mMap.mCurrentMapIndex < mMap.mMapsHitboxes.size()) {
        mMap.mCurrentMapIndex=2;
        mMap.loadTexture("../../src/Map3.png");
        mPlayer.setPosition({1150, 565});

    }
}