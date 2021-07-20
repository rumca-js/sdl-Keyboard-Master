
#include "SceneCommons.h"

#include "../Audio/MusicManager.h"


void SceneCommons::MakeSureMyMusicIsPlaying() {
    MusicManager & man = MusicManager::getObject();
    std::string myMusic = sceneInfo["music"];

    if (!MusicManager::isPlaying())
    {
        man.addMusic(myMusic);
        man.play();

    }
    else
    {
        if (!man.isMyMusicPlaying(myMusic, true)) {
            man.resetQueue();
            man.stop();

            man.addMusic( myMusic );
            man.play();
        }
    }
}

void SceneCommons::init()
{
}

int SceneCommons::write()
{
}

void SceneCommons::close()
{
}

void SceneCommons::onEnter()
{
}

void SceneCommons::onLeave()
{
}

std::string SceneCommons::getName() {
    return sceneInfo["name"];
} 

int SceneCommons::handleEvents()
{
}
