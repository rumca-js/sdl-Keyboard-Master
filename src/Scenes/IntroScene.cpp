/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include "IntroScene.h"


Uint32 my_callbackfunc1(Uint32 interval, void *param) {
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

IntroScene::IntroScene(SDL_Renderer *ren, SDL_Window * window) {

	win = window;
	renderer = ren;

	my_timer_id = -1;

	config = &MainConfiguration::getConfig();
}

IntroScene::~IntroScene() {
	// TODO Auto-generated destructor stub
}

void IntroScene::init() {
    logo.open(config->getConfigString("IMAGE_INTRO"), renderer);
}

void IntroScene::close() {
}

int IntroScene::write() {
	int status = SCENE_EXIT;

    my_timer_id = SDL_AddTimer(1000, my_callbackfunc1, 0);
    bool display = false;

	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT) {
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_USEREVENT) {
				if (e.user.code == 2) {
					display = true;
				}
				else if (e.user.code == 7) {
					status = SceneInterface::SCENE_FINISHED;
					break;
				}
			}
		}

		SDL_RenderClear(renderer);

		/* We display after some considerable amount of time */
		if (display) {

			float ratio = config->getHeight()/(float)logo.getHeight();
			float margin = config->getWidth()/10;

			SDL_Rect texr;
			texr.x = margin;
			texr.y = margin; 
			texr.w = (int)(logo.getWidth() *ratio-margin*2.0);
			texr.h = (int)(logo.getHeight()*ratio-margin*2.0);

			logo.draw(NULL, &texr);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_RemoveTimer(my_timer_id);

	return status;
}


