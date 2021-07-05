#ifndef __H_SDL_WIDGET_H_
#define __H_SDL_WIDGET_H_

class SdlWidget
{
    /*!
     *      * \brief Position of the button.
     *           */
    double _posx, _posy, _width, _height;

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
    /*!
     * sets position
     */
    virtual void setPosition(int x, int y);
    /*!
     * sets dimensions
     */
    virtual void setDimensions(int w, int h);
    /*!
     * relative toward screen position
     */
    virtual void setPositionR(double x, double y);
    /*!
     * relative toward screen dimentions
     */
    virtual void setDimensionsR(double w, double h);
};

#endif
