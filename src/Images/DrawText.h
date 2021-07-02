/*
 * DrawText.h
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#ifndef DrawText_H_
#define DrawText_H_

#include <SDL2/SDL_ttf.h>
#include "DrawItem.h"

/*!
 * Drawable letter
 */
class DrawText : public DrawItem
{
	/*!
	 * \brief SDL texture for letter.
	 */
	SDL_Texture* Message = NULL;
	/*!
	 * \brief SDL surfuce for letter.
	 */
	SDL_Surface* surfaceMessage;

	public:
		DrawText();
		DrawText(std::string text, SDL_Renderer *ren, TTF_Font* Sans, SDL_Color color);
        bool open(std::string text, SDL_Renderer *ren, TTF_Font* Sans, SDL_Color color);
		virtual ~DrawText();
		void close();
		void draw(SDL_Rect * srcRect, SDL_Rect * destRect);
		void update(Uint32 msec);
		Uint16 getWidth();
		Uint16 getHeight();
};

#endif /* DrawText_H_ */
