/*
 * Button.h
 *
 *  Created on: 24 mar 2018
 *      Author: hunter
 */

#ifndef GUI_BUTTON_H_
#define GUI_BUTTON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "../MainConfiguration.h"

class Button {
	SDL_Renderer * _r;
	/*!
	 * \brief Global configuration (for window sizes).
	 */
	MainConfiguration * config;
	/*!
	 * \brief Flag indicating hover.
	 */
	bool _hover;
	/*!
	 * \brief Position of the button.
	 */
	double _posx, _posy, _width, _height;
	/*!
	 * \brief Text of the button.
	 */
	std::string _text;
	/*!
	 * \brief Surface of the button.
	 */
	SDL_Surface* surface;
	/*!
	 * \brief The font of the button.
	 */
	TTF_Font * _font;
	/*!
	 * \brief The color of the button.
	 */
	SDL_Color _color;
	/*!
	 * \brief Texture of the button.
	 */
	SDL_Texture * tex_normal;
	/*!
	 * \brief texture of the button.
	 */
	SDL_Texture * tex_hover;
	/*!
	 * \brief texture of the button text.
	 */
	SDL_Texture * tex_text;

public:
	/*!
	 * \brief Constructor.
	 */
	Button(SDL_Renderer * renderer, std::string text);
	/*!
	 * \brief Destructor.
	 */
	virtual ~Button();
	/*!
	 * \brief Loads resources.
	 */
	bool load();
	/*!
	 * \brief Sets button position.
	 */
	void setPosition(double posx, double posy);
	/*!
	 * \brief Sets button dimentions.
	 */
	void setDimentions(double width, double height);
	/*!
	 * \brief Sets button textures.
	 */
	void setTextures(const char * texture, const char * hover_texture);
	/*!
	 * \brief Sets button text font.
	 */
	void setFont(TTF_Font * Font, SDL_Color & color);
	/*!
	 * \brief Draws the button.
	 */
	void draw();
	/*!
	 * \brief Sets hover indication.
	 */
	void setHover(bool);
};

#endif /* GUI_BUTTON_H_ */
