
#include <iostream>
#include "DrawGif.h"


DrawGif::DrawGif() {
}

DrawGif::DrawGif(std::string path, SDL_Renderer * aRenderer) {
	open(path, aRenderer);
}

bool DrawGif::open(std::string path, SDL_Renderer * aRenderer) {

	std::cout<< "Creating Gif"<<std::endl;

    gif = GIF_LoadImage(path.c_str() );
    current_frame = 0;
    msec_store = 0;

    renderer = aRenderer;

    for(int frame=0;frame<gif->num_frames;frame++)
    {
        textures.push_back(SDL_CreateTextureFromSurface(renderer, gif->frames[frame]->surface));
    }

	return true;
}

DrawGif::~DrawGif() {
    close();
}

void DrawGif::incrementFrame() {
    current_frame++;

    if (current_frame >= gif->num_frames)
        current_frame = 0;
}

void DrawGif::update(Uint32 msec) {
    msec_store += msec;

    if (gif->frames[current_frame]->delay == 0)
        gif->frames[current_frame]->delay = 10;

    while(true) {
        if (msec_store > gif->frames[current_frame]->delay) {
            incrementFrame();

            msec_store -= gif->frames[current_frame]->delay;
        }
        else
            break;
    }
}

void DrawGif::draw(SDL_Rect * SrcR, SDL_Rect * DestR) {
    SDL_Texture* texture = textures[current_frame];
    SDL_RenderCopy(renderer, texture, SrcR, DestR);
}

void DrawGif::close() {
    if (gif != NULL)
    {
        std::cout<< "Closing Gif"<<std::endl;
        for(int frame=0;frame<gif->num_frames;frame++)
        {
            SDL_DestroyTexture(textures[frame]);
        }
        GIF_FreeImage(gif);

        gif = NULL;
    }
}

Uint16 DrawGif::getWidth() {
    return gif->width;
}

Uint16 DrawGif::getHeight() {
    return gif->height;
}
