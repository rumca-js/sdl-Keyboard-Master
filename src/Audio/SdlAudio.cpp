
#include <iostream>
#include "SdlAudio.h"

SdlAudio::SdlAudio()
{
}

SdlAudio::SdlAudio(std::string path)
{
	open(path);
}

bool SdlAudio::open(std::string path)
{
	std::cout << "Load wav" << std::endl;

	chunk = Mix_LoadWAV( path.c_str() );
	if (!chunk)
	{
		std::cout << "Cannot load chunk" << std::endl;
		return false;
	}
	return true;
}

SdlAudio::~SdlAudio()
{
	close();
}

bool SdlAudio::play()
{
	if (Mix_PlayChannel( -1, chunk, 0 ) == -1 )
    {
        printf("Mix_PlayChannel: %s\n", Mix_GetError());
		return false;
    }
	return true;
}

void SdlAudio::pause()
{
	//Mix_FadeInMusic(musicq);
}

void SdlAudio::close()
{
	if (chunk != NULL)
	{
		Mix_FreeChunk(chunk);
		chunk = NULL;
	}
}
