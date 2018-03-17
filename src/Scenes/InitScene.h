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

#define TEXT_FULL_SCREEN "Press 'f' to toggle full screen"
#define TEXT_ENTER "Press 'Enter' for to start"
#define TEXT_ESCAPE "Press 'Escape' for to exit"

class InitScene : public SceneInterface {
	SDL_Renderer* renderer;
	SDL_Texture* wall;
	TTF_Font* Sans;
	SDL_Texture* mFull;
	SDL_Texture* mEnter;
	SDL_Texture* mExit;
	bool fullscreen;
	SDL_Window* win;

	MainConfiguration * config;

public:
	InitScene();

	static const int SCENE_EXIT=0;
	static const int SCENE_NEXT=1;

	void init(SDL_Renderer *ren, SDL_Window * window);
	int write();
	void close();

	virtual ~InitScene();
};

#endif /* INITSCENE_H_ */
