#ifndef __H_SDL_WIDGET_H_
#define __H_SDL_WIDGET_H_

#include "ScreenElement.h"

class SdlWidget : public ScreenElement
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
