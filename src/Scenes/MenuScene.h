/*
 * InitScene.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include <map>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "../Images/DrawTexture.h"
#include "SceneCommons.h"
#include "../MainConfiguration.h"

#include "../GUI/SdlButton.h"

// Text Defines
#define TEXT_ENTER "Start"
#define TEXT_FULL_SCREEN "Full Screen"
#define TEXT_STORY "Story"
#define TEXT_ESCAPE "EXIT"


class MenuScene : public SceneCommons {
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
     * \brief Font that is used.
     */
    TTF_Font* Sans;
    /*!
     * \brief The background picture.
     */
    DrawTexture wall;
    /*!
     * \brief Full screen indication.
     */
    bool fullscreen;
    /*!
     * \brief Buttons list.
     */
    std::vector<SdlButton *> buttons;
    /*!
     * \brief selected button, -1 if no button is selected
     */
    int selected_button;
    /*!
     * \brief increments selected button id;
     */
    void selected_increment();
    /*!
     * \brief decrements selected button id.
     */
    void selected_decrement();
    /*!
     * \brief Toggles full screen.
     */
    void setFullScreen();
public:
    MenuScene(SDL_Renderer *ren, SDL_Window * window, std::map<std::string, std::string> sceneInfo);
    virtual ~MenuScene();

    virtual void init() override;
    virtual int write() override;
    virtual void close() override;
    virtual std::string getName() override;
    virtual int handleEvents() override;
    virtual void onEnter() override;
    virtual void onLeave() override;
    static std::string getEngineName();
    void selectNewButton(unsigned int oldButtonId, unsigned int newButtonId);
    void deselectAll();
};

#endif /* MENUSCENE_H_ */
