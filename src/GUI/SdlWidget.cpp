#include "SdlWidget.h"

void SdlWidget::init() {
}
void SdlWidget::draw() {
}
void SdlWidget::close() {
}

void SdlWidget::setPosition(int posx, int posy) {
    _posx = posx;
    _posy = posy;
}

void SdlWidget::setDimensions(int width, int height) {
    _width = width;
    _height = height;
}

void SdlWidget::setPositionR(double posx, double posy) {
    _posx = posx;
    _posy = posy;
}

void SdlWidget::setDimensionsR(double width, double height) {
    _width = width;
    _height = height;
}
