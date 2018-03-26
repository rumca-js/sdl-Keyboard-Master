/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include "MenuScene.h"

#include "../config.h"


MenuScene::MenuScene(SDL_Renderer *ren, SDL_Window * window) {
	fullscreen = false;

	win = window;
	renderer = ren;

	mExit 	= NULL;
	mFull   = NULL;
	mEnter  = NULL;
	wall 	= NULL;
	Sans 	= NULL;

	surf1 = NULL;
	surf2 = NULL;
	surf3 = NULL;

	config = NULL;
}

void MenuScene::init() {

	fullscreen = false;

	config = &MainConfiguration::getConfig();

    Sans = TTF_OpenFont(FONT_NAME, FONT_SIZE);

    wall = IMG_LoadTexture(renderer, IMAGE_MENU);

    SDL_Color color = {0, 0, 255};

	surf1 = TTF_RenderText_Solid(Sans, TEXT_FULL_SCREEN , color);
	mFull = SDL_CreateTextureFromSurface(renderer, surf1);

	surf2 = TTF_RenderText_Solid(Sans, TEXT_ENTER , color);
	mEnter = SDL_CreateTextureFromSurface(renderer, surf2);

	surf3 = TTF_RenderText_Solid(Sans, TEXT_ESCAPE , color);
	mExit = SDL_CreateTextureFromSurface(renderer, surf3);
}
int MenuScene::write() {
	int status = SCENE_EXIT;

	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT) {
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN) {
				status = SCENE_FINISHED;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_f) {
				fullscreen = !fullscreen;

				if (fullscreen) {
					SDL_DisplayMode DM, windowMode;
					SDL_GetCurrentDisplayMode(0, &DM);

					SDL_GetWindowDisplayMode(win, &windowMode);

					windowMode.h = DM.h;
					windowMode.w = DM.w;

					config->setWindowSize(DM.w, DM.h);

					SDL_SetWindowDisplayMode(win, &windowMode);

					SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
				}
				else {
					// TODO do not use WIDTH or HEIGHT definitions directly
					config->setWindowSize(WIDTH, HEIGHT);

					SDL_SetWindowFullscreen(win, 0);
				}
			}
		}

		SDL_RenderClear(renderer);

		unsigned int letter_width = config->getWidth()/50;
		unsigned int letter_height = config->getHeight()/10;

		SDL_Rect rFull; rFull.x = config->getWidth()/3; rFull.y = config->getHeight()*1/4; rFull.w = letter_width * strlen(TEXT_FULL_SCREEN); rFull.h = letter_height;
		SDL_Rect rEnter; rEnter.x = config->getWidth()/3; rEnter.y = config->getHeight()*2/4; rEnter.w = letter_width * strlen(TEXT_ENTER); rEnter.h = letter_height;
		SDL_Rect rExit; rExit.x = config->getWidth()/3; rExit.y = config->getHeight()*3/4; rExit.w = letter_width * strlen(TEXT_ESCAPE); rExit.h = letter_height;

		SDL_Rect texr = config->getFullScreenSize();
		SDL_RenderCopy(renderer, wall, NULL, &texr);

		SDL_RenderCopy(renderer, mFull, NULL, &rFull);
		SDL_RenderCopy(renderer, mEnter, NULL, &rEnter);
		SDL_RenderCopy(renderer, mExit, NULL, &rExit);

		SDL_RenderPresent(renderer);
	}

	return status;
}
void MenuScene::close() {
	SDL_DestroyTexture(wall);
	TTF_CloseFont(Sans);
	SDL_FreeSurface(surf1);
	SDL_FreeSurface(surf2);
	SDL_FreeSurface(surf3);
}

MenuScene::~MenuScene() {
	// TODO Auto-generated destructor stub
}

