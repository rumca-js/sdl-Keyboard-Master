
#include <iostream>
#include "SdlMusic.h"

SdlMusic::SdlMusic()
{
}

SdlMusic::SdlMusic(std::string path)
{
    open(path);
}

bool SdlMusic::open(std::string path)
{
    music = Mix_LoadMUS(path.c_str() );
    if (!music)
    {
        std::cout << "Cannot load music" << std::endl;
        return false;
    }

    return true;
}

SdlMusic::~SdlMusic()
{
    close();
}

bool SdlMusic::play()
{
    if (Mix_PlayMusic(music, 1) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void SdlMusic::pause()
{
    //Mix_FadeInMusic(musicq);
}

void SdlMusic::close()
{
    if (music != NULL)
    {
        Mix_FreeMusic(music);
        music = NULL;
    }
}
