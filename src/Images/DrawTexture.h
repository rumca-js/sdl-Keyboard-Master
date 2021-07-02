#ifndef DRAWTEXTURE_H_
#define DRAWTEXTURE_H_

#include <SDL2/SDL_image.h>
#include "DrawItem.h"

/*!
 * Drawable texture item
 */
class DrawTexture : public DrawItem
{
	SDL_Texture * texture;

    public:
        /*!
         * Constructs texture
         */
        DrawTexture(std::string path, SDL_Renderer * aRenderer);
        ~DrawTexture();
        /*!
         * Updates flow of time
         */
        void update(Uint32 time);
        /*!
         * Draws texture
         */
        void draw(SDL_Rect * SrcR, SDL_Rect * DestR);
        /*!
         * closes the texture
         */
        void close();
        /*!
         * Returns width of the texture
         */
        Uint16 getWidth();
        /*!
         * Returns height of the texture
         */
        Uint16 getHeight();
};

#endif //DRAWTEXTURE_H_
