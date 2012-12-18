/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "DefaultSounds.h"
#include "Error.h"
#include "Log.h"
#include <SDL/SDL_mixer.h>

using std::string;

DefaultSounds::DefaultSounds() 
:   on(true), 
    isinit(false)
{
    //set sound paths
    sndPaths[0] = "sound/intro.wav";
    sndPaths[1] = "sound/munch_a.wav";
    sndPaths[2] = "sound/munch_b.wav";
    sndPaths[3] = "sound/large_pellet.wav";
    sndPaths[4] = "sound/ghost_eat.wav";
    sndPaths[5] = "sound/fruit.wav";
    sndPaths[6] = "sound/extra_man.wav";
    sndPaths[7] = "sound/vuln.wav";
    sndPaths[8] = "sound/death.wav";
    sndPaths[9] = "sound/newgame.wav";
    sndPaths[10] = "sound/siren.wav";
    sndPaths[11] = "sound/intermission.wav";
    sndPaths[12] = "sound/booster.wav";

    //initialize SDL mixer
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 512;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
        throw_exception("Error while initializing SDL");

    Mix_AllocateChannels(NUMOFSOUNDS);

    //load wav files
    int i;
    for (i=0;i<NUMOFSOUNDS;i++) {
        snd[i].reset(Mix_LoadWAV(sndPaths[i].c_str()), Mix_FreeChunk);
        if ( snd[i] == NULL )
            throw_exception(Mix_GetError());
    }

    isinit = true;
    logtxt.print("Sounds loaded successfully");
}

DefaultSounds::~DefaultSounds()
{
    Mix_CloseAudio();
}

void DefaultSounds::toggleSounds() {
    if ( on ) {
        on = false;
        stop();
    }
    else
        on = true;
}
void DefaultSounds::stop() {
    int i;
    for (i=0;i<NUMOFSOUNDS;i++)
        stop(i);
}

void DefaultSounds::stop(int i) {
    if ( !isinit ) return;
    if (Mix_Playing(i))
        Mix_HaltChannel(i);
}

void DefaultSounds::play(int i, bool looped, int volume) {
    if ( !isinit ) return;
    if (!on) return;

    if (Mix_Playing(i))
        Mix_HaltChannel(i);

    int loop = 0;
    if ( looped )
        loop = -1;

    Mix_Volume(i,volume);
    Mix_PlayChannel(i,snd[i].get(),loop);
}

