/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: hunter
 */

#include "MenuScene.h"

#include "../config.h"


MenuScene::MenuScene(SDL_Renderer *ren, SDL_Window * window) {
	fullscreen = true;

	win = window;
	renderer = ren;

	wall 	= NULL;
	Sans 	= NULL;

	config = NULL;

	selected = 0;
}

MenuScene::~MenuScene() {
	// TODO Auto-generated destructor stub
}

void MenuScene::init() {

	config = &MainConfiguration::getConfig();

    Sans = TTF_OpenFont(FONT_NAME, FONT_SIZE);

    wall = IMG_LoadTexture(renderer, IMAGE_MENU);

    buttons.push_back( new Button(renderer, TEXT_ENTER));
    buttons.push_back( new Button(renderer, TEXT_FULL_SCREEN));
    buttons.push_back( new Button(renderer, TEXT_ESCAPE));

    SDL_Color color = {0, 0, 255};

    buttons[0]->setDimentions(0.32, 0.06);
    buttons[0]->setPosition(0.6, 0.1);
    buttons[0]->setFont(Sans, color);
    buttons[0]->setTextures(TEXTURE_BUTTON1, TEXTURE_BUTTON1_HOVER);
    buttons[0]->load();

    buttons[1]->setDimentions(0.32, 0.06);
	buttons[1]->setPosition(0.6, 0.2);
	buttons[1]->setFont(Sans, color);
	buttons[1]->setTextures(TEXTURE_BUTTON1, TEXTURE_BUTTON1_HOVER);
	buttons[1]->load();

	buttons[2]->setDimentions(0.32, 0.06);
	buttons[2]->setPosition(0.6, 0.3);
	buttons[2]->setFont(Sans, color);
	buttons[2]->setTextures(TEXTURE_BUTTON1, TEXTURE_BUTTON1_HOVER);
	buttons[2]->load();

	buttons[0]->setHover(true);
}

void MenuScene::close() {
	SDL_DestroyTexture(wall);
	TTF_CloseFont(Sans);

	for(unsigned int i=0; i<buttons.size(); i++) {
		delete buttons[i];
	}
}

int MenuScene::write() {
	int status = SCENE_EXIT;

	while (1) {

		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT) {
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
				status = SCENE_EXIT;
				break;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN) {
				if (selected == 0) {
					status = SCENE_FINISHED;
					break;
				}
				else if (selected == 1) {
					setFullScreen();
				}
				if (selected == 2) {
					status = SCENE_EXIT;
					break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_UP) {
				selected_decrement();
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_DOWN) {
				selected_increment();
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_f) {
				setFullScreen();
			}
		}

		SDL_RenderClear(renderer);

		SDL_Rect texr = config->getFullScreenSize();
		SDL_RenderCopy(renderer, wall, NULL, &texr);

		for(unsigned int i=0; i<buttons.size(); i++)  {
			buttons[i]->draw();
		}

		SDL_RenderPresent(renderer);
	}

	return status;
}

void MenuScene::setFullScreen() {

	fullscreen = !fullscreen;

	if (fullscreen) {
		SDL_DisplayMode DM, windowMode;
		SDL_GetCurrentDisplayMode(0, &DM);

		SDL_GetWindowDisplayMode(win, &windowMode);

		windowMode.h = DM.h;
		windowMode.w = DM.w;

		config->setWindowSize(DM.w, DM.h);

		SDL_SetWindowDisplayMode(win, &windowMode);

		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
	}
	else {
		// TODO do not use WIDTH or HEIGHT definitions directly
		config->setWindowSize(WIDTH, HEIGHT);

		SDL_SetWindowFullscreen(win, 0);
	}
}

void MenuScene::selected_increment()
{
	if (selected != 2) {
		printf("selected");
		buttons[selected]->setHover(false);
		printf("selected");
		selected++;
		buttons[selected]->setHover(true);
		printf("selected");
	}
}

void MenuScene::selected_decrement()
{
	if (selected != 0) {
		printf("selected");
		buttons[selected]->setHover(false);
		printf("selected");
		selected--;
		buttons[selected]->setHover(true);
		printf("selected");
	}
}
