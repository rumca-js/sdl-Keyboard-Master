/*
 * SceneInterface.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef SCENEINTERFACE_H_
#define SCENEINTERFACE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class SceneInterface
{
protected:
    /**
     * scene parameters
     */
    std::map<std::string, std::string> sceneInfo;

public:
    /*!
     * \brief Provied destructor. Otherwise compiler would complain.
     */
    virtual ~SceneInterface() {}
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


#endif /* SCENEINTERFACE_H_ */
