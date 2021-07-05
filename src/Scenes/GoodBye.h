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
#include "../SceneInterface.h"
#include "../MainConfiguration.h"

class GoodBye : public SceneInterface {
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
    /*!
     * state name
     */
    std::map<std::string, std::string> sceneInfo;
public:
    GoodBye(SDL_Renderer *ren, SDL_Window * window, std::map<std::string, std::string> sceneInfo);
    virtual ~GoodBye();

    void init();
    int write();
    void close();
    std::string getName();
};

#endif /* SCENES_GOODBYE_H_ */
