/*
 * GameScene.cpp
 *
 *  Created on: 4 mar 2018
 */

#include <iostream>

#include "../Utilities.h"
#include "../Audio/MusicManager.h"
#include "../GameEventLogger.h"
#include "GameScene.h"


static Uint32 my_callbackfunc(Uint32 interval, void *param) {
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
    letter_ms_move_time  = 50;
    speed_factor = 1.0;
}

GameScene::~GameScene() {
    // TODO Auto-generated destructor stub
}

void GameScene::MakeSureMyMusicIsPlaying() {
	MusicManager & man = MusicManager::getObject();
    std::string myMusic = sceneInfo["music"];

    if (!MusicManager::isPlaying())
    {
        man.addMusic(myMusic);
        man.play();

    }
    else
    {
        if (!man.isMyMusicPlaying(myMusic, true)) {
            man.resetQueue();
            man.stop();

            man.addMusic( myMusic );
            man.play();
        }
    }
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

    MakeSureMyMusicIsPlaying();
}

void GameScene::close() {

	SDL_RemoveTimer( my_timer_id );

	if (wall != NULL)
	{
		delete wall;
		wall = NULL;
	}

	if (letters_active.size() != 0)
	{
		for(unsigned int i=0; i<letters_active.size(); i++)
		{
		   delete letters_active[i];
		   letters_active.clear();
		}

	}

	if (Sans != NULL)
	{
		TTF_CloseFont(Sans);
		Sans = NULL;

	}
}

void GameScene::reset() {
    speed_factor = config->getYpercent(0.005);

    letters_active.clear();

	create_new_letter();

    uint32_t param;
    my_timer_id = SDL_AddTimer(letter_ms_move_time, my_callbackfunc, &param);
}

static char get_rand_letter() {
    return rand_min_max(97, 122);
}

static char get_rand_string_letter(std::string text) {
    int which = rand_min_max(0, text.length()-1 );
	return text[which];
}

void GameScene::create_new_letter()
{
	char letter = get_rand_string_letter(sceneInfo["letters"]);

	Uint8 r = std::stoi(sceneInfo["letter-r"]);
	Uint8 g = std::stoi(sceneInfo["letter-g"]);
	Uint8 b = std::stoi(sceneInfo["letter-b"]);

    SDL_Color color = {r, g, b, 255};

    letters_active.push_back(new Letter(renderer, Sans, letter, color));
    letters_active[0]->setPosition( rand_min_max(0, config->getWinWidth()-config->getLetterWidth()), 0);
    letters_active[0]->setWidth( rand_min_max(config->getLetterWidth()/2, config->getLetterWidth()));
    letters_active[0]->setHeight( rand_min_max(config->getLetterHeight()/2, config->getLetterHeight()));
}

bool GameScene::move_letters() {
    for(unsigned int i=0; i<letters_active.size();i++)
    {
        letters_active[i]->setPositionY(letters_active[i]->getPositionY() + speed_factor);

        // It does not depend on windows size, because Y position is incremented
        // by window relative value

        if (letters_active[i]->getPositionY() > config->getWinHeight())  {

            if( !note_eog.play()) {
                printf("Could not play a note");
            }

            return true;
        }
    }

    return false;
}

void GameScene::display_letters() {
    for(unsigned int i=0; i<letters_active.size();i++) {
        letters_active[i]->display();
    }
}

void GameScene::kill_letter(Letter * letter)
{
    if (!notes[rand_min_max(0, 6)].play() ) {
        printf("Could not play a note");
    }

	letter->setDestroyed();

	GameEventLogger & logger = GameEventLogger::getObject();
	logger.addSuccessfulKeyStroke();

    updateCounter();
}

bool GameScene::check_if_killed(char key) {
    bool killed = false;

	std::vector<Letter*> alive;
	std::vector<Letter*> to_kill;

	// Do not operate on active letters. Cannot remove elements
	// while iterating over it.
    for(unsigned int i=0; i<letters_active.size(); i++) {
        if (letters_active[i]->is(key)) {
            killed = true;
			to_kill.push_back(letters_active[i]);
        }
		else
		{
			alive.push_back(letters_active[i]);
		}
    }

	letters_active = alive;
	letters_inactive = to_kill;

    for(unsigned int i=0; i<letters_inactive.size(); i++) {
		kill_letter(letters_inactive[i]);
		create_new_letter();
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
			GameEventLogger & logger = GameEventLogger::getObject();

            if (check_if_killed((char)e.key.keysym.sym)) {
				unsigned int limit = std::stoi(sceneInfo["limit"]);

                if (logger.getSuccessfulKeyStrokes() > limit) {
					return 0;
                }
            }
			else {
				logger.addUnSuccessfulKeyStroke();
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

void GameScene::check_if_remove_letters() {
	std::vector<Letter*> to_leave;
	std::vector<Letter*> to_remove;

	for(unsigned int i=0; i<letters_inactive.size(); i++)
	{
		if (letters_inactive[i]->isRemovable())
			to_remove.push_back(letters_inactive[i]);
		else
			to_leave.push_back(letters_inactive[i]);
	}

	letters_inactive = to_leave;

	for(unsigned int i=0; i<to_remove.size(); i++)
	{
		delete to_remove[i];
	}
}

int GameScene::write() {
    int status = -1;

    SDL_Rect texr;
	texr.x = 0; texr.y = 0;
	texr.w = config->getWinWidth();
	texr.h = config->getWinHeight();

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

	check_if_remove_letters();

    return status;
}

void GameScene::updateCounter() {
	Uint8 r = std::stoi(sceneInfo["letter-r"]);
	Uint8 g = std::stoi(sceneInfo["letter-g"]);
	Uint8 b = std::stoi(sceneInfo["letter-b"]);

    GameEventLogger & logger = GameEventLogger::getObject();

    SDL_Color color = {r, g, b, 255};
    counter_string = std::to_string(logger.getSuccessfulKeyStrokes() );

    if (counter_text != NULL) {
		delete counter_text;
    }

    counter_text = new DrawText(counter_string, renderer, Sans, color);
}

std::string GameScene::getName() {
    return sceneInfo["name"];
}

std::string GameScene::getEngineName() {
    return "GAME";
}
