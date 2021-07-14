
#include "GameEventLogger.h"

GameEventLogger & GameEventLogger::getObject()
{
   static GameEventLogger logger;
   return logger;
}

void GameEventLogger::setScenes(unsigned int size)
{
  sceneLog.resize(size);
}

void GameEventLogger::sceneStart(unsigned int scene)
{
    current_scene = scene;
    sceneLog[current_scene].time_start = std::chrono::steady_clock::now();
    sceneLog[current_scene].keySuccessful = 0;
    sceneLog[current_scene].keyFailed = 0;
}

void GameEventLogger::sceneStop(unsigned int scene)
{
    sceneLog[current_scene].time_stop = std::chrono::steady_clock::now();
}

void GameEventLogger::addSuccessfulKeyStroke()
{
    sceneLog[current_scene].keySuccessful++;
}

void GameEventLogger::addUnSuccessfulKeyStroke()
{
    sceneLog[current_scene].keyFailed++;
}

unsigned int GameEventLogger::getSuccessfulKeyStrokes()
{
    return sceneLog[current_scene].keySuccessful;
}

unsigned int GameEventLogger::getUnSuccessfulKeyStrokes()
{
    return sceneLog[current_scene].keyFailed;
}
