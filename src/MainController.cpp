/*
 * MainController.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include "MainController.h"

#include "config.h"
#include "time.h"


MainController::MainController() {
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize time with seed
    srand (time(NULL));

    window = SDL_CreateWindow(
        "An SDL2 window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }

	scene.init(window);
}

int MainController::run()   {
    scene.write();

    return 0;
}

MainController::~MainController() {
	scene.close();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

