#ifndef __H_SCREENELEMENT_H_
#define __H_SCREENELEMENT_H_

class ScreenElement
{
    /*!
     *      * \brief Position of the button.
     *           */
    int _posx, _posy, _width, _height;

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

    void setWidth(int w);
    void setHeight(int h);
    int getPositionX();
    int getPositionY();
    void setPositionX(int x);
    void setPositionY(int y);
    int getWidth();
    int getHeight();
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
