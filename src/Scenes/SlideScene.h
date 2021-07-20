/*
 * InitScene.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef _H_SLIDESCENE_H_
#define _H_SLIDESCENE_H_

#include <map>
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "../Images/DrawTexture.h"
#include "../Images/DrawText.h"
#include "SceneCommons.h"
#include "../MainConfiguration.h"

#define TEXT_LOGO "SLAVE STUDIO 1"

class SlideScene : public SceneCommons {
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
     * \brief logo texture.
     */
    DrawTexture logo;
    DrawText text1;
    DrawText text2;
    DrawText text3;
    /*!
     * Timer for displaying logo.
     */
    SDL_TimerID my_timer_id;
    /*!
     * in seconds
     */
    unsigned int time_fade_in;
    /*!
     * in seconds
     */
    unsigned int time_fade_out;
    /*!
     * in seconds
     */
    unsigned int time_display;

    bool display;
    /*!
     * \brief Font that is used.
     */
    TTF_Font* Sans;

public:
    /*!
     * \brief Constructor.
     */
    SlideScene(SDL_Renderer *ren, SDL_Window * window, std::map<std::string, std::string> sceneInfo);
    /*!
     * \brief Destructor.
     */
    virtual ~SlideScene();
    /*!
     * \brief Scene init function.
     */
    virtual void init() override;
    /*!
     * \brief Scene write function.
     */
    virtual int write() override;
    /*!
     * \brief Scene close function.
     */
    virtual void close() override;
    /*!
     * Returns Name of Scene Engine
     */
    virtual std::string getName() override;
    /*!
     * handles SDL events
     */
    virtual int handleEvents() override;
    virtual void onEnter() override;
    virtual void onLeave() override;
    static std::string getEngineName();
};

#endif /* _H_SLIDESCENE_H_ */
