/*
 * MainController.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include "MainController.h"
#include "MainConfiguration.h"

#include "config.h"
#include "time.h"


MainController::MainController() {
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize time with seed
    srand (time(NULL));

    MainConfiguration config = MainConfiguration::getConfig();

    //config.setWidth(WIDTH);
    //config.setHeight(HEIGHT);

    window = SDL_CreateWindow(
        "An SDL2 window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config.getWidth(),
        config.getHeight(),
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }

    if (TTF_Init() != 0)     {
    	printf("Could not initialize TTF");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	iscene.init(renderer, window);
	gscene.init(renderer, window);

	state = STATE_MENU;
}

int MainController::run() {

	int status;

	while(true) {
		if (state == STATE_MENU) {
			status = iscene.write();
			if (status == MenuScene::SCENE_EXIT) {
				return 0;
			}
			if (status == MenuScene::SCENE_FINISHED)  {
				state = STATE_GAME;
			}
		}
		if (state == STATE_GAME)  {
			gscene.reset();
			status = gscene.write();
			if (status == GameScene::SCENE_EXIT)  {
				return 0;
			}
			if (status == GameScene::SCENE_FINISHED)  {
				state = STATE_MENU;
			}
		}
	}

	return 0;
}

MainController::~MainController() {
	iscene.close();
	gscene.close();
	SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

