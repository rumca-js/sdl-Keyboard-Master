#ifndef __H_SDL_WIDGET_H_
#define __H_SDL_WIDGET_H_

class SdlWidget
{
    /*!
     * initialize widget
     */
    void init();
    /*!
     * draw widget
     */
    void draw();
    /*!
     * close widget
     */
    void close();
    /*!
     * sets position
     */
    void setPosition(int x, int y);
    /*!
     * sets dimensions
     */
    void setDimensions(int w, int h);
    /*!
     * relative toward screen position
     */
    void setPositionR(double x, double y);
    /*!
     * relative toward screen dimentions
     */
    void setDimensionsR(double w, double h);
};

#endif
