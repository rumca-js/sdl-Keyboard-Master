#ifndef __H_AUDIO__
#define __H_AUDIO__

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class SdlAudio
{
	Mix_Chunk *chunk = NULL;
	public:
		SdlAudio();
		SdlAudio(std::string path);
        bool open(std::string path);
		~SdlAudio();
		bool play();
        void pause();
		void close();
};

#endif // __H_AUDIO__
