/*
 * DrawLetter.cpp
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#include "../config.h"
#include "DrawLetter.h"


DrawLetter::DrawLetter(char _letter, SDL_Renderer *ren, TTF_Font* Sans) {
    char text[4];

    renderer = ren;

    text[0] = _letter;
    text[1] = '\0';

    letter= _letter;

    if (Sans != NULL) {
          SDL_Color White = {255, 0, 0, 255};
          surfaceMessage = TTF_RenderText_Solid(Sans, &text[0], White);
          Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    }
    else {
        printf("Could not open font");
    }
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
