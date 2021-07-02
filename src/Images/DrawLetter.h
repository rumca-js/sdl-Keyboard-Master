/*
 * DrawLetter.h
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#ifndef DRAWLETTER_H_
#define DRAWLETTER_H_

#include <SDL2/SDL_ttf.h>
#include "DrawItem.h"

/*!
 * Drawable letter
 */
class DrawLetter : public DrawItem
{
	/*!
	 * \brief SDL texture for letter.
	 */
	SDL_Texture* Message = NULL;
	/*!
	 * \brief SDL surfuce for letter.
	 */
	SDL_Surface* surfaceMessage;
	/*!
	 * \brief The actual letter that will be displayed.
	 */
	char letter;

	public:
		DrawLetter(char _letter, SDL_Renderer *ren, TTF_Font* Sans);
		virtual ~DrawLetter();
		void close();
		void draw(SDL_Rect * srcRect, SDL_Rect * destRect);
		void update(Uint32 msec);
		Uint16 getWidth();
		Uint16 getHeight();
};

#endif /* DRAWLETTER_H_ */
