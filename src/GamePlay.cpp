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
    , mMap()
    , mMenu()
{
    mPlayer.loadTexture("../../src/Player.png");
    mPlayer.setPosition({860.f, 0.f});
    mWindow.setFramerateLimit(60);
    mMap.loadTexture("../../src/Map1.png");
    mMap.mCurrentMapIndex = 0;
    mMap.setPosition({0.f,0.f});
    mMenu.menuLoadTexture("../../src/Map2.png");
    mMenu.setPosition({0.f, 0.f});
    inMenu = true;
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
                bool collisionDetected = false;
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
        if (mPlayer.getPosition().y > 1150.f && mMap.mCurrentMapIndex != 0) {
            map1Down();
        }
        if (mPlayer.getPosition().x > 1900.f && mMap.mCurrentMapIndex != 2) {
            map3();
        }
        if (mPlayer.getPosition().x < -50.f && mMap.mCurrentMapIndex != 0) {
            map1Left();
        }
    }
}
void GamePlay::render() {
    mWindow.clear();
    if (inMenu) {
        mMenu.draw(mWindow);
        for (int i = 0; i < mMenu.mMaxMenuOptions; ++i) {
            sf::RectangleShape button({200.f, 50.f});
            sf::Vector2f position = {400.f, 200.f + (i * 70.f)};
            button.setPosition(position);

            if (i == mMenu.mCurrentMenuIndex) {
                button.setFillColor(sf::Color::Yellow);
            }else {
                button.setFillColor(sf::Color(100, 100, 100));
            }
            mWindow.draw(button);
            sf::Text text(mMenu.mFont);
            text.setString(mMenu.mMenuOptions[i]);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);

            // 3. CENTRAGE DU TEXTE
            // On récupère la taille du texte pour le placer pile au milieu
            sf::FloatRect textBounds = text.getGlobalBounds();

            // Calcul : Position du bouton + (Taille bouton / 2) - (Taille texte / 2)
            float textX = position.x + (200.f / 2.f) - (textBounds.position.x / 2.f);
            float textY = position.y + (50.f / 2.f) - (textBounds.position.y); // Ajustement Y subtil

            text.setPosition({textX, textY});

            mWindow.draw(text);
        }
    }else {
        mMap.draw(mWindow);
        mPlayer.draw(mWindow);
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
            // On valide le choix
            if (mMenu.mCurrentMenuIndex == 0) inMenu = false; // "Play" : on lance le jeu
            if (mMenu.mCurrentMenuIndex == 1) mWindow.close(); // "Quit" : on ferme
        }
    }
    if (!inMenu) {
        if (key == sf::Keyboard::Key::W)
            mIsMovingUp = isPressed;
        else if (key == sf::Keyboard::Key::S)
            mIsMovingDown = isPressed;
        else if (key == sf::Keyboard::Key::A)
            mIsMovingLeft = isPressed;
        else if (key == sf::Keyboard::Key::D)
            mIsMovingRight = isPressed;
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
