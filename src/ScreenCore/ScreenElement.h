#ifndef __H_SCREENELEMENT_H_
#define __H_SCREENELEMENT_H_

template<class T>
class ScreenElement
{
    /*!
     *      * \brief Position of the button.
     *           */
    T _posx, _posy, _width, _height;

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
    virtual void setPosition(T x, T y);
    /*!
     * sets dimensions
     */
    virtual void setDimensions(T w, T h);

    void setWidth(T w);
    void setHeight(T h);
    T getPositionX();
    T getPositionY();
    void setPositionX(T x);
    void setPositionY(T y);
    T getWidth();
    T getHeight();
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
