
#include <iostream>
#include "DrawTexture.h"


DrawTexture::DrawTexture()
{
}

DrawTexture::DrawTexture(std::string path, SDL_Renderer * aRenderer) {
	open(path, aRenderer);
}

bool DrawTexture::open(std::string path, SDL_Renderer * aRenderer) {
	renderer = aRenderer;

	//SDL_Surface * Loading_Surf = SDL_LoadBMP(path.c_str());
	SDL_Surface * Loading_Surf = IMG_Load(path.c_str() );
	if (!Loading_Surf)
	{
		std::cout << "Cannot load surface" << std::endl;
		return false;
	}

  	texture = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
	if (!texture)
	{
		std::cout << "Cannot load texture" << std::endl;
		std::cout << SDL_GetError();
		return false;
	}

  	SDL_FreeSurface(Loading_Surf);

	return true;
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
	int w,h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	return w;
}

Uint16 DrawTexture::getHeight() {
	int w,h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	return h;
}

