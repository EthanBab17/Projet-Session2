//
// Created by babin on 2026-05-19.
//

#ifndef CMAKESFMLPROJECT_AUDIO_H
#define CMAKESFMLPROJECT_AUDIO_H
#include <SFML/Audio.hpp>
#include <iostream>

class Audio {
    private:
    sf::Music mBgMusic;
    sf::Music mWildBattleMusic;
    sf::Music mBossBattleMusic;
    public:
    Audio();
    void playMusic();
    void wildBattleMusic();
    void bossBattleMusic();
    void stopMusic();
    sf::SoundSource::Status getStatus();
};


#endif //CMAKESFMLPROJECT_AUDIO_H