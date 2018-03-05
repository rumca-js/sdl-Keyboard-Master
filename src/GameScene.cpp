/*
 * GameScene.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include "config.h"

#include "GameScene.h"
#include "stdio.h"


#define FONT_NAME  "/usr/share/fonts/truetype/freefont/FreeSans.ttf"

GameScene::GameScene() {
	// TODO Auto-generated constructor stub
}

void GameScene::init(SDL_Window * win)
{
	window = win;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //SDL_QueryTexture(img, NULL, NULL, &w, &h);

    wall = IMG_LoadTexture(renderer, "sky.jpg");

    if (TTF_Init() != 0)
    {
    	printf("Could not initialize TTF");
    }

    TTF_Font* Sans = TTF_OpenFont(FONT_NAME, 24);
    if (Sans != NULL)
    {
   	    SDL_Color White = {255, 0, 0};
  	    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Letter", White);
  	    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    }
    else
    {
    	printf("Could not open font");
    }
}

void GameScene::write()
{
	SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = WIDTH; texr.h = HEIGHT;

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, wall, NULL, &texr);
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

		SDL_RenderPresent(renderer);
	}
}

void GameScene::close()
{
	SDL_DestroyTexture(wall);
	SDL_DestroyRenderer(renderer);
}

GameScene::~GameScene() {
	// TODO Auto-generated destructor stub
}

