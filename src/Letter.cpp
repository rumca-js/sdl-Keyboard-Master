/*
 * Letter.cpp
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#include "config.h"
#include "Letter.h"

Letter::Letter(SDL_Renderer *ren, TTF_Font* Sans, char _letter) {
	char text[4];

	renderer = ren;

	text[0] = _letter;
	text[1] = '\0';

	letter= _letter;
	_w = LETTER_WIDTH;
	_h = LETTER_HEIGHT;

    if (Sans != NULL) {
   	    SDL_Color White = {255, 0, 0};
  	    surfaceMessage = TTF_RenderText_Solid(Sans, &text[0], White);
  	    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    }
    else {
    	printf("Could not open font");
    }

    x = 0;
    y = 0;
}

Letter::~Letter() {
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

unsigned Letter::getX() {
	return x;
}

unsigned Letter::getY() {
	return y;
}

bool Letter::is(char key) {
	if (key == letter)
		return true;
	return false;
}

void Letter::display() {
	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = _w;
	Message_rect.h = _h;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

void Letter::setX(unsigned _x) {
	x = _x;
}

void Letter::setY(unsigned _y) {
	y = _y;
}
void Letter::setWidth(unsigned int width) {
	_w = width;
}
void Letter::setHeight(unsigned int height) {
	_h = height;
}
