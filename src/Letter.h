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
	char letter;

public:
	Letter(SDL_Renderer *ren, TTF_Font* Sans, char letter);
	void move();
	void display();
	unsigned getX();
	unsigned getY();
	void setX(unsigned _x);
	bool is(char key);
	virtual ~Letter();
};

#endif /* LETTER_H_ */
