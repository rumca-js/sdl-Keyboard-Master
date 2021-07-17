/*
 * Letter.cpp
 */

#include "MainConfiguration.h"
#include "Letter.h"
#include "./Images/DrawLetter.h"

Letter::Letter(SDL_Renderer *ren, TTF_Font* Sans, char _letter, SDL_Color aColor) 
	: ScreenStateElement(ren)
{
    renderer = ren;

    letter= _letter;

    unsigned int _w = MainConfiguration::getConfig().getLetterWidth();
    unsigned int _h = MainConfiguration::getConfig().getLetterHeight();
	setDimensions(_w, _h);

    if (Sans != NULL) {
		items[state] = new DrawLetter(letter, ren, Sans, aColor);
    }
    else {
        printf("Could not open font");
    }

    setPosition(0,0);
}

Letter::~Letter() {
}

bool Letter::is(char key) {
    if (key == letter)
        return true;
    return false;
}
