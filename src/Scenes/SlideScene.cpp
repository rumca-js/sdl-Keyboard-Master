/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include "SlideScene.h"

#include <iostream>

#include "../Audio/MusicManager.h"

static volatile int seconds_counter = 0;

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

SlideScene::SlideScene(SDL_Renderer *ren, SDL_Window * window,  std::map<std::string, std::string> sceneInfo) {

    win = window;
    renderer = ren;

    Sans = NULL;

    this->sceneInfo = sceneInfo;

    my_timer_id = -1;

    config = &MainConfiguration::getConfig();

    time_fade_in = std::stoi(sceneInfo["fade-in"]);
    time_fade_out = std::stoi(sceneInfo["fade-out"]);
    time_display = std::stoi(sceneInfo["time"]);
}

SlideScene::~SlideScene() {
    // TODO Auto-generated destructor stub
}

void SlideScene::init() {

    logo.open(sceneInfo["background"], renderer);

    Sans = config->getDefaultFont();

    Uint8 r = std::stoi(sceneInfo["letter-r"]);
    Uint8 g = std::stoi(sceneInfo["letter-g"]);
    Uint8 b = std::stoi(sceneInfo["letter-b"]);

    SDL_Color color = {r, g, b, 255};

    text1.open(sceneInfo["slide-text1"], renderer, Sans, color);
    text2.open(sceneInfo["slide-text2"], renderer, Sans, color);
    text3.open(sceneInfo["slide-text3"], renderer, Sans, color);
}

void SlideScene::close() {
    if (Sans)
    {
        TTF_CloseFont(Sans);
        Sans = NULL;
    }

    text1.close();
    text2.close();
    text3.close();
}

void SlideScene::onEnter() {
    seconds_counter = 0;

    my_timer_id = SDL_AddTimer(1000, my_callbackfunc1, 0);

    display = false;

    MakeSureMyMusicIsPlaying();
}

void SlideScene::onLeave() {
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
            
            // do not use else if, since fade in and fade out can be 0s
            if (seconds == time_fade_in) {
                display = true;
            }
            if (seconds == time_fade_in + time_display) {
                display = false;
            }
            if (seconds == time_fade_in + time_display + time_fade_out) {
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
        texr.y = margin/3.0;
        texr.w = (int)(logo.getWidth() *ratio-margin*2.0);
        texr.h = (int)(logo.getHeight()*ratio-margin*2.0);

        logo.draw(NULL, &texr);

        texr.y = config->getWinHeight()-margin;
        texr.h = margin/4;
        texr.w = text1.getText().size() * margin/7.0;
        text1.draw(NULL, &texr);

        texr.y = config->getWinHeight()-margin+(margin/4);
        texr.h = margin/4;
        texr.w = text2.getText().size() * margin/7.0;
        text2.draw(NULL, &texr);

        texr.y = config->getWinHeight()-margin+(2*margin/4);
        texr.h = margin/4;
        texr.w = text3.getText().size() * margin/7.0;
        text3.draw(NULL, &texr);
    }

    return status;
}

std::string SlideScene::getName() {
    return sceneInfo["name"];
}

std::string SlideScene::getEngineName() {
    return "SLIDE";
}
