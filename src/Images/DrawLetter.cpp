/*
 * DrawLetter.cpp
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#include "../config.h"
#include "DrawLetter.h"


DrawLetter::DrawLetter() {
}

DrawLetter::DrawLetter(char _letter, SDL_Renderer *ren, TTF_Font* Sans, SDL_Color color) {
	open(_letter, ren, Sans, color);
}

bool DrawLetter::open(char _letter, SDL_Renderer *ren, TTF_Font* Sans, SDL_Color color) {
    char text[4];

    renderer = ren;

    text[0] = _letter;
    text[1] = '\0';

    letter= _letter;

    if (Sans != NULL) {
          surfaceMessage = TTF_RenderText_Solid(Sans, &text[0], color);
          Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    }
    else {
        printf("Could not open font");
		return false;
    }

	return true;
}

DrawLetter::~DrawLetter()
{
	close();
}

void DrawLetter::close() {

    if (surfaceMessage != NULL) {
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);
        surfaceMessage = NULL;
        Message = NULL;
    }
}

void DrawLetter::draw(SDL_Rect * srcR, SDL_Rect * dstR) {
    SDL_RenderCopy(renderer, Message, srcR, dstR);
}

Uint16 DrawLetter::getWidth() {
	return 100;
}

Uint16 DrawLetter::getHeight() {
	return 100;
}

void DrawLetter::update(Uint32 time) {
}
