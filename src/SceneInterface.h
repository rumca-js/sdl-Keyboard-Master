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

class SceneInterface
{
public:
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
    /*!
     * \brief Provied destructor. Otherwise compiler would complain.
     */
    virtual ~SceneInterface() {}
    /*!
     * \brief returns scene name. Used by scene configuration
     */
    virtual std::string getName() = 0;
    /*!
     * handles events
     */
    virtual int handleEvents() = 0;
};


#endif /* SCENEINTERFACE_H_ */
