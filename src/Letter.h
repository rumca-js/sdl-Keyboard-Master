/*
 * Letter.h
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#ifndef LETTER_H_
#define LETTER_H_

#include <SDL2/SDL_ttf.h>

class Letter {
	SDL_Texture* Message = NULL;
	SDL_Renderer *renderer = NULL;
	unsigned x,y;

public:
	Letter(SDL_Renderer *ren, TTF_Font* Sans, char letter);
	void move();
	void display();
	unsigned int getX();
	unsigned int getY();
	virtual ~Letter();
};

#endif /* LETTER_H_ */
