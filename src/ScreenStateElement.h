#ifndef _H_SCREENSTATEELEMENT_H_
#define _H_SCREENSTATEELEMENT_H_

#include <SDL2/SDL_ttf.h>
#include <map>

#include "./Images/DrawLetter.h"
#include "./GUI/ScreenElement.h"
#include "./GUI/ScreenElement.cpp"

class ScreenStateElement : public ScreenElement<unsigned int> {
  protected:
    /*!
     * \brief SDL renderer
     */
    SDL_Renderer *renderer = NULL;
    /*!
     * \brief state vs image mapping
     */
    std::map<unsigned int,DrawItem*> items;
    unsigned int state;

  public:
    /*!
     * \brief The constructor just copy the pointers.
     */
    ScreenStateElement(SDL_Renderer *ren);
    virtual ~ScreenStateElement();
    virtual void display();
};

#endif /* LETTER_H_ */
