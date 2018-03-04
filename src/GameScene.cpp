/*
 * GameScene.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include "GameScene.h"

#include "config.h"

#define IMG_PATH "sdl.png"


GameScene::GameScene() {
	// TODO Auto-generated constructor stub
}

void GameScene::init(SDL_Window * win)
{
	window = win;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    img = IMG_LoadTexture(renderer, IMG_PATH);
    SDL_QueryTexture(img, NULL, NULL, &w, &h);

}

void GameScene::write()
{
	SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = WIDTH; texr.h = HEIGHT;

	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, img, NULL, &texr);
		SDL_RenderPresent(renderer);
	}
}

void GameScene::close()
{
	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
}

GameScene::~GameScene() {
	// TODO Auto-generated destructor stub
}

