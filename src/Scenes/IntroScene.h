/*
 * InitScene.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef INITSCENE_H_
#define INITSCENE_H_

#include <SDL2/SDL_ttf.h>

#include "../SceneInterface.h"
#include "../MainConfiguration.h"

#define TEXT_LOGO "SLAVE STUDIO 1"

class IntroScene : public SceneInterface {
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
	SDL_Texture* logo;
	SDL_TimerID my_timer_id;

public:
	IntroScene();

	void init(SDL_Renderer *ren, SDL_Window * window);
	int write();
	void close();

	virtual ~IntroScene();
};

#endif /* INITSCENE_H_ */
