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

#include "MainConfiguration.h"
#include "SceneMachine.h"

class MainController {
	SDL_Window *window;
	SceneMachine machine;

	SDL_Renderer *renderer = NULL;
	int state;
	MainConfiguration * config;

public:
	/**
	 * \brief Creates the window
	 */
	MainController();
	/**
	 * \brief Draws on window (polls scenes to draw on the window)
	 */
	void run();
	/**
	 * \brief sets to full screen.
	 */
	void setFullScreen();
	/**
	 * \brief Cleans up
	 */
	virtual ~MainController();
};

#endif /* MAINCONTROLLER_H_ */
