
#include <iostream>
#include "DrawItem.h"

DrawItem::DrawItem()
{
    initialized = true;
}

DrawItem::~DrawItem()
{
    close();
}

void DrawItem::close()
{
    std::cout << "DrawItem close" << std::endl;
}

Uint16 DrawItem::getWidth()
{
    return 1;
}

Uint16 DrawItem::getHeight()
{
    return 1;
}
