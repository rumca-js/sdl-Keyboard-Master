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
	/*!
	 * \brief SDL renderer
	 */
	SDL_Renderer *renderer = NULL;
	/*!
	 * \brief SDL texture for letter.
	 */
	SDL_Texture* Message = NULL;
	/*!
	 * \brief Position of the letter.
	 */
	unsigned x,y;
	/*!
	 * \brief The actual letter that will be displayed.
	 */
	char letter;

public:
	/*!
	 * \brief The constructor just copy the pointers.
	 */
	Letter(SDL_Renderer *ren, TTF_Font* Sans, char letter);
	/*!
	 * \brief Displays the letter using renderer.
	 */
	void display();
	/*!
	 * \brief Returns X position.
	 */
	unsigned getX();
	/*!
	 * \brief Returns Y position.
	 */
	unsigned getY();
	/*!
	 * \brief Sets X position.
	 */
	void setX(unsigned);
	/*!
	 * \brief Sets Y position.
	 */
	void setY(unsigned);
	/*!
	 * \brief Returns true if this char is equal to <key>.
	 */
	bool is(char key);
	virtual ~Letter();

};

#endif /* LETTER_H_ */
