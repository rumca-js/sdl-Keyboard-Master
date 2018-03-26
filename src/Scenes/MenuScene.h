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
	/*!
	 * \brief Font that is used.
	 */
	TTF_Font* Sans;
	/*!
	 * \brief The background picture.
	 */
	SDL_Texture* wall;
	/*!
	 * \brief The full screen text texture.
	 */
	SDL_Texture* mFull;
	/*!
	 * \brief The start game text texture.
	 */
	SDL_Texture* mEnter;
	/*!
	 * \brief The exit text texture.
	 */
	SDL_Texture* mExit;
	/*!
	 * \brief full screen text surface.
	 */
	SDL_Surface* surf1;
	/*!
	 * \brief The start game text surface.
	 */
	SDL_Surface* surf2;
	/*!
	 * \brief The exit text surface.
	 */
	SDL_Surface* surf3;
	/*!
	 * \brief Full screen indication.
	 */
	bool fullscreen;

public:
	MenuScene(SDL_Renderer *ren, SDL_Window * window);
	virtual ~MenuScene();

	void init();
	int write();
	void close();
};

#endif /* MENUSCENE_H_ */
