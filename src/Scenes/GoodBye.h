/*
 * GoodBye.h
 *
 *  Created on: 26 mar 2018
 *      Author: hunter
 */

#ifndef SCENES_GOODBYE_H_
#define SCENES_GOODBYE_H_

#include <map>

#include "../Images/DrawTexture.h"
#include "SceneCommons.h"
#include "../Main/MainConfiguration.h"

class GoodBye : public SceneCommons {
    /*!
     * \brief SDL Renderer pointer.
     */
    SDL_Renderer* renderer;
    /*!
     * \brief SDL window pointer.
     */
    SDL_Window* win;
    /*!
     * \brief Configuration instance pointer.
     */
    MainConfiguration * config;
    /*!
     * Timer for leaving game.
     */
    SDL_TimerID my_timer_id;
    /*!
     * \brief The background picture.
     */
    DrawTexture wall;
public:
    GoodBye(SDL_Renderer *ren, SDL_Window * window, std::map<std::string, std::string> sceneInfo);
    virtual ~GoodBye();

    virtual void init() override;
    virtual int write() override;
    virtual void close() override;
    virtual std::string getName() override;
    virtual int handleEvents() override;
    virtual void onEnter() override;
    virtual void onLeave() override;
    static std::string getEngineName();
};

#endif /* SCENES_GOODBYE_H_ */
