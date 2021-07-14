
#ifndef _H_GAMEEVENTLOGGER_H
#define _H_GAMEEVENTLOGGER_H

#include <chrono>
#include <vector>

typedef struct _SceneInformation
{
   unsigned int keyStrokes;
   unsigned int keySuccessful;
   unsigned int keyFailed;
   std::chrono::steady_clock::time_point time_start;
   std::chrono::steady_clock::time_point time_stop;
} SceneInformation;

class GameEventLogger
{
   std::vector<SceneInformation> sceneLog;
   unsigned int current_scene;

   public:
      static GameEventLogger & getObject();
      void setScenes(unsigned int size);
      void sceneStart(unsigned int scene);
      void sceneStop(unsigned int scene);
      void addSuccessfulKeyStroke();
      void addUnSuccessfulKeyStroke();
      unsigned int getSuccessfulKeyStrokes();
      unsigned int getUnSuccessfulKeyStrokes();
};

#endif //_H_GAMEEVENTLOGGER_H
