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
	virtual void init(SDL_Renderer *renderer, SDL_Window * window) = 0;
	virtual int write() = 0;
	virtual void close() = 0;

	static const int SCENE_EXIT=0;
	static const int SCENE_FINISHED=1;
};


#endif /* SCENEINTERFACE_H_ */
