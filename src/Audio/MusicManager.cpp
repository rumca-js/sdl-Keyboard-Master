
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

bool MusicManager::play()
{
  if (SdlMusic::isPaused())
  {
      SdlMusic::resume();
      queue[current_pos].play(1);
  }
  else if (!SdlMusic::isPlaying())
  {
      queue[current_pos].play(1);
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
