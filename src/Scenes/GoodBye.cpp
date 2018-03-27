/*
 * GoodBye.cpp
 *
 *  Created on: 26 mar 2018
 *      Author: hunter
 */

#include "../config.h"

#include "GoodBye.h"


Uint32 my_callbackfunc2(Uint32 interval, void *param) {
	static int counter = 0;

	counter ++;

    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = counter;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}


GoodBye::GoodBye(SDL_Renderer *ren, SDL_Window * window) {
	win      = window;
	renderer = ren;

	wall = NULL;

	my_timer_id = -1;

	config = &MainConfiguration::getConfig();
}

GoodBye::~GoodBye() {
	// TODO Auto-generated destructor stub
}

void GoodBye::init() {
	wall = IMG_LoadTexture(renderer, IMAGE_EXIT);
}

void GoodBye::close() {

}

int GoodBye::write() {
	int status = SCENE_EXIT;

    my_timer_id = SDL_AddTimer(1000, my_callbackfunc2, 0);

	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
			{
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
			else if (e.type == SDL_USEREVENT)
			{
				if (e.user.code == 4)
				{
					status = SceneInterface::SCENE_FINISHED;
					break;
				}
			}
		}

		SDL_RenderClear(renderer);

		SDL_Rect texr = config->getFullScreenSize();
		SDL_RenderCopy(renderer, wall, NULL, &texr );

		SDL_RenderPresent(renderer);
	}

	SDL_RemoveTimer(my_timer_id);

	return status;
}

