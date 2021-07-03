/*
 * Button.cpp
 *
 *  Created on: 24 mar 2018
 *      Author: hunter
 */

#include "Button.h"

Button::Button(SDL_Renderer * renderer, std::string text) {
	_r = renderer;
	_font = NULL;

	_text = text;

	_posx = 0.0;
	_posy = 0.0;

	_width  = 1.0;
	_height = 1.0;

	_hover = false;

	config = &MainConfiguration::getConfig();
}

Button::~Button() {
	tex_normal.close();
	tex_hover.close();
	text.close();
}

bool Button::load() {
	text.open(_text, _r, _font, _color);

	return true;
}

void Button::setPosition(double posx, double posy) {
	_posx = posx;
	_posy = posy;
}

void Button::setDimentions(double width, double height) {
	_width = width;
	_height = height;
}

void Button::setTextures(std::string texture, std::string hover_texture) {
	tex_normal.open(texture, _r);
	tex_hover.open(hover_texture, _r);
}

void Button::setFont(TTF_Font * Font, SDL_Color & color) {
	_font = Font;
	_color = color;
}

void Button::draw() {

	SDL_Rect texr;
	texr.x = config->getXpercent(_posx);
	texr.y = config->getYpercent(_posy);
	texr.w = config->getXpercent(_width);
	texr.h = config->getYpercent(_height);

	if (_hover) {
		tex_hover.draw(NULL, &texr);
	}
	else {
		tex_normal.draw(NULL, &texr);
	}

	SDL_Rect textr;
	textr.x = config->getXpercent(_posx);
	textr.y = config->getYpercent(_posy);
	textr.w = config->getXpercent(_height)*(double)_text.length()/2.0;
	textr.h = config->getYpercent(_height);

	text.draw(NULL, &textr);
}

void Button::setHover(bool hover) {
	_hover = hover;
}
