/*
 * Letter.cpp
 */

#include "MainConfiguration.h"
#include "Letter.h"
#include "./Images/DrawLetter.h"

Letter::Letter(SDL_Renderer *ren, TTF_Font* Sans, char _letter, SDL_Color aColor) {
    renderer = ren;

    letter= _letter;

    unsigned int _w = MainConfiguration::getConfig().getLetterWidth();
    unsigned int _h = MainConfiguration::getConfig().getLetterHeight();
	setDimensions(_w, _h);

    if (Sans != NULL) {
          dletter.open(letter, ren, Sans, aColor);
    }
    else {
        printf("Could not open font");
    }

    setPosition(0,0);
}

Letter::~Letter() {
    dletter.close();
}

bool Letter::is(char key) {
    if (key == letter)
        return true;
    return false;
}

void Letter::display() {
    SDL_Rect Message_rect;
    Message_rect.x = getPositionX();
    Message_rect.y = getPositionY();
    Message_rect.w = getWidth();
    Message_rect.h = getHeight();
    dletter.draw(NULL, &Message_rect);
}
