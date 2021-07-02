#ifndef DRAWGIF_H_
#define DRAWGIF_H_

#include <vector>
#include "SDL_gifwrap.h"
#include "DrawItem.h"

/*!
 * Drawable GIF item
 */
class DrawGif : public DrawItem
{
    /*!
     * gif structure
     */
	GIF_Image* gif;
    /*!
     * current frame of gif
     */
	Uint32 current_frame;
    /*!
     * amount of cumulated mseconds
     */
    Uint32 msec_store;
    /*!
     * frame textures
     */
    std::vector<SDL_Texture*> textures;

    public:
        DrawGif();
        DrawGif(std::string path, SDL_Renderer * aRenderer);
        bool open(std::string path, SDL_Renderer * aRenderer);
        virtual ~DrawGif();
        /*!
         * closes Gif
         */
        void close();
        /*!
         * Draws GIF
         */
        void draw(SDL_Rect*, SDL_Rect*);
        /*!
         * Returns gif width
         */
        Uint16 getWidth();
        /*!
         * Returns gif height
         */
        Uint16 getHeight();
        /*!
         * Updates 'flow of time' in gif animation
         * @param msec_time milliseconds of time
         */
        void update(Uint32 msec_time);
        void incrementFrame();
};

#endif //DRAWGIF_H_
