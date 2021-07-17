/*
 * ScreenStateElement.cpp
 */

#include "./ScreenStateElement.h"

#include "MainConfiguration.h"
#include "ScreenStateElement.h"

ScreenStateElement::ScreenStateElement(SDL_Renderer *ren) {
    renderer = ren;

	setDimensions(0, 0);
    setPosition(0,0);
}

ScreenStateElement::~ScreenStateElement() {
	for(auto it = items.begin(); it != items.end(); it++)
	{
		delete it->second;
	}
}

void ScreenStateElement::display() {
    SDL_Rect Message_rect;
    Message_rect.x = getPositionX();
    Message_rect.y = getPositionY();
    Message_rect.w = getWidth();
    Message_rect.h = getHeight();

	DrawItem * item = items[state];
	item->draw(NULL, &Message_rect);
}

bool ScreenStateElement::setState(unsigned int newState) {
	if (items.find(newState) != items.end()) {
		state = newState;
		return true;
	}

	return false;
}

unsigned int ScreenStateElement::getState() {
	return state;
}
