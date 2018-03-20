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

    if (TTF_Init() != 0)     {
    	printf("Could not initialize TTF");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    setFullScreen();

	iscene.init(renderer, window);
	mscene.init(renderer, window);
	gscene.init(renderer, window);

	state = STATE_INTRO;
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

int MainController::run() {

	int status;

	while(true) {
		if (state == STATE_INTRO) {
			status = iscene.write();
			if (status == MenuScene::SCENE_EXIT) {
				return 0;
			}
			if (status == MenuScene::SCENE_FINISHED)  {
				state = STATE_MENU;
			}
		}
		if (state == STATE_MENU) {
			status = mscene.write();
			if (status == MenuScene::SCENE_EXIT) {
				return 0;
			}
			if (status == MenuScene::SCENE_FINISHED)  {
				state = STATE_GAME;
			}
		}
		if (state == STATE_GAME)  {
			status = gscene.write();
			if (status == GameScene::SCENE_EXIT)  {
				state = STATE_MENU;
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
	mscene.close();
	gscene.close();
	SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

