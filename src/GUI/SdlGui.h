#ifndef _H_GUI_H_
#define _H_GUI_H_

#include "ScreenElement.h"
#include "SdlWidget.h"

class SdlGui
{
    public:
        SdlGui & getObject();
        void addWidget(SdlWidget & widget);
        void display();
        void update(unsigned int mmsec);
        void checkInput();
};

#endif // _H_GUI_H_
