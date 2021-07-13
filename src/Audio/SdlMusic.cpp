
#include <iostream>
#include "SdlMusic.h"

SdlMusic::SdlMusic()
{
    music = NULL;
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

bool SdlMusic::play(int loops)
{
	std::cout << "Playing music!" << std::endl;

    if (Mix_PlayMusic(music, loops) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void SdlMusic::pause()
{
    Mix_PauseMusic();
}

void SdlMusic::close()
{
    if (music != NULL)
    {
        Mix_FreeMusic(music);
        music = NULL;
    }
}

bool SdlMusic::isPlaying()
{
    return (bool)Mix_PlayingMusic();
}

bool SdlMusic::isPaused()
{
    return (bool)Mix_PausedMusic();
}

void SdlMusic::rewind()
{
    Mix_RewindMusic();
}

void SdlMusic::resume()
{
    Mix_ResumeMusic();
}
