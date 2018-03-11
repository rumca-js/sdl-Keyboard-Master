/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include "config.h"


#include "InitScene.h"

InitScene::InitScene() {
	// TODO Auto-generated constructor stub
}

void InitScene::init(SDL_Renderer *ren, SDL_Window * window)
{
	win = window;
	renderer = ren;
	fullscreen = false;

    Sans = TTF_OpenFont(FONT_NAME, 24);

    wall = IMG_LoadTexture(renderer, "sky.jpg");

	SDL_Color White = {0, 0, 255};

	SDL_Surface* surf1 = TTF_RenderText_Solid(Sans, "Press 'f' to toggle full screen" , White);
	mFull = SDL_CreateTextureFromSurface(renderer, surf1);

	SDL_Surface* surf2 = TTF_RenderText_Solid(Sans, "Press 'Enter' for to start" , White);
	mEnter = SDL_CreateTextureFromSurface(renderer, surf2);

	SDL_Surface* surf3 = TTF_RenderText_Solid(Sans, "Press 'Escape' for to exit" , White);
	mExit = SDL_CreateTextureFromSurface(renderer, surf3);
}
int InitScene::write()
{
	SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = WIDTH; texr.h = HEIGHT;
	SDL_Rect rFull; rFull.x = 200; rFull.y = 230; rFull.w = 400; rFull.h = 50;
	SDL_Rect rEnter; rEnter.x = 200; rEnter.y = 300; rEnter.w = 300; rEnter.h = 50;
	SDL_Rect rExit; rExit.x = 200; rExit.y = 370; rExit.w = 300; rExit.h = 50;

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
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f)
			{
				fullscreen = !fullscreen;
				if (fullscreen)
				{
					SDL_DisplayMode DM, windowMode;
					SDL_GetCurrentDisplayMode(0, &DM);

					SDL_GetWindowDisplayMode(win, &windowMode);

					windowMode.h = DM.h;
					windowMode.w = DM.w;
					SDL_SetWindowDisplayMode(win, &windowMode);


					SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
				}
				else
				{
					SDL_SetWindowFullscreen(win, 0);
				}
			}
		}

		SDL_RenderClear(renderer);

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

