/*
 * MainController.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include <SDL2/SDL_ttf.h>

#include "MainController.h"
#include "MainConfiguration.h"

#include "config.h"
#include "time.h"


MainController::MainController() {
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize time with seed
    srand (time(NULL));

    config = &MainConfiguration::getConfig();

    //config.setWidth(WIDTH);
    //config.setHeight(HEIGHT);

    window = SDL_CreateWindow(
        "Keyboard master",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config->getWidth(),
        config->getHeight(),
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }

    if (TTF_Init() != 0)  {
    	printf("Could not initialize TTF");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    setFullScreen();

    machine.load(renderer, window);
}

void MainController::setFullScreen()
{
	SDL_DisplayMode DM, windowMode;
	SDL_GetCurrentDisplayMode(0, &DM);

	SDL_GetWindowDisplayMode(window, &windowMode);

	windowMode.h = DM.h;
	windowMode.w = DM.w;

	config->setWindowSize(DM.w, DM.h);

	SDL_SetWindowDisplayMode(window, &windowMode);

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void MainController::run() {
	machine.write();
}

MainController::~MainController() {
	machine.close();

	SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

