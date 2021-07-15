/*
 * GoodBye.cpp
 *
 *  Created on: 26 mar 2018
 *      Author: hunter
 */

#include "GoodBye.h"


static Uint32 my_callbackfunc2(Uint32 interval, void *param) {
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

GoodBye::GoodBye(SDL_Renderer *ren, SDL_Window * window,  std::map<std::string, std::string> sceneInfo) {
	win      = window;
	renderer = ren;

    this->sceneInfo = sceneInfo;

	my_timer_id = -1;

	config = &MainConfiguration::getConfig();
}

GoodBye::~GoodBye() {
	// TODO Auto-generated destructor stub
}

void GoodBye::init() {
	wall.open(sceneInfo["background"], renderer);

    my_timer_id = SDL_AddTimer(1000, my_callbackfunc2, 0);
}

void GoodBye::close() {
	SDL_RemoveTimer(my_timer_id);
}

int GoodBye::handleEvents() {
    int status = -1;

    SDL_Event e;
    if ( SDL_PollEvent(&e) ) {
        if (e.type == SDL_QUIT)
        {
            status = 1;
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
		{
            status = 1;
		}
        else if (e.type == SDL_USEREVENT)
        {
            if (e.user.code == 4)
            {
                status = 0;
            }
        }
    }
    return status;
}

int GoodBye::write() {
	int status = 0;

    status = handleEvents();
	if (status != -1)
		return status;

    SDL_Rect texr = config->getFullScreenSize();
    wall.draw(NULL, &texr);

	return status;
}

std::string GoodBye::getName() {
	return sceneInfo["name"];
}

std::string GoodBye::getEngineName() {
	return "GOODBYE";
}
