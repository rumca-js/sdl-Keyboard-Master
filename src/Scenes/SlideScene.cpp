/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include "SlideScene.h"

#include <iostream>

#include "../Audio/MusicManager.h"


static Uint32 my_callbackfunc1(Uint32 interval, void *param) {
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

SlideScene::SlideScene(SDL_Renderer *ren, SDL_Window * window,  std::map<std::string, std::string> sceneInfo) {

    win = window;
    renderer = ren;

    this->sceneInfo = sceneInfo;

    std::cout << "Scene information" << sceneInfo["background"] << std::endl;

    my_timer_id = -1;

    config = &MainConfiguration::getConfig();

    time_fade_in = std::stoi(sceneInfo["fade-in"]);
    time_fade_out = std::stoi(sceneInfo["fade-out"]);
    time_display = std::stoi(sceneInfo["time"]);
}

SlideScene::~SlideScene() {
    // TODO Auto-generated destructor stub
}

void SlideScene::MakeSureMyMusicIsPlaying() {
	MusicManager & man = MusicManager::getObject();
    std::string myMusic = sceneInfo["music"];

    if (!man.isPlaying())
    {
        man.addMusic(myMusic);
        man.play();
    }
    else
    {
        if (!man.isMyMusicPlaying(myMusic, true)) {
            man.resetQueue();
            man.stop();

            man.addMusic( myMusic );
            man.play();
        }
    }
}

void SlideScene::init() {

    logo.open(sceneInfo["background"], renderer);

    my_timer_id = SDL_AddTimer(1000, my_callbackfunc1, 0);

    display = false;

    MakeSureMyMusicIsPlaying();
}

void SlideScene::close() {
    SDL_RemoveTimer(my_timer_id);
}

int SlideScene::handleEvents() {
    int status = -1;
    SDL_Event e;
    if ( SDL_PollEvent(&e) ) {
        if (e.type == SDL_QUIT) {
            status = 1;
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
            status = 1;
        }
        else if (e.type == SDL_USEREVENT) {

            // code represents time in seconds
            unsigned int seconds = e.user.code;
            
            if (seconds == time_fade_in) {
                display = true;
            }
            else if (seconds == time_fade_in + time_display) {
                display = false;
            }
            else if (seconds == time_fade_in + time_display + time_fade_out) {
                status = 0;
            }
        }
    }

    return status;
}

int SlideScene::write() {
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

std::string SlideScene::getName() {
    return sceneInfo["name"];
}

std::string SlideScene::getEngineName() {
    return "SLIDE";
}
