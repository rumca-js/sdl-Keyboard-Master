/*
 * InitScene.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef INITSCENE_H_
#define INITSCENE_H_

#include <map>
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "../Images/DrawTexture.h"
#include "SceneInterface.h"
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
	/*!
	 * \brief logo texture.
	 */
	DrawTexture logo;
	/*!
	 * Timer for displaying logo.
	 */
	SDL_TimerID my_timer_id;
    bool display;
public:
	/*!
	 * \brief Constructor.
	 */
	IntroScene(SDL_Renderer *ren, SDL_Window * window, std::map<std::string, std::string> sceneInfo);
	/*!
	 * \brief Destructor.
	 */
	virtual ~IntroScene();
	/*!
	 * \brief Scene init function.
	 */
	void init();
	/*!
	 * \brief Scene write function.
	 */
	int write();
	/*!
	 * \brief Scene close function.
	 */
	void close();
	std::string getName();
	static std::string getEngineName();
    int handleEvents();
    void onEnter();
    void onLeave();
};

#endif /* INITSCENE_H_ */
