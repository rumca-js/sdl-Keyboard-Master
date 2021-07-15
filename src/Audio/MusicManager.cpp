
#include <iostream>
#include "MusicManager.h"

MusicManager & MusicManager::getObject()
{
    static MusicManager man;
    return man;
}

MusicManager::MusicManager()
{
    current_pos = 0;
}

std::vector<SdlMusic> & MusicManager::getQueue()
{
    return queue;
}

void MusicManager::addMusic(std::string aMusic)
{
   SdlMusic music;
   queue.push_back(music);
   queue[queue.size()-1].open(aMusic);
}

bool MusicManager::play(int loops)
{
  if (SdlMusic::isPaused())
  {
      SdlMusic::resume();
      queue[current_pos].play(loops);
  }
  else if (!SdlMusic::isPlaying())
  {
      queue[current_pos].play(loops);
      return true;
  }
  return false;
}

void MusicManager::pause()
{
  std::cout << "MusicManager::pause"<<std::endl;
   SdlMusic::pause();
}

void MusicManager::stop()
{
  std::cout << "MusicManager::stop"<<std::endl;
  SdlMusic::pause();
  SdlMusic::rewind();
}

void MusicManager::resetQueue()
{
   queue.clear();
}

bool MusicManager::isMyMusicPlaying(std::string apath, bool onlyMy)
{
    if (onlyMy) {
        if (queue.size() == 1 && queue[1].getName() == apath) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        for(unsigned int i=0; i<queue.size(); i++) {
            if (queue[i].getName() == apath) {
                return true;
            }
        }
        return false;
    }
}

bool MusicManager::isPlaying()
{
	return SdlMusic::isPlaying();
}
