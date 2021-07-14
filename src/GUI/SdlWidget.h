#ifndef __H_SDL_WIDGET_H_
#define __H_SDL_WIDGET_H_

#include "ScreenElement.h"
#include "ScreenElement.cpp"

class SdlWidget : public ScreenElement<int>
{
    public:
    /*!
     * initialize widget
     */
    virtual void init();
    /*!
     * draw widget
     */
    virtual void draw();
    /*!
     * close widget
     */
    virtual void close();
};

#endif
