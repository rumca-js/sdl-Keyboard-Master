/*
 * Letter.cpp
 */

#include "MainConfiguration.h"
#include "Letter.h"
#include "./Images/DrawLetter.h"
#include "./Images/DrawGif.h"

Letter::Letter(SDL_Renderer *ren, TTF_Font* Sans, char _letter, SDL_Color aColor) 
	: ScreenStateElement(ren)
{
    renderer = ren;

    letter= _letter;

    unsigned int _w = MainConfiguration::getConfig().getLetterWidth();
    unsigned int _h = MainConfiguration::getConfig().getLetterHeight();
	setDimensions(_w, _h);

	state = 0;

    if (Sans != NULL) {
		items[STATE_NORMAL] = new DrawLetter(letter, ren, Sans, aColor);
		items[STATE_DESTROYED] = new DrawGif("data/textures/explosion.gif", ren);
    }
    else {
        printf("Could not open font");
    }

    setPosition(0,0);

	forceX = 0;
	forceY = 0;
}

Letter::~Letter() {
}

bool Letter::is(char key) {
    if (key == letter)
        return true;
    return false;
}

void Letter::move() {
    setPositionX(getPositionX() + forceX);
    setPositionY(getPositionY() + forceY);
}

bool Letter::setDestroyed() {
	DrawGif * gif = (DrawGif *)items[STATE_DESTROYED];
	gif->resetAnimation();
	return setState(STATE_DESTROYED);
}

bool Letter::isRemovable() {
	DrawGif * gif = (DrawGif *)items[STATE_DESTROYED];

	return getState() == STATE_DESTROYED &&
		gif->getCycles() > 0;
}

void Letter::setForce(int aforceX, int aforceY) {
    forceX = aforceX;
    forceY = aforceY;
}
