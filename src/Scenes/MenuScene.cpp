/*
 * InitScene.cpp
 *
 *  Created on: 11 mar 2018
 */

#include <iostream>
#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer *ren, SDL_Window * window,  std::map<std::string, std::string> sceneInfo) {
    fullscreen = true;

    win = window;
    renderer = ren;

    this->sceneInfo = sceneInfo;

    Sans     = NULL;

    config = NULL;

    selected_button = 0;
}

MenuScene::~MenuScene() {
    // TODO Auto-generated destructor stub
}

void MenuScene::init() {

    selected_button = 0;

    config = &MainConfiguration::getConfig();

    Sans = config->getDefaultFont();

    wall.open(sceneInfo["background"], renderer);

    buttons.push_back( new SdlButton(renderer, TEXT_ENTER));
    buttons.push_back( new SdlButton(renderer, TEXT_FULL_SCREEN));
    buttons.push_back( new SdlButton(renderer, TEXT_STORY));
    buttons.push_back( new SdlButton(renderer, TEXT_ESCAPE));

    SDL_Color color = {0, 0, 255, 255};

    buttons[0]->setDimentions(0.32, 0.06);
    buttons[0]->setPosition(0.6, 0.1);
    buttons[0]->setFont(Sans, color);
    buttons[0]->setTextures(config->getConfigString("TEXTURE_BUTTON1"), config->getConfigString("TEXTURE_BUTTON1_HOVER") );
    buttons[0]->load();

    buttons[1]->setDimentions(0.32, 0.06);
    buttons[1]->setPosition(0.6, 0.2);
    buttons[1]->setFont(Sans, color);
    buttons[1]->setTextures(config->getConfigString("TEXTURE_BUTTON1"), config->getConfigString("TEXTURE_BUTTON1_HOVER") );
    buttons[1]->load();

    buttons[2]->setDimentions(0.32, 0.06);
    buttons[2]->setPosition(0.6, 0.3);
    buttons[2]->setFont(Sans, color);
    buttons[2]->setTextures(config->getConfigString("TEXTURE_BUTTON1"), config->getConfigString("TEXTURE_BUTTON1_HOVER") );
    buttons[2]->load();

    buttons[3]->setDimentions(0.32, 0.06);
    buttons[3]->setPosition(0.6, 0.4);
    buttons[3]->setFont(Sans, color);
    buttons[3]->setTextures(config->getConfigString("TEXTURE_BUTTON1"), config->getConfigString("TEXTURE_BUTTON1_HOVER") );
    buttons[3]->load();

    //buttons[0]->setHover(true);
}

void MenuScene::close() {
    if (buttons.size() != 0)
    {
        for(unsigned int i=0; i<buttons.size(); i++) {
            delete buttons[i];
        }
        buttons.clear();

    }
    if (Sans)
    {
        TTF_CloseFont(Sans);
        Sans = NULL;
    }
}

void MenuScene::onEnter() {
	deselectAll();
    selectNewButton(0, 0);

    MakeSureMyMusicIsPlaying();
}

void MenuScene::onLeave() {
}

int MenuScene::handleEvents()
{
    int status = -1;
    SDL_Event e;
    if ( SDL_PollEvent(&e) ) {
        if (e.type == SDL_QUIT) {
            status = 1;
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
            status = 1;
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN) {
            if (selected_button == -1)
                return status;

            if (buttons[selected_button]->getText() == TEXT_ENTER) {
                status = 0;
            }
            else if (buttons[selected_button]->getText() == TEXT_STORY) {
                status = 2;
            }
            else if (buttons[selected_button]->getText() == TEXT_FULL_SCREEN) {
                setFullScreen();
            }
            else if (buttons[selected_button]->getText() == TEXT_ESCAPE) {
                status = 1;
            }
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_UP) {
            std::cout << "Keyup" << std::endl;
            selected_decrement();
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_DOWN) {
            std::cout << "Keydown" << std::endl;
            selected_increment();
        }
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_f) {
            setFullScreen();
        }
    }
    return status;
}

int MenuScene::write() {
    int status = 0;

    status = handleEvents();
    if (status != -1)
        return status;

    SDL_Rect texr = config->getFullScreenSize();
    wall.draw(NULL, &texr);

    for(unsigned int i=0; i<buttons.size(); i++)  {
        buttons[i]->draw();
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
        config->setWindowSize(config->getConfigInt("WIDTH"), config->getConfigInt("HEIGHT") );

        SDL_SetWindowFullscreen(win, 0);
    }
}

void MenuScene::selectNewButton(unsigned int oldButtonId, unsigned int newButtonId) {
    buttons[oldButtonId]->setHover(false);
    buttons[newButtonId]->setHover(true);

    selected_button = newButtonId;
}

void MenuScene::deselectAll()
{
	for(unsigned int i=0; i<buttons.size(); i++)
	{
		buttons[i]->setHover(false);
	}
}

void MenuScene::selected_increment() {

    unsigned int old_button = selected_button;
    unsigned int new_button = selected_button;

    if (selected_button <= (int)buttons.size()-2) {
        new_button = selected_button+1;
    }
    else
    {
        std::cout << "Could not increment" << std::endl;
    }

    if (old_button != new_button)
        selectNewButton(old_button, new_button);

}

void MenuScene::selected_decrement() {
    unsigned int old_button = selected_button;
    unsigned int new_button = selected_button;

    if (selected_button >= (int)1) {
        new_button = selected_button-1;
    }
    else
    {
        std::cout << "Could not decrement" << std::endl;
    }

    if (old_button != new_button)
        selectNewButton(old_button, new_button);
}

std::string MenuScene::getName() {
    return sceneInfo["name"];
}

std::string MenuScene::getEngineName() {
    return "MENU";
}
