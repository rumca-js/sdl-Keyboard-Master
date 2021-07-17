/*
 * GameScene.h
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_


#include <vector>
#include <string>
#include <map>

#include <SDL2/SDL_mixer.h>

#include "../Images/DrawBuilder.h"
#include "../Letter.h"
#include "../Audio/SdlAudio.h"
#include "SceneInterface.h"
#include "../MainConfiguration.h"


class GameScene : public SceneInterface {
    /*!
     * \brief SDL Renderer pointer.
     */
    SDL_Renderer *renderer = NULL;
    /*!
     * \brief Configuration instance pointer.
     */
    MainConfiguration * config;
    /*!
     * \brief Font for game.
     */
    TTF_Font* Sans = NULL;
    /*!
     * \brief The background texture.
     */
    DrawItem * wall;
    /*!
     * \brief The high score counter texture.
     */
    DrawItem * counter_text = NULL;
    /*!
     * \brief Counter text (digits).
     */
    std::string counter_string;
    /*!
     * \brief The letter fall timer.
     */
    SDL_TimerID my_timer_id;
    /*!
     * The letters placeholder.
     */
    std::vector<Letter*> letters_active;
    std::vector<Letter*> letters_inactive;
    /*!
     * \brief defines how fast the letter counter is updated.
     */
    unsigned int timer_delay;
    /*!
     * \brief defines how the consecutive letter speed up.
     */
    double speed_factor;
    /*!
     * \brief Piano notes A-G.
     */
    SdlAudio notes[7];
    /*!
     * \brief Sound for the end of the game.
     */
    SdlAudio note_eog;
    /*!
     * \brief Resets to a default state.
     */
    void reset();
    /*!
     * \brief Updates high score counter.
     */
    void updateCounter();
    /*!
     * state name
     * */
    std::map<std::string, std::string> sceneInfo;
    /*!
     * Sets up music for scene
     */
    void MakeSureMyMusicIsPlaying();

public:
    /*!
     * \brief Constructor.
     */
    GameScene(SDL_Renderer *ren, SDL_Window * window, std::map<std::string, std::string> sceneInfo);
    /*!
     * \brief Destructor.
     */
    virtual ~GameScene();
    /**
     * @brief Performs initialization
     */
    void init();
    /**
     * @brief Writes scene on the window
     */
    int write();
    /**
     * @brief Updates letter positions. Every timer event.
     */
    bool move_letters();
    /**
     * @brief Displays the letters on the renderer
     */
    void display_letters();
    /**
     * @brief Checks if letter should be destroyed.
     */
    bool check_if_killed(char key);
    /*!
     * \brief Disposes previous letter and creates new letter.
     */
    void kill_letter(Letter * letter);
    void create_new_letter();
    /**
     * @brief Closes the scene, disposes elements.
     */
    void close();
    std::string getName();
    static std::string getEngineName();
    int handleEvents();
    void check_if_remove_letters();
};

#endif /* GAMESCENE_H_ */
