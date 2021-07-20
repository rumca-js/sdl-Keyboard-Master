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
    virtual void init() override;
    /*!
     \brief Writes the scene.
     \returns the scene return code.
    */
    virtual int write() override;
    /*!
     \brief Closes scene.
    */
    virtual void close() override;
    /**
     * called when scene is entered
     */
    virtual void onEnter() override;
    /**
     * called when we leave scene
     */
    virtual void onLeave() override;
    /*!
     * \brief returns scene unique name. Used by scene configuration
     */
    virtual std::string getName() override;
    /*!
     * handles events
     */
    virtual int handleEvents() override;
};

#endif
