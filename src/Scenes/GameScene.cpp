/*
 * GameScene.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include "../config.h"

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

unsigned rand_min_max(unsigned min, unsigned max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}


GameScene::GameScene() {
	timer_delay = 50;
	speed_factor = 1;
}

void GameScene::init(SDL_Renderer *ren, SDL_Window * window)
{
	config = &MainConfiguration::getConfig();
	renderer = ren;

    wall = IMG_LoadTexture(renderer, SKY_WALLPAPER);

    Sans = TTF_OpenFont(FONT_NAME, 24);

    letters.push_back(Letter(renderer, Sans, 'a'));
    letters[0].setX( rand_min_max(0, WIDTH-LETTER_WIDTH));

    uint32_t param;
    my_timer_id = SDL_AddTimer(timer_delay, my_callbackfunc, &param);
}

bool GameScene::move_letters()
{
	for(unsigned int i=0; i<letters.size();i++)
	{
		letters[i].setY(letters[i].getY() + speed_factor);


		/*letters[i].move(speed_factor);*/

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

bool GameScene::check_if_killed(char key)
{
	bool killed = false;

	for(unsigned int i=0; i<letters.size(); i++)
	{
		if (letters[i].is(key))
		{
			letters.pop_back();

			char letter = rand_min_max(97, 122);

			letters.push_back(Letter(renderer, Sans, letter));
			letters[0].setX( rand_min_max(0, WIDTH-LETTER_WIDTH));

			killed = true;
		}
	}

	return killed;
}

int GameScene::write()
{
	SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = config->getWidth(); texr.h = config->getHeight();


	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
			else if (e.type == SDL_KEYDOWN)
			{
				if (check_if_killed((char)e.key.keysym.sym) )
				{
					speed_factor++;
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

	return 0;
}

void GameScene::close()
{
	TTF_CloseFont(Sans);
	SDL_RemoveTimer( my_timer_id );
	SDL_DestroyTexture(wall);
}

GameScene::~GameScene() {
	// TODO Auto-generated destructor stub
}

