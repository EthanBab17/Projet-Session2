//
// Created by babin on 2026-05-19.
//

#include "Audio.h"
Audio::Audio() {
    if (mBgMusic.openFromFile("../../src/Audio/Background.mp3")) {
        mBgMusic.setLooping(true);
        mBgMusic.setVolume(40.f);
    }
    if (mWildBattleMusic.openFromFile("../../src/Audio/Wild-Pokemon-Battle.mp3")) {
        mWildBattleMusic.setLooping(true);
        mWildBattleMusic.setVolume(50.f);
    }
    if (mBossBattleMusic.openFromFile("../../src/Audio/Champion-Battle.mp3")) {
        mBossBattleMusic.setLooping(true);
        mBossBattleMusic.setVolume(50.f);
    }
}
void Audio::playMusic() {

    mBgMusic.setLooping(true);
    mBgMusic.setVolume(50.f);

    mWildBattleMusic.stop();
    mBossBattleMusic.stop();
    mBgMusic.play();
}
void Audio::wildBattleMusic() {

    mWildBattleMusic.setLooping(true);
    mWildBattleMusic.setVolume(50.f);

    mBgMusic.stop();
    mWildBattleMusic.play();
}
void Audio::bossBattleMusic() {

    mBossBattleMusic.setLooping(true);
    mBossBattleMusic.setVolume(50.f);

    mBgMusic.stop();
    mBossBattleMusic.play();
}
void Audio::stopMusic() {

}
sf::SoundSource::Status Audio::getStatus() {
    return mBgMusic.getStatus();
}
