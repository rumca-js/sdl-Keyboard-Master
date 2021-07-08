#ifndef _H_DRAW_BUILDER_H_
#define _H_DRAW_BUILDER_H_

#include <string>

#include "DrawGif.h"
#include "DrawItem.h"
#include "DrawLetter.h"
#include "DrawText.h"
#include "DrawTexture.h"

class DrawBuilder
{
	static std::vector<DrawItem*> updateItems;
	public:
	static DrawItem * Build(std::string item, SDL_Renderer * renderer);
	static std::vector<DrawItem*> & GetUpdateItems();
};

#endif //_H_DRAW_BUILDER_H_
