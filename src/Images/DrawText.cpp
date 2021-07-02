/*
 * DrawText.cpp
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#include "../config.h"
#include "DrawText.h"


DrawText::DrawText(std::string text, SDL_Renderer *ren, TTF_Font* Sans) {

    renderer = ren;

    if (Sans != NULL) {
          SDL_Color White = {255, 0, 0, 255};
          surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White);
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
