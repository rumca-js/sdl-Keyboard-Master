/*
 * GameScene.cpp
 *
 *  Created on: 4 mar 2018
 *      Author: hunter
 */

#include <iostream>

#include "../Utilities.h"
#include "GameScene.h"


Uint32 my_callbackfunc(Uint32 interval, void *param) {
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

GameScene::GameScene(SDL_Renderer *ren, SDL_Window * window,  std::map<std::string, std::string> sceneInfo) {
    renderer = ren;

    this->sceneInfo = sceneInfo;

    // Initializers
    counter_text  = NULL;
    config   = NULL;

	wall = NULL;

    //configuration
    my_timer_id  = -1;
    timer_delay  = 50;
    speed_factor = 1;
}

GameScene::~GameScene() {
    // TODO Auto-generated destructor stub
}

void GameScene::init() {
    config = &MainConfiguration::getConfig();

	wall = DrawBuilder::Build(sceneInfo["background"], renderer);
    wall->open( sceneInfo["background"], renderer);

    Sans = TTF_OpenFont(config->getConfigString("FONT_NAME").c_str(), config->getConfigInt("FONT_SIZE") );

    notes[0].open( config->getConfigString("SOUND_A") );
    notes[1].open( config->getConfigString("SOUND_B") );
    notes[2].open( config->getConfigString("SOUND_C") );
    notes[3].open( config->getConfigString("SOUND_D") );
    notes[4].open( config->getConfigString("SOUND_E") );
    notes[5].open( config->getConfigString("SOUND_F") );
    notes[6].open( config->getConfigString("SOUND_G") );

    note_eog.open( config->getConfigString("SOUND_END_OF_GAME") );

    reset();
}

void GameScene::close() {

	SDL_RemoveTimer( my_timer_id );

	if (wall != NULL)
	{
		delete wall;
		wall = NULL;
	}

	if (letters.size() != 0)
	{
		for(unsigned int i=0; i<letters.size(); i++)
		{
		   delete letters[i];
		   letters.clear();
		}

	}

	if (Sans != NULL)
	{
		TTF_CloseFont(Sans);
		Sans = NULL;

	}
}

void GameScene::reset() {
    speed_factor = 1;

    letters.clear();

	Uint8 r = std::stoi(sceneInfo["letter-r"]);
	Uint8 g = std::stoi(sceneInfo["letter-g"]);
	Uint8 b = std::stoi(sceneInfo["letter-b"]);

    SDL_Color color = {r, g, b, 255};

    letters.push_back(new Letter(renderer, Sans, 'a', color));
    letters[0]->setPosition( rand_min_max(0, config->getWidth()-config->getLetterWidth()), 0);
    letters[0]->setWidth( rand_min_max(config->getLetterWidth()/2, config->getLetterWidth()));
    letters[0]->setHeight( rand_min_max(config->getLetterHeight()/2, config->getLetterHeight()));

    uint32_t param;
    my_timer_id = SDL_AddTimer(timer_delay, my_callbackfunc, &param);

    config->setHighScore(0);
}

bool GameScene::move_letters() {
    for(unsigned int i=0; i<letters.size();i++)
    {
        letters[i]->setPositionY(letters[i]->getPositionY() + speed_factor);

        /*if (letters[i].getY() > config->getHeight()-LETTER_HEIGHT)
            return true;
            */
        if (letters[i]->getPositionY() > config->getHeight())  {

            if( !note_eog.play()) {
                printf("Could not play a note");
            }

            return true;
        }
    }

    return false;
}

void GameScene::display_letters() {
    for(unsigned int i=0; i<letters.size();i++) {
        letters[i]->display();
    }
}

char get_rand_letter() {
    return rand_min_max(97, 122);
}

char get_rand_string_letter(std::string text) {
    int which = rand_min_max(0, text.length()-1 );
	return text[which];
}

void GameScene::new_letter()
{
    if (!notes[rand_min_max(0, 6)].play() ) {
        printf("Could not play a note");
    }

    delete letters[letters.size()-1];
    letters.pop_back();

	char letter = get_rand_string_letter(sceneInfo["letters"]);

	Uint8 r = std::stoi(sceneInfo["letter-r"]);
	Uint8 g = std::stoi(sceneInfo["letter-g"]);
	Uint8 b = std::stoi(sceneInfo["letter-b"]);

    SDL_Color color = {r, g, b, 255};

    letters.push_back(new Letter(renderer, Sans, letter, color));
    letters[0]->setPositionX( rand_min_max(0, config->getWidth()-config->getLetterWidth()));
    letters[0]->setWidth( rand_min_max(config->getLetterWidth()/2, config->getLetterWidth()));
    letters[0]->setHeight( rand_min_max(config->getLetterHeight()/2, config->getLetterHeight()));

    config->setHighScore(config->getHighScore()+1);

    updateCounter();
}

bool GameScene::check_if_killed(char key) {
    bool killed = false;

    for(unsigned int i=0; i<letters.size(); i++) {
        if (letters[i]->is(key)) {
            killed = true;
            new_letter();
        }
    }

    if (killed) {
        //speed_factor++;
    }

    return killed;
}

int GameScene::handleEvents()
{
    int status = -1;

    SDL_Event e;
    if ( SDL_PollEvent(&e) ) {
        if (e.type == SDL_QUIT)
			return 1;
        else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			return 1;
        else if (e.type == SDL_KEYDOWN) {
            if (check_if_killed((char)e.key.keysym.sym)) {
				unsigned int limit = std::stoi(sceneInfo["limit"]);

                if (config->getHighScore() > limit) {
					return 0;
                }
            }

        }
        else if (e.type == SDL_USEREVENT) {
            if (this->move_letters() ) {
                return 0;
            }
        }
    }

    return status;
}

int GameScene::write() {
    int status = -1;

    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = config->getWidth(); texr.h = config->getHeight();

    status = handleEvents();
	if (status != -1)
		return status;

    wall->draw(NULL, &texr);

    this->display_letters();

    if (counter_text) {
        SDL_Rect Message_rect;
        Message_rect.x = config->getXpercent(0.9);
        Message_rect.y = config->getYpercent(0.05);
        Message_rect.w = config->getLetterWidth();
        Message_rect.h = config->getLetterHeight();
        counter_text->draw(NULL, &Message_rect);
    }

    return status;
}

void GameScene::updateCounter() {
	Uint8 r = std::stoi(sceneInfo["letter-r"]);
	Uint8 g = std::stoi(sceneInfo["letter-g"]);
	Uint8 b = std::stoi(sceneInfo["letter-b"]);

    SDL_Color color = {r, g, b, 255};
    counter_string = std::to_string(config->getHighScore() );

    if (counter_text != NULL) {
		delete counter_text;
    }

    counter_text = new DrawText(counter_string, renderer, Sans, color);
}

std::string GameScene::getName() {
    return sceneInfo["name"];
}
