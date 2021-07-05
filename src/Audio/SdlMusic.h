#ifndef __H_AUDIO__
#define __H_AUDIO__

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
        bool play();
        void pause();
        void close();
};

#endif // __H_AUDIO__
