/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include <iostream>
#include "IntroScene.h"


static int seconds_counter = 0;

static Uint32 my_callbackfunc1(Uint32 interval, void *param) {

    seconds_counter ++;

    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = seconds_counter;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

IntroScene::IntroScene(SDL_Renderer *ren, SDL_Window * window,  std::map<std::string, std::string> sceneInfo) {

    win = window;
    renderer = ren;

    this->sceneInfo = sceneInfo;

    std::cout << "Scene information" << sceneInfo["background"] << std::endl;

    my_timer_id = -1;

    config = &MainConfiguration::getConfig();
}

IntroScene::~IntroScene() {
    // TODO Auto-generated destructor stub
}

void IntroScene::init() {
	seconds_counter = 0;
    logo.open(sceneInfo["background"], renderer);
    my_timer_id = SDL_AddTimer(1000, my_callbackfunc1, 0);
    display = false;
}

void IntroScene::close() {
    SDL_RemoveTimer(my_timer_id);
}

int IntroScene::handleEvents() {
    int status = -1;
    SDL_Event e;
    if ( SDL_PollEvent(&e) ) {
        if (e.type == SDL_QUIT) {
            status = 1;
        }
        else if (e.type == SDL_USEREVENT) {
            if (e.user.code == 2) {
                display = true;
            }
            else if (e.user.code == 7) {
                status = 0;
            }
        }
    }

    return status;
}

int IntroScene::write() {
    int status = 0;

    status = handleEvents();
    if (status != -1)
    {
        return status;
    }

    /* We display after some considerable amount of time */
    if (display) {

        float ratio = config->getWinHeight()/(float)logo.getHeight();
        float margin = config->getWinWidth()/10;

        SDL_Rect texr;
        texr.x = margin;
        texr.y = margin; 
        texr.w = (int)(logo.getWidth() *ratio-margin*2.0);
        texr.h = (int)(logo.getHeight()*ratio-margin*2.0);

        logo.draw(NULL, &texr);
    }

    return status;
}

std::string IntroScene::getName() {
    return sceneInfo["name"];
}

std::string IntroScene::getEngineName() {
    return "INTRO";
}
