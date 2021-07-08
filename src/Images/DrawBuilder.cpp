
#include <string>
#include "DrawBuilder.h"

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


std::vector<DrawItem*> & DrawBuilder::GetUpdateItems()
{
	return DrawBuilder::updateItems;
}

DrawItem * DrawBuilder::Build(std::string item, SDL_Renderer* renderer)
{
	if (hasEnding(item, ".gif"))
	{
		DrawItem * result = new DrawGif(item, renderer);
		DrawBuilder::updateItems.push_back(result);
		return result;
	}
	if (hasEnding(item, ".jpg"))
		return new DrawTexture(item, renderer);
	if (hasEnding(item, ".png"))
		return new DrawTexture(item, renderer);

	return NULL;
}

std::vector<DrawItem*> DrawBuilder::updateItems;
