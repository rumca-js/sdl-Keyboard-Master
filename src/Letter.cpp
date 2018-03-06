/*
 * Letter.cpp
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#include "config.h"
#include "Letter.h"

Letter::Letter(SDL_Renderer *ren, TTF_Font* Sans, char letter) {
	renderer = ren;
	char text[4];

	text[0] = letter;
	text[1] = '\0';

    if (Sans != NULL)
    {
   	    SDL_Color White = {255, 0, 0};
  	    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, &text[0], White);
  	    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    }
    else
    {
    	printf("Could not open font");
    }

    unsigned min, max;
    max = WIDTH-LETTER_WIDTH;
    min = 0;

    x = min + (rand() % static_cast<int>(max - min + 1));
    y = 0;
}

void Letter::move()
{
	//x += 1;
	y += 1;
}

unsigned int Letter::getX()
{
	return x;
}

unsigned int Letter::getY()
{
	return y;
}

void Letter::display()
{
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

Letter::~Letter() {
	// TODO Auto-generated destructor stub
}

