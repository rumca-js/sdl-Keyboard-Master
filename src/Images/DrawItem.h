
//
// vector<Items> items;
// items.push_back(new GifItem("../data/test.gif"));
// items.push_back(new JpegItem("../data/test.jpeg"));
//
// draw()
// {
//    for(int i=0;i<items.size();i++)
//    	items[i]->update(time());
//    	items[i]->draw();
// }
//

#ifndef DRAWITEM_H_
#define DRAWITEM_H_

#include <string>
#include <SDL2/SDL.h>

/*!
 * Abstract class
 */
class DrawItem
{
protected:
    /*!
     * Indicates whether it has been initialized
     */
	bool initialized;
    /*!
     * SDL renderer
     */
	SDL_Renderer * renderer;
    /*!
     * width of the object
     */
	Uint16 width;
    /*!
     * height of the object
     */
    Uint16 height;
public:
    /*!
     * Constructs drawable item
     */
    DrawItem();
    /*!
     * Deconstructs drawable item
     */
    virtual ~DrawItem();
    /*!
     * Updates the drawable item according passage of time
     */
	virtual void update(Uint32 time) = 0;
    /*!
     * Draws the item
     */
	virtual void draw(SDL_Rect * SrcR=NULL, SDL_Rect * DestR=NULL) = 0;
    /*!
     * Disposes data of the item
     */
	virtual void close();
    /*!
     * Returns width
     */
	virtual Uint16 getWidth() = 0;
    /*!
     * Returns height
     */
	virtual Uint16 getHeight() = 0;
};

#endif // DRAWITEM_H_
