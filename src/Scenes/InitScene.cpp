/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include "../config.h"


#include "InitScene.h"

InitScene::InitScene() {
	// TODO Auto-generated constructor stub
}

void InitScene::init(SDL_Renderer *ren, SDL_Window * window)
{
	win = window;
	renderer = ren;
	fullscreen = false;

	config = &MainConfiguration::getConfig();

    Sans = TTF_OpenFont(FONT_NAME, 24);

    wall = IMG_LoadTexture(renderer, SKY_WALLPAPER);

	SDL_Color White = {0, 0, 255};

	SDL_Surface* surf1 = TTF_RenderText_Solid(Sans, TEXT_FULL_SCREEN , White);
	mFull = SDL_CreateTextureFromSurface(renderer, surf1);

	SDL_Surface* surf2 = TTF_RenderText_Solid(Sans, TEXT_ENTER , White);
	mEnter = SDL_CreateTextureFromSurface(renderer, surf2);

	SDL_Surface* surf3 = TTF_RenderText_Solid(Sans, TEXT_ESCAPE , White);
	mExit = SDL_CreateTextureFromSurface(renderer, surf3);
}
int InitScene::write()
{
	int status = 0;


	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
			{
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			{
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN)
			{
				status = SCENE_NEXT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_f)
			{
				fullscreen = !fullscreen;
				if (fullscreen)
				{
					SDL_DisplayMode DM, windowMode;
					SDL_GetCurrentDisplayMode(0, &DM);

					SDL_GetWindowDisplayMode(win, &windowMode);

					windowMode.h = DM.h;
					windowMode.w = DM.w;

					config->setWindowSize(DM.w, DM.h);

					SDL_SetWindowDisplayMode(win, &windowMode);


					SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
				}
				else
				{
					// TODO do not use WIDTH or HEIGHT definitions directly
					config->setWindowSize(WIDTH, HEIGHT);

					SDL_SetWindowFullscreen(win, 0);
				}
			}
		}

		SDL_RenderClear(renderer);

		unsigned int letter_width = config->getWidth()/50;
		unsigned int letter_height = config->getHeight()/10;

		SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = config->getWidth(); texr.h = config->getHeight();

		SDL_Rect rFull; rFull.x = config->getWidth()/3; rFull.y = config->getHeight()*1/4; rFull.w = letter_width * strlen(TEXT_FULL_SCREEN); rFull.h = letter_height;
		SDL_Rect rEnter; rEnter.x = config->getWidth()/3; rEnter.y = config->getHeight()*2/4; rEnter.w = letter_width * strlen(TEXT_ENTER); rEnter.h = letter_height;
		SDL_Rect rExit; rExit.x = config->getWidth()/3; rExit.y = config->getHeight()*3/4; rExit.w = letter_width * strlen(TEXT_ESCAPE); rExit.h = letter_height;

		SDL_RenderCopy(renderer, wall, NULL, &texr);

		SDL_RenderCopy(renderer, mFull, NULL, &rFull);
		SDL_RenderCopy(renderer, mEnter, NULL, &rEnter);
		SDL_RenderCopy(renderer, mExit, NULL, &rExit);

		SDL_RenderPresent(renderer);
	}

	return status;
}
void InitScene::close()
{
	SDL_DestroyTexture(wall);
	TTF_CloseFont(Sans);
}

InitScene::~InitScene() {
	// TODO Auto-generated destructor stub
}

