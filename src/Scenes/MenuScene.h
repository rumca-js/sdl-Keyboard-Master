/*
 * InitScene.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include <SDL2/SDL_ttf.h>
#include <vector>

#include "../SceneInterface.h"
#include "../MainConfiguration.h"

#include "../GUI/Button.h"

// Text Defines
#define TEXT_ENTER "Start"
#define TEXT_FULL_SCREEN "Full Screen"
#define TEXT_ESCAPE "EXIT"


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
	 * \brief Full screen indication.
	 */
	bool fullscreen;
	/*!
	 * \brief Buttons list.
	 */
	std::vector<Button *> buttons;
	/*!
	 * \brief
	 */
	unsigned int selected;
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
	MenuScene(SDL_Renderer *ren, SDL_Window * window);
	virtual ~MenuScene();

	void init();
	int write();
	void close();
};

#endif /* MENUSCENE_H_ */
