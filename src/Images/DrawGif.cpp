
#include <iostream>
#include "DrawGif.h"
#include "DrawBuilder.h"


DrawGif::DrawGif() {
	gif = NULL;
}

DrawGif::DrawGif(std::string path, SDL_Renderer * aRenderer) {
    open(path, aRenderer);
}

bool DrawGif::open(std::string path, SDL_Renderer * aRenderer) {
    renderer = aRenderer;

    gif = GIF_LoadImage(path.c_str() );

	resetAnimation();

    for(int frame=0;frame<gif->num_frames;frame++)
    {
        textures.push_back(SDL_CreateTextureFromSurface(renderer, gif->frames[frame]->surface));
    }

	DrawBuilder::AddUpdateable(this);

    return true;
}

DrawGif::~DrawGif() {
    close();
}

void DrawGif::incrementFrame() {
    current_frame++;

    if (current_frame >= gif->num_frames)
	{
        current_frame = 0;
		cycle++;
	}
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
		DrawBuilder::RemoveUpdateable(this);
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

Uint32 DrawGif::getCycles() {
	return cycle;
}

void DrawGif::resetAnimation()
{
	current_frame = 0;
	cycle = 0;
	msec_store = 0;
}
