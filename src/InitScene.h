/*
 * InitScene.h
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#ifndef INITSCENE_H_
#define INITSCENE_H_

#include <SDL2/SDL_ttf.h>

#include "SceneInterface.h"


class InitScene : public SceneInterface {
	SDL_Renderer* renderer;
	SDL_Texture* wall;
	TTF_Font* Sans;
	SDL_Texture* mFull;
	SDL_Texture* mEnter;
	SDL_Texture* mExit;
	bool fullscreen;
	SDL_Window* win;

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
