
#include <iostream>
#include "DrawTexture.h"


DrawTexture::DrawTexture(std::string path, SDL_Renderer * aRenderer) {
	renderer = aRenderer;

	//SDL_Surface * Loading_Surf = SDL_LoadBMP(path.c_str());
	SDL_Surface * Loading_Surf = IMG_Load(path.c_str() );
	if (!Loading_Surf)
	{
		std::cout << "Cannot load surface" << std::endl;
	}

  	texture = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
	if (!texture)
	{
		std::cout << "Cannot load texture" << std::endl;
		std::cout << SDL_GetError();
	}

  	SDL_FreeSurface(Loading_Surf);
}

DrawTexture::~DrawTexture() {
	close();
}

void DrawTexture::update(Uint32 time) {
}

void DrawTexture::draw(SDL_Rect * SrcR, SDL_Rect * DestR) {
	SDL_RenderCopy(renderer, texture, SrcR, DestR);
}

void DrawTexture::close() {
    if (texture == NULL)
    {
		std::cout << "Closing texture" << std::endl;

        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

Uint16 DrawTexture::getWidth() {
	return 100;
}

Uint16 DrawTexture::getHeight() {
	return 100;
}

