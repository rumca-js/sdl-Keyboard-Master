#ifndef __H_AUDIO_MUSIC_
#define __H_AUDIO_MUSIC_

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class SdlMusic
{
    Mix_Music *music = NULL;
    public:
        SdlMusic();
        SdlMusic(std::string path);
        bool open(std::string path);
        ~SdlMusic();
        bool play(int loops);
        static void pause();
        void close();
        static bool isPlaying();
        static bool isPaused();
        static void rewind();
        static void resume();
};

#endif // __H_AUDIO__
