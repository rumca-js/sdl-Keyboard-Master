/*
 * GameScene.h
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#ifndef COSMOSSCENE_H_
#define COSMOSSCENE_H_


#include <vector>
#include <string>
#include <SDL2/SDL_mixer.h>

#include "../Letter.h"

#include "../SceneInterface.h"
#include "../MainConfiguration.h"



class CosmosScene : public SceneInterface {
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
    SDL_Texture *wall = NULL;
    /*!
     * \brief The high score counter texture.
     */
    SDL_Texture * counter_text = NULL;
    /*!
     * \brief Counter surface.
     */
    SDL_Surface* counter_surface;
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
    std::vector<Letter*> letters;
    /*!
     * \brief defines how fast the letter counter is updated.
     */
    unsigned int timer_delay;
    /*!
     * \brief defines how the consecutive letter speed up.
     */
    unsigned int speed_factor;
    /*!
     * \brief Piano notes A-G.
     */
	Mix_Chunk* notes[7];
	/*!
	 * \brief Sound for the end of the game.
	 */
	Mix_Chunk* note_eog;
    /*!
     * \brief Resets to a default state.
     */
	void reset();
	/*!
	 * \brief Updates high score counter.
	 */
	void updateCounter();
public:
	/*!
	 * \brief Constructor.
	 */
	CosmosScene(SDL_Renderer *ren, SDL_Window * window);
	/*!
	 * \brief Destructor.
	 */
	virtual ~CosmosScene();
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
	void new_letter();
	/**
	 * @brief Closes the scene, disposes elements.
	 */
	void close();
};

#endif /* COSMOSSCENE_H_ */
