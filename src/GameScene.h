/*
 * GameScene.h
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_


#include <vector>
#include "Letter.h"

#include "SceneInterface.h"

class GameScene : public SceneInterface {
    SDL_Renderer *renderer = NULL;
    TTF_Font* Sans = NULL;

    SDL_Texture *wall = NULL;
    unsigned int timer_delay;

    int w, h;
    //SDL_Window * window;
    std::vector<Letter> letters;
    SDL_TimerID my_timer_id;

public:
	GameScene();
	/**
	 * @brief Performs initialization
	 */
	void init(SDL_Renderer *ren, SDL_Window * window);
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
	void check_if_killed(char key);
	/**
	 * @brief Closes the scene, disposes elements.
	 */
	void close();
	virtual ~GameScene();
};

#endif /* GAMESCENE_H_ */
