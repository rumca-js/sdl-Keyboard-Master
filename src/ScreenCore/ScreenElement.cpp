#ifndef _CPP_SCREENELEMENT_CPP_
#define _CPP_SCREENELEMENT_CPP_

#include "ScreenElement.h"

template <class T>
void ScreenElement<T>::init() {
}

template <class T>
void ScreenElement<T>::draw() {
}

template <class T>
void ScreenElement<T>::close() {
}

template <class T>
void ScreenElement<T>::setPosition(T posx, T posy) {
    _posx = posx;
    _posy = posy;
}

template <class T>
void ScreenElement<T>::setDimensions(T width, T height) {
    _width = width;
    _height = height;
}

template <class T>
void ScreenElement<T>::setPositionR(double posx, double posy) {
    _posx = posx;
    _posy = posy;
}

template <class T>
void ScreenElement<T>::setDimensionsR(double width, double height) {
    _width = width;
    _height = height;
}

template <class T>
void ScreenElement<T>::setPositionX(T posx) {
    _posx = posx;
}

template <class T>
void ScreenElement<T>::setPositionY(T posy) {
    _posy = posy;
}

template <class T>
T ScreenElement<T>::getPositionX() {
	return _posx;
}

template <class T>
T ScreenElement<T>::getPositionY() {
	return _posy;
}

template <class T>
T ScreenElement<T>::getWidth() {
	return _width;
}

template <class T>
T ScreenElement<T>::getHeight() {
	return _height;
}

template <class T>
void ScreenElement<T>::setWidth(T w) {
	_width = w;
}

template <class T>
void ScreenElement<T>::setHeight(T h) {
	_height = h;
}

#endif //_CPP_SCREENELEMENT_CPP_
