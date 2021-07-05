/*
 * Letter.cpp
 *
 *  Created on: 6 mar 2018
 *      Author: hunter
 */

#include "MainConfiguration.h"
#include "Letter.h"
#include "./Images/DrawLetter.h"

Letter::Letter(SDL_Renderer *ren, TTF_Font* Sans, char _letter) {
    renderer = ren;

    letter= _letter;
    _w = MainConfiguration::getConfig().getLetterWidth();
    _h = MainConfiguration::getConfig().getLetterHeight();

    if (Sans != NULL) {
           SDL_Color White = {255, 0, 0, 255};
          dletter.open(letter, ren, Sans, White);
    }
    else {
        printf("Could not open font");
    }

    x = 0;
    y = 0;
}

Letter::~Letter() {
    dletter.close();
}

unsigned Letter::getX() {
    return x;
}

unsigned Letter::getY() {
    return y;
}

bool Letter::is(char key) {
    if (key == letter)
        return true;
    return false;
}

void Letter::display() {
    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = _w;
    Message_rect.h = _h;
    dletter.draw(NULL, &Message_rect);
}

void Letter::setX(unsigned _x) {
    x = _x;
}

void Letter::setY(unsigned _y) {
    y = _y;
}
void Letter::setWidth(unsigned int width) {
    _w = width;
}
void Letter::setHeight(unsigned int height) {
    _h = height;
}
