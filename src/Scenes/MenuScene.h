/*
 * InitScene.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include <SDL2/SDL_ttf.h>

#include "../SceneInterface.h"
#include "../MainConfiguration.h"

#define TEXT_FULL_SCREEN "Press 'f' to toggle full screen"
#define TEXT_ENTER "Press 'Enter' for to start"
#define TEXT_ESCAPE "Press 'Escape' for to exit"

class MenuScene : public SceneInterface {
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

	TTF_Font* Sans;
	SDL_Texture* wall;
	SDL_Texture* mFull;
	SDL_Texture* mEnter;
	SDL_Texture* mExit;

	SDL_Surface* surf1;
	SDL_Surface* surf2;
	SDL_Surface* surf3;

	bool fullscreen;

public:
	MenuScene(SDL_Renderer *ren, SDL_Window * window);
	virtual ~MenuScene();

	void init();
	int write();
	void close();
};

#endif /* MENUSCENE_H_ */
