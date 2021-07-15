#ifndef _H_MUSIC_MANAGER_H_
#define _H_MUSIC_MANAGER_H_

#include <vector>
#include "SdlMusic.h"

class MusicManager
{
    std::vector<SdlMusic> queue;
    unsigned int current_pos;

    public:
        /*!
         * public constructor
         */
        MusicManager();
        /*!
         * singleton acess
         */
        static MusicManager & getObject();
        /*!
         * returns music queue
         */
        std::vector<SdlMusic> & getQueue();
        /*!
         * Adds song to queue
         */
        void addMusic(std::string);
        /*!
         * play queued music
         */
        bool play(int loops=1);
        /*!
         * pauses playing music
         */
        static void pause();
        /*!
         * stops playing music
         */
        static void stop();
        /*!
         * indicates wheter anythin is playing
         */
        static bool isPlaying();
        /*!
         * clears/resets queue
         */
        void resetQueue();
        /*!
         * returns true if apath music is in queue
         * @onlyMy checks if only apath music is in queue
         */
        bool isMyMusicPlaying(std::string apath, bool onlyMy);
};

#endif
