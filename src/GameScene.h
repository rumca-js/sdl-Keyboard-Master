/*
 * GameScene.h
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class GameScene {
    SDL_Renderer *renderer = NULL;

    SDL_Texture *wall = NULL;
    SDL_Texture* Message = NULL;

    int w, h;
    SDL_Window * window;

public:
	GameScene();
	/**
	 * @brief Performs initialization
	 */
	void init(SDL_Window * window);
	/**
	 * @brief Writes scene on the window
	 */
	void write();
	/**
	 * @brief Closes the scene, disposes elements.
	 */
	void close();
	virtual ~GameScene();
};

#endif /* GAMESCENE_H_ */
