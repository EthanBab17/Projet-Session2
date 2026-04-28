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
    , mPlayer() {
    mPlayer.loadTexture("../../src/Player.png");
    mPlayer.setPosition({0.f, 0.f});
    mWindow.setFramerateLimit(60);
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
                mWindow.close();
            }
            handlePlayerInput(keyPressed->code, true);
        }

        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            handlePlayerInput(keyReleased->code, false);
        }
    }
}
void GamePlay::update() {
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
        movement.x += 5.f;
        mPlayer.setDirection(1);
    }
    mPlayer.move(movement, 3.f);
}
void GamePlay::render() {
    mWindow.clear();
    mPlayer.draw(mWindow);
    mWindow.display();
}
void GamePlay::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Key::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::Key::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::Key::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::Key::D)
        mIsMovingRight = isPressed;
}