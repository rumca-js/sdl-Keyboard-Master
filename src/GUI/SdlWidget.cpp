#ifndef __H_SDL_WIDGET_H_
#define __H_SDL_WIDGET_H_

#include "SdlWidget.h"

void SdlWidget::init() {
}
void SdlWidget::draw() {
}
void SdlWidget::close() {
}

void SdlWidget::setPosition(double posx, double posy) {
    _posx = posx;
    _posy = posy;
}

void SdlWidget::setDimentions(double width, double height) {
    _width = width;
    _height = height;
}

#endif
