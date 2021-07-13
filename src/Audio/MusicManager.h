#ifndef _H_MUSIC_MANAGER_H_
#define _H_MUSIC_MANAGER_H_

#include <vector>
#include "SdlMusic.h"

class MusicManager
{
    std::vector<SdlMusic> queue;
    unsigned int current_pos;

    public:
        MusicManager();
        static MusicManager & getObject();
        std::vector<SdlMusic> & getQueue();
        void addMusic(std::string);
        bool play();
        static void pause();
        static void stop();
        void resetQueue();
};

#endif
