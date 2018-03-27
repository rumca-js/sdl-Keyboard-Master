/*
 * Button.cpp
 *
 *  Created on: 24 mar 2018
 *      Author: hunter
 */

#include "Button.h"

Button::Button(SDL_Renderer * renderer, std::string text) {
	_r = renderer;
	surface = NULL;
	_font = NULL;

	_text = text;

	_posx = 0.0;
	_posy = 0.0;

	_width  = 1.0;
	_height = 1.0;

	tex_normal = NULL;
	tex_hover  = NULL;
	tex_text  = NULL;

	_hover = false;

	config = &MainConfiguration::getConfig();
}

Button::~Button() {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(tex_normal);
	SDL_DestroyTexture(tex_hover);
	SDL_DestroyTexture(tex_text);
}

bool Button::load() {
	surface = TTF_RenderText_Solid(_font, _text.c_str() , _color);
	tex_text = SDL_CreateTextureFromSurface(_r, surface);

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

void Button::setTextures(const char * texture, const char * hover_texture) {
	tex_normal = IMG_LoadTexture(_r, texture);
	tex_hover = IMG_LoadTexture(_r, hover_texture);
}

void Button::setFont(TTF_Font * Font, SDL_Color & color) {
	_font = Font;
	_color = color;
}

void Button::draw() {
	SDL_Rect texr; texr.x = config->getXpercent(_posx); texr.y = config->getYpercent(_posy); texr.w = config->getXpercent(_width); texr.h = config->getYpercent(_height);
	if (_hover) {
		SDL_RenderCopy(_r, tex_hover, NULL, &texr);
	}
	else {
		SDL_RenderCopy(_r, tex_normal, NULL, &texr);
	}

	SDL_Rect textr; textr.x = config->getXpercent(_posx); textr.y = config->getYpercent(_posy); textr.w = config->getXpercent(_height)*(double)_text.length()/2.0; textr.h = config->getYpercent(_height);
	SDL_RenderCopy(_r, tex_text, NULL, &textr);
}

void Button::setHover(bool hover) {
	_hover = hover;
}
