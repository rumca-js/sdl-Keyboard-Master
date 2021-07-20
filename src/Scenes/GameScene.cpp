/*
 * GameScene.cpp
 *
 *  Created on: 4 mar 2018
 */

#include <iostream>
#include <sstream>

#include "../Utilities.h"
#include "../Audio/MusicManager.h"
#include "../GameEventLogger.h"
#include "GameScene.h"


void CannonInformation::timeUpdateEvent()
{
    //create new letter
    std::cout << "Creating new cannon letter" << std::endl; 
    std::cout << release_ms << std::endl;

    scene->create_cannon_letter(this);
}

int CannonInformation::getForceX()
{
    return forceX;
}

int CannonInformation::getForceY()
{
    return forceY;
}

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

void GameScene::parseCannonsInfo() {
    for(int i=1; i<=10; i++)
    {
        parseCannonInfo("cannon-info" + std::to_string(i) );
    }
}

void GameScene::parseCannonInfo(std::string cannonID) {
    if (sceneInfo[cannonID] == "")
        return;

    std::stringstream stream(sceneInfo[cannonID]);
    std::string segment;
    int i = 0;

    CannonInformation cannon;
    cannon.scene = this;

    while(std::getline(stream, segment, ';'))
    {
        if (i == 0)
            cannon.direction = segment;
        if (i == 1)
            cannon.setReleaseTime(std::stoi(segment));
        if (i == 2)
            cannon.forceX = config->getXpercent(std::stod(segment));
        if (i == 3)
            cannon.forceY = config->getYpercent(std::stod(segment));

        i++;

    }

    cannons.push_back(cannon);
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

void GameScene::init() {
    std::cout << "Game scene init" << std::endl;

    config = &MainConfiguration::getConfig();

    wall = DrawBuilder::Build(sceneInfo["background"], renderer);
    wall->open( sceneInfo["background"], renderer);

    Sans = config->getDefaultFont();

    notes[0].open( config->getConfigString("SOUND_A") );
    notes[1].open( config->getConfigString("SOUND_B") );
    notes[2].open( config->getConfigString("SOUND_C") );
    notes[3].open( config->getConfigString("SOUND_D") );
    notes[4].open( config->getConfigString("SOUND_E") );
    notes[5].open( config->getConfigString("SOUND_F") );
    notes[6].open( config->getConfigString("SOUND_G") );

    note_eog.open( config->getConfigString("SOUND_END_OF_GAME") );

    parseCannonsInfo();

    std::cout << "Game scene init done" << std::endl;
}

void GameScene::clearLetters() {
    if (letters_active.size() != 0)
    {
        for(unsigned int i=0; i<letters_active.size(); i++)
        {
           delete letters_active[i];
        }
       letters_active.clear();
    }

    if (letters_inactive.size() != 0)
    {
        for(unsigned int i=0; i<letters_inactive.size(); i++)
        {
           delete letters_inactive[i];
        }
       letters_inactive.clear();
    }
}

void GameScene::close() {

    if (wall != NULL)
    {
        delete wall;
        wall = NULL;
    }

	clearLetters();

    if (Sans != NULL)
    {
        TTF_CloseFont(Sans);
        Sans = NULL;

    }

    if (cannons.size() != 0)
    {
        cannons.clear();
    }

    if (counter_text != NULL)
    {
        delete counter_text;
        counter_text = NULL;
    }
}

void GameScene::onEnter() {
    reset();
    updateCounter();

    MakeSureMyMusicIsPlaying();
}
void GameScene::onLeave() {
    SDL_RemoveTimer( my_timer_id );
}

void GameScene::reset() {
    speed_factor = config->getYpercent(0.005);

	clearLetters();

    if (cannons.size() == 0)
        create_new_letter();

    for(unsigned int i=0; i<cannons.size(); i++)
    {
		cannons[i].startCounting();
        create_cannon_letter(&cannons[i]);
    }

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

    Letter * letterObj = letters_active[letters_active.size()-1];

    letterObj->setForce(0, speed_factor);
    letterObj->setPosition( rand_min_max(0, config->getWinWidth()-config->getLetterWidth()), 0);
    letterObj->setWidth( rand_min_max(config->getLetterWidth()/2, config->getLetterWidth()));
    letterObj->setHeight( rand_min_max(config->getLetterHeight()/2, config->getLetterHeight()));
}

void GameScene::create_cannon_letter(CannonInformation * aCannon) {
    char letter = get_rand_string_letter(sceneInfo["letters"]);

    Uint8 r = std::stoi(sceneInfo["letter-r"]);
    Uint8 g = std::stoi(sceneInfo["letter-g"]);
    Uint8 b = std::stoi(sceneInfo["letter-b"]);

    SDL_Color color = {r, g, b, 255};

    letters_active.push_back(new Letter(renderer, Sans, letter, color));

    Letter * letterObj = letters_active[letters_active.size()-1];
    letterObj->setForce(aCannon->getForceX(), aCannon->getForceY());
    letterObj->setWidth( rand_min_max(config->getLetterWidth()/2, config->getLetterWidth()));
    letterObj->setHeight( rand_min_max(config->getLetterHeight()/2, config->getLetterHeight()));

    unsigned int letter_width = config->getLetterWidth();
    unsigned int letter_height = config->getLetterHeight();

    if (aCannon->direction == "south") {
        letterObj->setPosition( 
                 rand_min_max(0, config->getWinWidth()-letter_width),
                 0);
    }
    else if (aCannon->direction == "north") {
        letterObj->setPosition( 
                 rand_min_max(0, config->getWinWidth()-letter_width),
                 config->getWinHeight()-letter_height );
    }
    else if (aCannon->direction == "left") {
        letterObj->setPosition( 
                config->getWinWidth()-letter_width,
                rand_min_max(0, config->getWinHeight()-letter_height));
    }
    else if (aCannon->direction == "right") {
        letterObj->setPosition( 
                 0,
                 rand_min_max(0, config->getWinHeight()-letter_height));
    }
    else
    {
        std::cerr << "Unkown direction" << std::endl;

        letterObj->setPosition( 
                 0,0);
    }
         
}

void GameScene::update_cannon_time() {
    for(unsigned int i=0; i<cannons.size(); i++) {
        cannons[i].updateTime();
    }
}

bool GameScene::is_letter_outside_window(Letter * letter) {
    if (letter->getPositionY() <= 0)
        return true;
    if (letter->getPositionX() <= 0)
        return true;
    if (letter->getPositionY() > config->getWinHeight())
        return true;
    if (letter->getPositionX() > config->getWinWidth())
        return true;

    return false;
}

bool GameScene::move_letters() {
    for(unsigned int i=0; i<letters_active.size();i++)
    {
        letters_active[i]->move();

        // It does not depend on windows size, because Y position is incremented
        // by window relative value

        if (is_letter_outside_window(letters_active[i])) {
            handle_not_caught_letter(letters_active[i]);

            return true;
        }
    }

    return false;
}

void GameScene::handle_not_caught_letter(Letter * letter)
{
    if( !note_eog.play()) {
        printf("Could not play a note");
    }
    GameEventLogger & logger = GameEventLogger::getObject();
    logger.notCaughtLetter(letter);
}

void GameScene::display_letters() {
    for(unsigned int i=0; i<letters_active.size();i++) {
        letters_active[i]->display();
    }
}

void GameScene::display_exploded() {
    for(unsigned int i=0; i<letters_inactive.size();i++) {
        letters_inactive[i]->display();
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

        if (cannons.size() == 0)
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
            check_if_remove_letters();
            update_cannon_time();

            if (this->move_letters() ) {
                return 1;
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
    this->display_exploded();

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
