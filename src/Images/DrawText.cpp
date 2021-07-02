/*
 * DrawText.cpp
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#include "../config.h"
#include "DrawText.h"


DrawText::DrawText() {
}

DrawText::DrawText(std::string text, SDL_Renderer *ren, TTF_Font* Sans, SDL_Color color) {
	open(text, ren, Sans, color);
}

bool DrawText::open(std::string text, SDL_Renderer *ren, TTF_Font* Sans, SDL_Color color) {

    renderer = ren;

    if (Sans != NULL) {
          surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), color);
          Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    }
    else {
        printf("Could not open font");
    }
}

DrawText::~DrawText()
{
	close();
}

void DrawText::close() {

    if (surfaceMessage != NULL) {
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);
        surfaceMessage = NULL;
        Message = NULL;
    }
}

void DrawText::draw(SDL_Rect * srcR, SDL_Rect * dstR) {
    SDL_RenderCopy(renderer, Message, srcR, dstR);
}

Uint16 DrawText::getWidth() {
	return 100;
}

Uint16 DrawText::getHeight() {
	return 100;
}

void DrawText::update(Uint32 time) {
}
