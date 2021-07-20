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
	virtual void init() override;
	/*!
	 * \brief Scene write function.
	 */
	virtual int write() override;
	/*!
	 * \brief Scene close function.
	 */
	virtual void close() override;
	virtual std::string getName() override;
    virtual int handleEvents() override;
    virtual void onEnter() override;
    virtual void onLeave() override;
	static std::string getEngineName();
};

#endif /* INITSCENE_H_ */
