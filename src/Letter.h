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
#include "./GUI/ScreenElement.h"
#include "./GUI/ScreenElement.cpp"

class Letter : public ScreenElement<double> {
    /*!
     * \brief SDL renderer
     */
    SDL_Renderer *renderer = NULL;
    /*!
     * \brief SDL texture for letter.
     */
    DrawLetter dletter;
    char letter;

public:
    /*!
     * \brief The constructor just copy the pointers.
     */
    Letter(SDL_Renderer *ren, TTF_Font* Sans, char letter, SDL_Color aColor);
    virtual ~Letter();
    /*!
     * \brief Displays the letter using renderer.
     */
    void display();
    bool is(char key);
};

#endif /* LETTER_H_ */
