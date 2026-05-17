//
// Created by babin on 2026-04-27.
//

#include "GamePlay.h"

GamePlay::GamePlay()
    : mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "Game", sf::Style::None)
      , mIsMovingUp(false)
      , mIsMovingDown(false)
      , mIsMovingLeft(false)
      , mIsMovingRight(false) {
    mPlayer.loadTexture("../../src/Sprite/Player.png");
    mPlayer.setPosition({860.f, 0.f});
    mPnj.loadTexture("../../src/Sprite/Master.png");
    // mRhaegal.setPosition({100.f, 50.f});
    // mRhaegal.mSprite.setScale({1.f, 1.f});
    // mPlayerTeam.push_back(new Rhaegal());
    // if (!mPlayerTeam.empty() && mPlayerTeam[0] != nullptr) {
    //     mPlayerTeam[0]->loadTexture("../../src/Sprite/Rhaegal.png");
    //     mPlayerTeam[0]->setPosition({50.f, 0.f});
    //     mPlayerTeam[0]->setSpriteScale({1.f, 1.f});
    // }
    mPlayerTeam.push_back(new GiantParrot());
    if (!mPlayerTeam.empty() && mPlayerTeam[0] != nullptr) {
        mPlayerTeam[0]->loadTexture("../../src/Sprite/Parrot.png");
        mPlayerTeam[0]->setPosition({50.f, 0.f});
        mPlayerTeam[0]->setSpriteScale({1.f, 1.f});
    }
    // mPlayerTeam.push_back(new Tarrasque());
    // if (!mPlayerTeam.empty() && mPlayerTeam[2] != nullptr) {
    //     mPlayerTeam[2]->loadTexture("../../src/Sprite/Tarrasque.png");
    //     mPlayerTeam[2]->setPosition({100.f, 100.f});
    //     mPlayerTeam[2]->setSpriteScale({0.8f, 0.8f});
    // }
    mRhaegal.setPosition({1700.f, -120.f});
    mRhaegal.setSpriteScale({-0.7f, 0.7f});

    mWindow.setFramerateLimit(60);
    mMap.loadTexture("../../src/Sprite/Map1.png");
    mMap.setCurrentMapIndex(0);
    mMap.setPosition({0.f, 0.f});
    mFight.CombatLoadTexture("../../src/Sprite/FightSprite.png");
    mFight.menuFight({"Attacks", "Team", "Run"});
    mMenu.menuLoadTexture("../../src/Sprite/Map2.png");
    mMenu.init((windowlength / 2), ((windowHeight / 2) - 100.f));
    mMenu.setPosition({0.f, 0.f});
    inMenu = true;
    inMenuFight = false;
}

GamePlay::~GamePlay() {
    if (mWildEnemy != nullptr) {
        delete mWildEnemy;
    }
    for (Monster *m: mPlayerTeam) {
        delete m;
    }
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
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handlePlayerInput(keyPressed->code, true);
        }
        if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            handlePlayerInput(keyReleased->code, false);
        }
    }
}

void GamePlay::update() {
    if (inMenu) {
    } else if (inMenuFight) {
        if (!playerTurn) {
            if (mTurnClock.getElapsedTime().asSeconds() > 1.5f) {
                int damage = 10; // Remplace par une vraie fonction mEnemy.attack(
                mPlayerTeam[mActiveMonsterIndex]->takeDamage(damage);

                std::cout << "L'ennemi attaque ! Vos PV : " << mPlayerTeam[mActiveMonsterIndex]->getActualPv() <<
                        std::endl;
                mFight.m_currentFightState = FightState::MainMenu;
                if (bossFight) {
                    mFight.menuFight({"Attacks", "Team", "Run"});
                } else {
                    mFight.menuFight({"Attacks", "Team", "Capture", "Run"});
                }
                playerTurn = true;
            }
        }
        bool playerDead = mPlayerTeam[mActiveMonsterIndex]->getActualPv() <= 0;
        bool enemyDead = false;

        if (bossFight) {
            enemyDead = (mRhaegal.getActualPv() <= 0);
        } else if (mWildEnemy != nullptr) {
            enemyDead = (mWildEnemy->getActualPv() <= 0);
        }

        if ((playerDead || enemyDead) && mFight.getAnimPhase() == AnimPhase::None) {
            mPlayerTeam[mActiveMonsterIndex]->resetAtk();
            if (mPlayerTeam[mActiveMonsterIndex]->getActualPv() > 0) {
                mPlayerTeam[mActiveMonsterIndex]->gainExp(100);
            }
            mActiveMonsterIndex = 0;
            inMenuFight = false;
            bossFight = false;
            mWildEnemy = nullptr;
            for (size_t i = 0; i < mPlayerTeam.size(); i++) {
                mPlayerTeam[i]->resetPv();
            }
            mRhaegal.resetPv();
            playerTurn = true;
        }
    } else {
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
            movement.x += 5.f;
            mPlayer.setDirection(1);
        }
        mPlayer.move(movement, 3.f);
        if (mMap.getCurrentMapIndex() < mMap.getHitboxes().size()) {
            for (const auto &wall: mMap.getHitboxes()[mMap.getCurrentMapIndex()]) {
                collisionDetected = false;
                for (const auto &wall: mMap.getHitboxes()[mMap.getCurrentMapIndex()]) {
                    if (mPlayer.getHitbox().findIntersection(wall)) {
                        collisionDetected = true;
                    }
                }
                if (collisionDetected) {
                    mPlayer.setPosition(oldPosition);
                    mPlayer.setHitboxPos(oldPosition);
                }
            }
        }

        if (mPlayer.getPosition().y < -150.f && mMap.getCurrentMapIndex() != 1) {
            map2();
        }
        if (mPlayer.getPosition().y > 1150.f && mMap.getCurrentMapIndex() != 0 && mMap.getCurrentMapIndex() != 3) {
            map1Down();
        }
        if (mPlayer.getPosition().x > 1900.f && mMap.getCurrentMapIndex() != 2) {
            map3();
        }
        if (mPlayer.getPosition().x < -50.f && mMap.getCurrentMapIndex() != 0) {
            map1Left();
        }
        if (mPlayer.getHitbox().findIntersection(mDoor.mhitboxes[0]) && mMap.getCurrentMapIndex() == 2) {
            HouseIn();
        }
        if (mPlayer.getHitbox().findIntersection(mDoor.mhitboxes[1]) && mMap.getCurrentMapIndex() == 3) {
            HouseOut();
        }
        if (mPlayer.getHitbox().findIntersection(mPnj.mPnjHitboxes[0][0]) && mMap.getCurrentMapIndex() == 3) {
            collisionDetected = true;
            mPlayer.setPosition(oldPosition);
            mPlayer.setHitboxPos(oldPosition);
        }
        if (mPlayer.getHitbox().findIntersection(mPnj.mPnjHitboxes[0][1]) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && mMap.getCurrentMapIndex() == 3) {
            bossFight = true;
            inMenuFight = true;
        }
        if (mMap.getCurrentMapIndex() == 1) {
            checkGrassCollision();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            startWildFight();
            inMenuFight = true;
        }
    }
}

void GamePlay::render() {
    mWindow.clear();
    if (inMenu) {
        mMenu.draw(mWindow);
    } else {
        if (inMenuFight) {
            if (!mPlayerTeam.empty() && mPlayerTeam[0] != nullptr && bossFight == true) {
                mFight.updateAnimation(*mPlayerTeam[mActiveMonsterIndex]);
                mFight.draw(mWindow, *(mPlayerTeam[mActiveMonsterIndex]), mRhaegal);
            } else if (!mPlayerTeam.empty() && mPlayerTeam[0] != nullptr && mWildEnemy != nullptr) {
                mFight.updateAnimation(*mPlayerTeam[mActiveMonsterIndex]);
                mFight.draw(mWindow, *(mPlayerTeam[mActiveMonsterIndex]), *mWildEnemy);
            } else {
                // std::cerr << "Erreur : L'equipe est vide, impossible de combattre !" << std::endl;
                inMenuFight = false;
            }
        } else {
            mMap.draw(mWindow);
            if (mMap.getCurrentMapIndex() == 1 || mMap.getCurrentMapIndex() == 2) {
                if (mMap.getTallGrass().size() > 0) {
                    for (const auto &grassRect: mMap.getTallGrass()) {
                        sf::RectangleShape debugShape;

                        // On donne au rectangle de debug la taille exacte de la zone d'herbe
                        debugShape.setSize({grassRect.size.x, grassRect.size.y});

                        // On le positionne aux coordonnées exactes de la zone
                        debugShape.setPosition({grassRect.position.x, grassRect.position.y});

                        // Vert semi-transparent (Rouge, Vert, Bleu, Alpha/Transparence)
                        // 100 permet de voir ton décor à travers le rectangle
                        debugShape.setFillColor(sf::Color(0, 255, 0, 100));

                        // Bordure verte opaque pour bien voir les limites du rectangle
                        debugShape.setOutlineColor(sf::Color::Green);
                        debugShape.setOutlineThickness(2.f);

                        // On l'affiche à l'écran
                        mWindow.draw(debugShape);
                    }
                }
            }
            if (mMap.getCurrentMapIndex() == 3) {
                mPnj.draw(mWindow);
                if (mPlayer.getHitbox().findIntersection(mPnj.mPnjHitboxes[0][1])) {
                    mRenderText.CombatText(0, (windowHeight - 100.f), mWindow);
                }
            }
            mPlayer.draw(mWindow);
            // mRhaegal.draw(mWindow);
        }
    }
    mWindow.display();
}

void GamePlay::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Key::Escape && isPressed) {
        if (!inMenu) {
            inMenu = true;
        }
        return;
    }
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
                loadGame();
                inMenu = false;
            }
            if (mMenu.mCurrentMenuIndex == 2) {
                inMemory();
            }
            if (mMenu.mCurrentMenuIndex == 3) {
                mWindow.close();
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
                if (bossFight == true) {
                    bossFightMenu();
                } else {
                    wildFightMenu();
                }
            }
        }
        if (key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::Up) {
            mIsMovingUp = isPressed;
        } else if (key == sf::Keyboard::Key::S || key == sf::Keyboard::Key::Down) {
            mIsMovingDown = isPressed;
        } else if (key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::Left) {
            mIsMovingLeft = isPressed;
        } else if (key == sf::Keyboard::Key::D || key == sf::Keyboard::Key::Right) {
            mIsMovingRight = isPressed;
        }
        if (key == sf::Keyboard::Key::P) {
            mPlayerTeam[mActiveMonsterIndex]->gainExp(50);
            std::cout << mPlayerTeam[mActiveMonsterIndex]->getActualPv() << std::endl;
        }
    }
}

void GamePlay::map1Down() {
    mMap.setCurrentMapIndex(0);
    if (mMap.getCurrentMapIndex() < mMap.getHitboxes().size()) {
        mMap.loadTexture("../../src/Sprite/Map1.png");
        mMap.clearZones();
        mPlayer.setPosition({mPlayer.getPosition().x, windowHeight - 1200.f});
    }
}

void GamePlay::map1Left() {
    mMap.setCurrentMapIndex(0);
    if (mMap.getCurrentMapIndex() < mMap.getHitboxes().size()) {
        mMap.loadTexture("../../src/Sprite/Map1.png");
        mMap.clearZones();
        mPlayer.setPosition({windowlength - 70.f, mPlayer.getPosition().y});
    }
}

void GamePlay::map2() {
    mMap.setCurrentMapIndex(1);
    if (mMap.getCurrentMapIndex() < mMap.getHitboxes().size()) {
        mMap.loadTexture("../../src/Sprite/Map2.png");
        mMap.clearZones();
        mMap.addTallGrass(sf::FloatRect({118, 95}, {389, 312}));
        mMap.addTallGrass(sf::FloatRect({115, 500}, {389, 312}));
        mMap.addTallGrass(sf::FloatRect({1378, 95}, {389, 312}));
        mMap.addTallGrass(sf::FloatRect({1380, 510}, {389, 312}));
        mPlayer.setPosition({mPlayer.getPosition().x, windowHeight - 200.f});
    }
}

void GamePlay::map3() {
    mMap.setCurrentMapIndex(2);
    if (mMap.getCurrentMapIndex() < mMap.getHitboxes().size()) {
        mMap.loadTexture("../../src/Sprite/Map3.png");
        mMap.clearZones();
        mMap.addTallGrass(sf::FloatRect({(618*windowlength/900), (377*windowHeight/507)}, {389.f, 312.f}));
        mPlayer.setPosition({windowlength - (windowlength - 25), mPlayer.getPosition().y});
    }
}

void GamePlay::HouseIn() {
    mMap.setCurrentMapIndex(3);
    if (mMap.getCurrentMapIndex() < mMap.getHitboxes().size()) {
        mMap.loadTexture("../../src/Sprite/House.png");
        mPnj.setPosition({950, 600});
        mPnj.initPnj(0);
        mMap.clearZones();

        mPlayer.setPosition({windowlength / 2, windowHeight - 250.f});
    }
}

void GamePlay::HouseOut() {
    mMap.setCurrentMapIndex(2);
    if (mMap.getCurrentMapIndex() < mMap.getHitboxes().size()) {
        mMap.loadTexture("../../src/Sprite/Map3.png");
        mMap.clearZones();
        mPlayer.setPosition({1150, 565});
        mPnj.initPnj(1);
    }
}

void GamePlay::inMemory() {
    std::ofstream dataRecording("../../src/data.csv");
    if (dataRecording.is_open()) {
        dataRecording << mMap.getCurrentMapIndex() << ","
                << mPlayer.getPosition().x << ","
                << mPlayer.getPosition().y;
        for (size_t i = 0; i < mPlayerTeam.size(); ++i) {
            dataRecording << "," << mPlayerTeam[i]->getLevel() << ","
                    << mPlayerTeam[i]->getCurrentExp();
        }
    }
}

void GamePlay::loadGame() {
    std::ifstream loading("../../src/data.csv");
    if (loading.is_open()) {
        std::string line;
        if (std::getline(loading, line)) {
            std::stringstream ss(line);

            std::string val;
            std::getline(ss, val, ',');
            mMap.setCurrentMapIndex(std::stoi(val));

            std::getline(ss, val, ',');
            float posX = std::stof(val);

            std::getline(ss, val, ',');
            float posY = std::stof(val);

            mPlayer.setPosition({posX, posY});

            if (mMap.getCurrentMapIndex() == 1) mMap.loadTexture("../../src/Sprite/Map2.png");
            else if (mMap.getCurrentMapIndex() == 2) mMap.loadTexture("../../src/Sprite/Map3.png");
            else if (mMap.getCurrentMapIndex() == 3) {
                mMap.loadTexture("../../src/Sprite/House.png");
                mPnj.setPosition({950, 600});
                mPnj.initPnj(0);
            } else mMap.loadTexture("../../src/Sprite/Map1.png");
            for (size_t i = 0; i < mPlayerTeam.size(); ++i) {
                std::getline(ss, val, ',');
                mPlayerTeam[i]->setLevel(stoi(val));

                std::getline(ss, val, ',');
                mPlayerTeam[i]->setCurrentExp(stoi(val));
            }
            std::cout << "Chargement reussi : Map " << mMap.getCurrentMapIndex() << std::endl;
        }
        loading.close();
    }
}

void GamePlay::checkGrassCollision() {
    if (!mIsMovingUp && !mIsMovingDown && !mIsMovingLeft && !mIsMovingRight) {
        return;
    }
    sf::FloatRect playerBounds = mPlayer.getHitbox();

    for (const auto &grassRect: mMap.getTallGrass()) {
        if (playerBounds.findIntersection(grassRect)) {
            if (stepClock.getElapsedTime().asSeconds() > 0.5f && (
                    mIsMovingUp || mIsMovingDown || mIsMovingLeft || mIsMovingRight)) {
                if (rand() % 100 < 20) {
                    startWildFight();
                }
                stepClock.restart();
            }
            break;
        }
    }
}

void GamePlay::captureMonster(Monster *wildMonster) {
    if (rand() % 3 < 1) {
        if (mPlayerTeam.size() < 3) {
            mPlayerTeam.push_back(wildMonster);
            std::cout << wildMonster->getName() << " a rejoint votre equipe !" << std::endl;
        } else {
            mStorage.push_back(wildMonster);
            std::cout << wildMonster->getName() << " a ete envoye dans le sac !" << std::endl;
        }
    }
}

void GamePlay::startWildFight() {
    if (mWildEnemy != nullptr) {
        delete mWildEnemy;
        mWildEnemy = nullptr;
    }

    int randomChoice = rand() % 100;

    if (randomChoice < 10) {
        mWildEnemy = new Rhaegal();
        mWildEnemy->loadTexture("../../src/Sprite/Rhaegal.png");
        mWildEnemy->setSpriteScale({-1.f, 1.f});
        mWildEnemy->setPosition({1300.f, 250.f});
    } else if (randomChoice > 10 && randomChoice < 30) {
        mWildEnemy = new GiantParrot();
        mWildEnemy->loadTexture("../../src/Sprite/Parrot.png");
        mWildEnemy->setSpriteScale({1.f, 1.f});
        mWildEnemy->setPosition({1300.f, 250.f});
    } else if (randomChoice > 30 && randomChoice < 35) {
        mWildEnemy = new Tarrasque();
        mWildEnemy->loadTexture("../../src/Sprite/Tarrasque.png");
        mWildEnemy->setSpriteScale({0.8f, 0.8f});
        mWildEnemy->setPosition({1300.f, 250.f});
    } else if (randomChoice > 35 && randomChoice < 50) {
        mWildEnemy = new Snake();
        mWildEnemy->loadTexture("../../src/Sprite/Snake.png");
        mWildEnemy->setSpriteScale({0.75f, 0.75f});
        mWildEnemy->setPosition({900.f, 100.f});
    } else {
        mWildEnemy = new GiantParrot();
        mWildEnemy->loadTexture("../../src/Sprite/Parrot.png");
        mWildEnemy->setSpriteScale({1.f, 1.f});
        mWildEnemy->setPosition({1300.f, 250.f});
    }

    mFight.m_currentFightState = FightState::MainMenu;
    mFight.menuFight({"Attack", "Team", "Capture", "Run"});

    inMenuFight = true;
    playerTurn = true;
}

// Monster *GamePlay::generateWildMonster() {
//     int r = rand() % 10;
//     if (r == 0) {
//         return new Rhaegal();
//     }else if (r == 1) {
//         return new Tarrasque();
//     }else if (r == 2) {
//         return new GiantParrot();
//     }else if (r == 3) {
//         return new Snake();
//     }else{
//     return new GiantParrot();
//     }
// }
void GamePlay::bossFightMenu() {
    if (mFight.m_currentFightState == FightState::MainMenu) {
        if (mFight.mCurrentFightIndex == 0) {
            mFight.m_currentFightState = FightState::SelectAttack;
            mFight.menuFight({
                mPlayerTeam[mActiveMonsterIndex]->getAttackName(0), mPlayerTeam[mActiveMonsterIndex]->getAttackName(1),
                mPlayerTeam[mActiveMonsterIndex]->getAttackName(2), "Back"
            });
        } else if (mFight.mCurrentFightIndex == 1) {
            std::vector<std::string> teamNames;
            for (auto &member: mPlayerTeam) {
                teamNames.push_back(member->getName() + "Lvl " + std::to_string(member->getLevel()));
            }
            teamNames.push_back("Back");
            mFight.menuFight(teamNames);
            mFight.m_currentFightState = FightState::SelectTeam;
        } else if (mFight.mCurrentFightIndex == 2) {
            captureMonster(mWildEnemy);
        } else if (mFight.mCurrentFightIndex == 3) {
            inMenuFight = false;
        }
    } else if (mFight.m_currentFightState == FightState::SelectAttack) {
        if (mFight.mCurrentFightIndex == 0) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(0, mRhaegal);
            std::cout << mRhaegal.getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 1) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(1, mRhaegal);
            std::cout << mRhaegal.getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 2) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(2, mRhaegal);

            std::cout << mRhaegal.getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mString[mFight.mCurrentFightIndex] == "Back") {
            mFight.m_currentFightState = FightState::MainMenu;
            mFight.menuFight({"Attacks", "Team", "Capture", "Run"});
        }
    } else if (mFight.m_currentFightState == FightState::SelectTeam) {
        if (mFight.mCurrentFightIndex == 0) {
            mActiveMonsterIndex = 0;
            mFight.m_currentFightState = FightState::MainMenu;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 1) {
            mActiveMonsterIndex = 1;
            mFight.m_currentFightState = FightState::MainMenu;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 2) {
            mActiveMonsterIndex = 2;
            mFight.m_currentFightState = FightState::MainMenu;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mString[mFight.mCurrentFightIndex] == "Back") {
            mFight.m_currentFightState = FightState::MainMenu;
            mFight.menuFight({"Attack", "Team", "Capture", "Run"});
        }
    }
}

void GamePlay::wildFightMenu() {
    if (mFight.m_currentFightState == FightState::MainMenu) {
        if (mFight.mCurrentFightIndex == 0) {
            mFight.m_currentFightState = FightState::SelectAttack;
            mFight.menuFight({
                mPlayerTeam[mActiveMonsterIndex]->getAttackName(0), mPlayerTeam[mActiveMonsterIndex]->getAttackName(1),
                mPlayerTeam[mActiveMonsterIndex]->getAttackName(2), "Back"
            });
        } else if (mFight.mCurrentFightIndex == 1) {
            std::vector<std::string> teamNames;
            for (auto &member: mPlayerTeam) {
                teamNames.push_back(member->getName() + "Lvl " + std::to_string(member->getLevel()));
            }
            teamNames.push_back("Back");
            mFight.menuFight(teamNames);
            mFight.m_currentFightState = FightState::SelectTeam;
        } else if (mFight.mCurrentFightIndex == 2) {
            inMenuFight = false;
            bossFight = false;
        }
    } else if (mFight.m_currentFightState == FightState::SelectAttack) {
        if (mFight.mCurrentFightIndex == 0) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(0, mRhaegal);
            std::cout << mWildEnemy->getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 1) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(1, mRhaegal);
            std::cout << mWildEnemy->getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 2) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(2, mRhaegal);

            std::cout << mWildEnemy->getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mString[mFight.mCurrentFightIndex] == "Back") {
            mFight.m_currentFightState = FightState::MainMenu;
            mFight.menuFight({"Attacks", "Team", "Capture", "Run"});
        }
    } else if (mFight.m_currentFightState == FightState::SelectTeam) {
        if (mFight.mCurrentFightIndex == 0) {
            mActiveMonsterIndex = 0;
            mFight.m_currentFightState = FightState::MainMenu;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 1) {
            mActiveMonsterIndex = 1;
            mFight.m_currentFightState = FightState::MainMenu;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 2) {
            mActiveMonsterIndex = 2;
            mFight.m_currentFightState = FightState::MainMenu;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mString[mFight.mCurrentFightIndex] == "Back") {
            mFight.m_currentFightState = FightState::MainMenu;
            mFight.menuFight({"Attack", "Team", "Capture", "Run"});
        }
    }
}
