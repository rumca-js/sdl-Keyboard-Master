#include "ScreenElement.h"

void ScreenElement::init() {
}
void ScreenElement::draw() {
}
void ScreenElement::close() {
}

void ScreenElement::setPosition(int posx, int posy) {
    _posx = posx;
    _posy = posy;
}

void ScreenElement::setDimensions(int width, int height) {
    _width = width;
    _height = height;
}

void ScreenElement::setPositionR(double posx, double posy) {
    _posx = posx;
    _posy = posy;
}

void ScreenElement::setDimensionsR(double width, double height) {
    _width = width;
    _height = height;
}

void ScreenElement::setPositionX(int posx) {
    _posx = posx;
}

void ScreenElement::setPositionY(int posy) {
    _posy = posy;
}

int ScreenElement::getPositionX() {
	return _posx;
}

int ScreenElement::getPositionY() {
	return _posy;
}

int ScreenElement::getWidth() {
	return _width;
}

int ScreenElement::getHeight() {
	return _height;
}

void ScreenElement::setWidth(int w) {
	_width = w;
}

void ScreenElement::setHeight(int h) {
	_height = h;
}
