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
#include <vector>
#include "Letter.h"

class GameScene {
    SDL_Renderer *renderer = NULL;
    TTF_Font* Sans = NULL;

    SDL_Texture *wall = NULL;

    int w, h;
    SDL_Window * window;
    std::vector<Letter> letters;
    SDL_TimerID my_timer_id;

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
	bool move_letters();
	void display_letters();
	/**
	 * @brief Closes the scene, disposes elements.
	 */
	void close();
	virtual ~GameScene();
};

#endif /* GAMESCENE_H_ */
