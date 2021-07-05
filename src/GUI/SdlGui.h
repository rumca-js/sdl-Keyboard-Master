#ifndef _H_GUI_H_
#define _H_GUI_H_

class SdlGui
{
    public:
        SdlGui & getObject();
        void addWidget(SdlWidget & widget);
        void display();
        void update(Uint16 mmsec);
        void checkInput();
};

#endif // _H_GUI_H_
