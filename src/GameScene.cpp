/*
 * GameScene.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include "config.h"

#include "GameScene.h"
#include "stdio.h"



Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}



GameScene::GameScene() {
	// TODO Auto-generated constructor stub
}

void GameScene::init(SDL_Window * win)
{
	window = win;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //SDL_QueryTexture(img, NULL, NULL, &w, &h); to know how big the picture is

    wall = IMG_LoadTexture(renderer, "sky.jpg");

    if (TTF_Init() != 0)
    {
    	printf("Could not initialize TTF");
    }

    Sans = TTF_OpenFont(FONT_NAME, 24);

    letters.push_back(Letter(renderer, Sans, 'A'));

    uint32_t param;
    my_timer_id = SDL_AddTimer(TIMER_DELAY, my_callbackfunc, &param);
}

bool GameScene::move_letters()
{
	for(unsigned int i=0; i<letters.size();i++)
	{
		letters[i].move();

		if (letters[i].getY() > HEIGHT-LETTER_HEIGHT)
			return true;
	}

	return false;
}

void GameScene::display_letters()
{
	for(unsigned int i=0; i<letters.size();i++)
	{
		letters[i].display();
	}
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
			else if (e.type == SDL_KEYDOWN)
			{
				if ((char)e.key.keysym.sym == SDLK_a)
				{
					letters.pop_back();

					letters.push_back(Letter(renderer, Sans, 'B'));
				}
			}
			else if (e.type == SDL_USEREVENT)
			{
				if (this->move_letters() )
				{
					break;
				}
			}
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, wall, NULL, &texr);

		this->display_letters();

		SDL_RenderPresent(renderer);
	}
}

void GameScene::close()
{
	TTF_CloseFont(Sans);
	SDL_RemoveTimer( my_timer_id );
	SDL_DestroyTexture(wall);
	SDL_DestroyRenderer(renderer);
}

GameScene::~GameScene() {
	// TODO Auto-generated destructor stub
}

