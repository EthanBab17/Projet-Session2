//
// Created by babin on 2026-04-27.
//

#include "GamePlay.h"

GamePlay::GamePlay()
    : mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "Game", sf::Style::None)
      , mIsMovingUp(false)
      , mIsMovingDown(false)
      , mIsMovingLeft(false)
      , mIsMovingRight(false)
      , mWildEnemy(nullptr) {
    mPlayer.loadTexture("../../src/Sprite/Player.png");
    mPlayer.setPosition({860.f, 0.f});
    mPnj.loadTexture("../../src/Sprite/Master.png");
    mPlayerTeam.push_back(new GiantParrot());
    if (!mPlayerTeam.empty() && mPlayerTeam[0] != nullptr) {
        mPlayerTeam[0]->loadTexture("../../src/Sprite/Parrot.png");
        mPlayerTeam[0]->setPosition({50.f, 0.f});
        mPlayerTeam[0]->setSpriteScale({1.f, 1.f});
    }
    mRhaegal.setPosition({1700.f, -120.f});
    mRhaegal.setSpriteScale({-0.7f, 0.7f});

    if (!mFont.openFromFile("../../src/RetroText.ttf")) {
        std::cerr << "Erreur de chargement de la police !" << std::endl;
    }
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
    bossFight = false;
    storageDraw = false;
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
                if (bossFight) {
                    int atk = (rand() % 3);
                    mFight.startAttackAnimEnemy(mRhaegal);
                    mRhaegal.attack(atk, *mPlayerTeam[mActiveMonsterIndex]);
                } else {
                    mFight.startAttackAnimEnemy(*mWildEnemy);
                    mWildEnemy->attack(1, *mPlayerTeam[mActiveMonsterIndex]);
                }
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
                if (playerTurn) {
                    mFight.updateAnimation(mRhaegal);
                } else {
                    mFight.updateAnimation(*mPlayerTeam[mActiveMonsterIndex]);
                }
                mFight.draw(mWindow, *(mPlayerTeam[mActiveMonsterIndex]), mRhaegal);
            } else if (!mPlayerTeam.empty() && mPlayerTeam[0] != nullptr && mWildEnemy != nullptr) {
                if (playerTurn) {
                    mFight.updateAnimation(*mWildEnemy);
                } else {
                    mFight.updateAnimation(*mPlayerTeam[mActiveMonsterIndex]);
                }
                mFight.draw(mWindow, *(mPlayerTeam[mActiveMonsterIndex]), *mWildEnemy);
            } else {
                std::cerr << "Erreur : L'equipe est vide, impossible de combattre !" << std::endl;
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
            if (storageDraw == true) {
                sf::RectangleShape dimOverlay;
                dimOverlay.setSize(sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
                dimOverlay.setFillColor(sf::Color(0, 0, 0, 150));

                for (size_t i = 0; i < mRectangle.size(); ++i) {
                    if (i == mStorageIndex) {
                        mRectangle[i].setOutlineColor(sf::Color::Green);
                        mRectangle[i].setOutlineThickness(4);
                    } else {
                        mRectangle[i].setOutlineColor(sf::Color::White);
                        mRectangle[i].setOutlineThickness(2);
                    }

                    mWindow.draw(mRectangle[i]);
                }
                mWindow.draw(dimOverlay);

                drawStorage(mWindow);
            }
        }
    }
    mWindow.display();
}

void GamePlay::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Key::Escape && isPressed) {
        if (!inMenu) {
            inMenu = true;
            storageDraw = false;
        }
        return;
    }
    if (key == sf::Keyboard::Key::M && isPressed) {
        storageDraw = !storageDraw;
        std::cout << "État du Storage : " << (storageDraw ? "Ouvert" : "Fermé") << std::endl;
    }
    if (storageDraw && isPressed) {
        mIsMovingUp = false;
        mIsMovingDown = false;
        mIsMovingLeft = false;
        mIsMovingRight = false;
        if (key == sf::Keyboard::Key::Up) {
            mStorageIndex = (mStorageIndex - 1 + maxStorageIndex) % maxStorageIndex;
        }
        if (key == sf::Keyboard::Key::Down) {
            mStorageIndex = (mStorageIndex + 1 + maxStorageIndex) % maxStorageIndex;
        }
        if (key == sf::Keyboard::Key::Enter) {
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
                mFight.mCurrentFightIndex = (mFight.mCurrentFightIndex - 1 + mFight.mMaxFightOptions) % mFight.
                                            mMaxFightOptions;
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
        mMap.addTallGrass(sf::FloatRect({(618 * windowlength / 900), (377 * windowHeight / 507)}, {389.f, 312.f}));
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
                << mPlayer.getPosition().y << "\n";
        for (size_t i = 0; i < mPlayerTeam.size(); ++i) {
            if (mPlayerTeam[i] != nullptr) {
                dataRecording << "TEAM,"
                              << mPlayerTeam[i]->getName() << ","
                              << mPlayerTeam[i]->getLevel() << ","
                              << mPlayerTeam[i]->getCurrentExp() << "\n";
            }
        }

        // Lignes Sac : "STORAGE",Slot,Type,Niveau,Exp
        for (auto const& [slot, monster] : mStorage) {
            if (monster != nullptr) {
                dataRecording << "STORAGE,"
                              << slot << ","
                              << monster->getName() << ","
                              << monster->getLevel() << ","
                              << monster->getCurrentExp() << "\n";
            }
        }
    }
}

void GamePlay::loadGame() {
    std::string type;
    int level, exp, pv;
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
            for (Monster *m: mPlayerTeam) {
                delete m;
            }
            mPlayerTeam.clear();

            for (auto const &[slot, monster]: mStorage) {
                delete monster;
            }
            mStorage.clear();

            while (std::getline(loading, line)) {
                if (line.empty()) continue;

                std::stringstream ss(line);
                std::string rowType;
                std::getline(ss, rowType, ','); // Détermine si c'est "TEAM" ou "STORAGE"

                int targetSlot = -1;
                std::string monsterType;

                if (rowType == "STORAGE") {
                    std::string slotVal;
                    std::getline(ss, slotVal, ',');
                    targetSlot = std::stoi(slotVal);
                }

                std::getline(ss, monsterType, ',');
                if (monsterType.empty()) continue;

                Monster *loadedMonster = nullptr;
                if (monsterType == "Rhaegal") {
                    loadedMonster = new Rhaegal();
                    loadedMonster->loadTexture("../../src/Sprite/Rhaegal.png");
                } else if (monsterType == "GiantParrot") {
                    loadedMonster = new GiantParrot();
                    loadedMonster->loadTexture("../../src/Sprite/Parrot.png");
                } else if (monsterType == "Tarrasque") {
                    loadedMonster = new Tarrasque();
                    loadedMonster->loadTexture("../../src/Sprite/Tarrasque.png");
                } else if (monsterType == "Snake") {
                    loadedMonster = new Snake();
                    loadedMonster->loadTexture("../../src/Sprite/Snake.png");
                }

                if (loadedMonster != nullptr) {
                    std::string val;

                    std::getline(ss, val, ',');
                    loadedMonster->setLevel(std::stoi(val));

                    std::getline(ss, val, ',');
                    loadedMonster->setCurrentExp(std::stoi(val));

                    // Config de base d'affichage
                    loadedMonster->setPosition({50.f, 0.f});
                    loadedMonster->setSpriteScale({1.f, 1.f});

                    if (rowType == "TEAM") {
                        mPlayerTeam.push_back(loadedMonster);
                    } else if (rowType == "STORAGE" && targetSlot != -1) {
                        mStorage[targetSlot] = loadedMonster;
                    }
                }
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
            mWildEnemy = nullptr;
        } else {
            Monster *clonedMonster = nullptr;
            if (wildMonster->getName() == "Rhaegal") {
                clonedMonster = new Rhaegal();
            } else if (wildMonster->getName() == "GiantParrot") {
                clonedMonster = new GiantParrot();
            } else if (wildMonster->getName() == "Tarrasque") {
                clonedMonster = new Tarrasque();
            } else if (wildMonster->getName() == "Snake") {
                clonedMonster = new Snake();
            } else {
                clonedMonster = new GiantParrot();
            }

            clonedMonster->setLevel(wildMonster->getLevel());
            clonedMonster->setCurrentExp(wildMonster->getCurrentExp());

            int freeSlot = 0;
            while (mStorage.find(freeSlot) != mStorage.end()) {
                freeSlot++;
            }
            mStorage[freeSlot] = clonedMonster;
            std::cout << wildMonster->getName() << " a ete envoye dans le sac !" << std::endl;

            delete wildMonster;
            mWildEnemy = nullptr;
        }
        inMenuFight = false;
    } else {
        std::cout << wildMonster->getName() << " n'a pas été capturé" << std::endl;
        playerTurn = false;
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
            if (mPlayerTeam.size() > 1 && mPlayerTeam[1] != nullptr) {
                mActiveMonsterIndex = 1;
                mFight.m_currentFightState = FightState::MainMenu;
                playerTurn = false;
                mTurnClock.restart();
            } else {
                std::cout << "Pas de monstre a l'emplacement 2 !" << std::endl;
            }
        }

        if (mFight.mCurrentFightIndex == 2) {
            if (mPlayerTeam.size() > 2 && mPlayerTeam[2] != nullptr) {
                mActiveMonsterIndex = 2;
                mFight.m_currentFightState = FightState::MainMenu;
                playerTurn = false;
                mTurnClock.restart();
            } else {
                std::cout << "Pas de monstre a l'emplacement 3 !" << std::endl;
            }
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
            captureMonster(mWildEnemy);
        } else if (mFight.mCurrentFightIndex == 3) {
            inMenuFight = false;
        }
    } else if (mFight.m_currentFightState == FightState::SelectAttack) {
        if (mFight.mCurrentFightIndex == 0) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(0, *mWildEnemy);
            std::cout << mWildEnemy->getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 1) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(1, *mWildEnemy);
            std::cout << mWildEnemy->getActualPv() << std::endl;
            playerTurn = false;
            mTurnClock.restart();
        }
        if (mFight.mCurrentFightIndex == 2) {
            mFight.startAttackAnim(*mPlayerTeam[mActiveMonsterIndex]);
            mPlayerTeam[mActiveMonsterIndex]->attack(2, *mWildEnemy);

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
            if (mPlayerTeam.size() > 1 && mPlayerTeam[1] != nullptr) {
                mActiveMonsterIndex = 1;
                mFight.m_currentFightState = FightState::MainMenu;
                playerTurn = false;
                mTurnClock.restart();
            } else {
                std::cout << "Pas de monstre a l'emplacement 2 !" << std::endl;
            }
        }

        if (mFight.mCurrentFightIndex == 2) {
            if (mPlayerTeam.size() > 2 && mPlayerTeam[2] != nullptr) {
                mActiveMonsterIndex = 2;
                mFight.m_currentFightState = FightState::MainMenu;
                playerTurn = false;
                mTurnClock.restart();
            } else {
                std::cout << "Pas de monstre a l'emplacement 3 !" << std::endl;
            }
        }
        if (mFight.mString[mFight.mCurrentFightIndex] == "Back") {
            mFight.m_currentFightState = FightState::MainMenu;
            mFight.menuFight({"Attack", "Team", "Capture", "Run"});
        }
    }
}

void GamePlay::switchMonster(size_t teamIndex, int storageKey) {
    if (teamIndex >= mPlayerTeam.size()) {
        return;
    }
    if (mStorage.find(storageKey) == mStorage.end()) {
        return;
    }

    // 2. Le mécanisme d'échange (Swap)
    Monster *temp = mPlayerTeam[teamIndex];
    mPlayerTeam[teamIndex] = mStorage[storageKey];

    if (temp != nullptr) {
        mStorage[storageKey] = temp;
    } else {
        mStorage.erase(storageKey);
    }

    std::cout << "Echange effectue avec succes !" << std::endl;
}

void GamePlay::drawStorage(sf::RenderWindow &window) {
    float X = windowlength / 2;
    float Y = 200.f;
    float spacingY = 120.f;

    if (mStorage.size() > 0) {
        int count = 0;
        for (auto const &[slot, monster]: mStorage) {
            if (monster != nullptr) {
                sf::Text infoText(mFont);
                infoText.setString(
                    "Case " + std::to_string(slot) + " : " + monster->getName() + " Lvl " + std::to_string(
                        monster->getLevel()));
                infoText.setCharacterSize(24);
                infoText.setFillColor(sf::Color::White);
                sf::FloatRect bounds = infoText.getLocalBounds();
                infoText.setOrigin({
                    bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f
                });
                infoText.setPosition({X + 100.f, Y + (count * spacingY)});
                window.draw(infoText);
                for (size_t i = 0; i < mStorage.size(); ++i) {
                    sf::RectangleShape rect({500, 100});
                    rect.setFillColor(sf::Color(50, 50, 50, 200));
                    rect.setOutlineThickness(2);
                    rect.setOutlineColor(sf::Color::White);
                    float posX = X - (rect.getSize().x / 2.f);
                    float posY = Y + (i * spacingY);
                    rect.setPosition({posX, posY});
                    mRectangle.push_back(rect);
                }

                sf::Vector2f originalPos = monster->getSpritePosition();
                sf::Vector2f originalScale = monster->getSpriteScale();
                monster->setSpriteScale({0.2f, 0.2f});
                monster->setPosition({X, Y + (count * spacingY)});

                monster->draw(window); // Ou window.draw(monster->mSprite);

                monster->setSpriteScale(originalScale);
                monster->setPosition(originalPos);
                count++;
                maxStorageIndex++;
            }
        }
    } else {
        sf::Text infoText(mFont);
        infoText.setString("No monster in the storage");
        infoText.setCharacterSize(24);
        infoText.setFillColor(sf::Color::White);
        sf::FloatRect bounds = infoText.getLocalBounds();
        infoText.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        });
        infoText.setPosition({X, Y});
        window.draw(infoText);
    }
}
