#ifndef _H_SCENECOMMONS_H_
#define _H_SCENECOMMONS_H_

#include "SceneInterface.h"

class SceneCommons : public SceneInterface
{
  public:
    virtual void MakeSureMyMusicIsPlaying();
    /*!
     \brief Initializes scene.
    */
    virtual void init() = 0;
    /*!
     \brief Writes the scene.
     \returns the scene return code.
    */
    virtual int write() = 0;
    /*!
     \brief Closes scene.
    */
    virtual void close() = 0;
    /**
     * called when scene is entered
     */
    virtual void onEnter() = 0;
    /**
     * called when we leave scene
     */
    virtual void onLeave() = 0;
    /*!
     * \brief returns scene unique name. Used by scene configuration
     */
    virtual std::string getName() = 0;
    /*!
     * handles events
     */
    virtual int handleEvents() = 0;
};

#endif
