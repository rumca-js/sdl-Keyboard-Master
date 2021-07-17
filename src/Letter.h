/*
 * Letter.h
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#ifndef LETTER_H_
#define LETTER_H_

#include <SDL2/SDL_ttf.h>
#include "./Images/DrawLetter.h"
#include "ScreenStateElement.h"

class Letter : public ScreenStateElement {
    /*!
     * \brief SDL renderer
     */
    SDL_Renderer *renderer = NULL;
    char letter;
    const unsigned int STATE_NORMAL = 0;
    const unsigned int STATE_DESTROYED = 1;
    const unsigned int STATE_TO_REMOVE = 2;

public:
    /*!
     * \brief The constructor just copy the pointers.
     */
    Letter(SDL_Renderer *ren, TTF_Font* Sans, char letter, SDL_Color aColor);
    virtual ~Letter();
    bool is(char key);
    bool setDestroyed();
    bool setToRemove();
    bool isRemovable();
};

#endif /* LETTER_H_ */
