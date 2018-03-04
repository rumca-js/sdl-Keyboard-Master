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
#include "GameScene.h"


class MainController {
	SDL_Window *window;
	GameScene scene;

public:
	/**
	 * @brief Creates the window
	 */
	MainController();
	/**
	 * @brief Draws on window (polls scenes to draw on the window)
	 */
	int run();
	/**
	 * @brief Cleans up
	 */
	virtual ~MainController();
};

#endif /* MAINCONTROLLER_H_ */
