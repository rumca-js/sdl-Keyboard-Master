/*
 * MainController.h
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#ifndef MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"



class MainController {
	SDL_Window *window;
	MenuScene iscene;
	GameScene gscene;
	SDL_Renderer *renderer = NULL;
	int state;

public:
	static const int STATE_MENU = 0;
	static const int STATE_GAME = 1;

	/**
	 * \brief Creates the window
	 */
	MainController();
	/**
	 * \brief Draws on window (polls scenes to draw on the window)
	 */
	int run();
	/**
	 * \brief Cleans up
	 */
	virtual ~MainController();
};

#endif /* MAINCONTROLLER_H_ */
