
#include <iostream>

#include "SceneMachine.h"
#include "../GameEventLogger.h"

#include "MenuScene.h"
#include "IntroScene.h"
#include "GoodBye.h"
#include "GameScene.h"
#include "SlideScene.h"

using namespace std;
using namespace libconfig;

SceneMachine::SceneMachine() {
    SCENE_STM_START = "INIT";
    SCENE_STM_STOP = "QUIT";
    
    current_scene = 0;
    current_state_name = SCENE_STM_START;
}

SceneMachine::~SceneMachine() {
}

bool SceneMachine::load(SDL_Renderer *renderer, SDL_Window *window) {
    current_scene = 0;
    current_state_name = SCENE_STM_START;
    
    std::cout << "Loading configuration" << std::endl;
    load_config();

    std::cout << "Loading states" << std::endl;
	std::vector<std::string> states = getStateInformation();

	for(unsigned int i=0; i<states.size(); i++)
	{
		map<std::string, std::string> sceneInfo = getSceneInformation(states[i]);
		std::cout << "State: "<<states[i] << std::endl;

		if (sceneInfo["engine"] == GameScene::getEngineName())
			scenes.push_back(new GameScene(renderer, window, sceneInfo) );
        else if (sceneInfo["engine"] == IntroScene::getEngineName())
			scenes.push_back(new IntroScene(renderer, window, sceneInfo) );
        else if (sceneInfo["engine"] == MenuScene::getEngineName())
			scenes.push_back(new MenuScene(renderer, window, sceneInfo) );
        else if (sceneInfo["engine"] == GoodBye::getEngineName())
			scenes.push_back(new GoodBye(renderer, window, sceneInfo) );
        else if (sceneInfo["engine"] == SlideScene::getEngineName())
			scenes.push_back(new SlideScene(renderer, window, sceneInfo) );
		else {
			// INIT and quit are without scen
			if (states[i] == "INIT" || states[i] == "QUIT")
			{
				continue;
			}
			else
			{
				std::cout << "Unknown engine '" << sceneInfo["engine"] <<"'"<< std::endl;
				return false;
			}
		}
	}

	GameEventLogger & logger = GameEventLogger::getObject();
	logger.setScenes(scenes.size());

    this->renderer = renderer;
    
    std::cout << "Loading transition data" << std::endl;
    std::vector<TransitionInfo> trans_data = getTransitionData();
    
    for(unsigned int i=0; i<trans_data.size(); i++)
    {
        join(trans_data[i].from, trans_data[i].to, trans_data[i].when);
    }

    if (current_state_name == SCENE_STM_START) {
        std::string new_state;
        if (findTransition(current_state_name, 0, new_state))
        {
            performTransition(new_state);
        }
		else
		{
			return false;
		}
        scenes[current_scene]->init();
    }

    std::cout << "Loading configuration done" << std::endl;

    return true;
}

std::vector<std::string> SceneMachine::getStateInformation()
{
	std::vector<std::string> result;

	try {
        const Setting & states = cfg.lookup("states");
        int count = states.getLength();
        
        for(int i=0; i<count; i++) {
			std::string val = states[i];
			result.push_back(val);
		}

    }
    catch(const SettingNotFoundException &nfex)      {
        cerr << "State setting not found" << endl;
    }
	return result;
}

void SceneMachine::close() {
    for(unsigned int i=0;i<scenes.size();i++) {
        scenes[i]->close();
        delete scenes[i];
    }

}

void SceneMachine::join(std::string from, std::string to, unsigned int when) {
    TransitionInfo val;
    val.from = from;
    val.to = to;
    val.when = when;
    transitions.push_back(val);
}

void updateElements() {
    // some elements need to be updated as time flows by
    // for example gifs need to be animated

    std::vector<DrawItem*> items = DrawBuilder::GetUpdateItems();
    for(unsigned int i=0; i<items.size(); i++)
    {
        items[i]->update(33);
    }
}

void SceneMachine::write() {

    while(true) {
        SceneInterface * scene = scenes[current_scene];

        SDL_RenderClear(renderer);
        int status = scene->write();
        SDL_RenderPresent(renderer);

        SDL_Delay(33.3);

        if (status == -1)
        {
            updateElements();
        }
        else
        {
			std::cout << "Leaving state: "<<current_state_name<<std::endl;

            std::string new_state;
            if (findTransition(current_state_name, status, new_state))
            {
				std::cout << "New state: "<<new_state<<std::endl;
                performTransition(new_state);
            }
            else
			{
                break;
			}
        }
    }
}

void SceneMachine::performTransition(std::string new_state) {
	std::cout << "Close state: "<<scenes[current_scene]->getName() << std::endl;
    scenes[current_scene]->close();
	std::cout << "Close state: "<<scenes[current_scene]->getName() << " done" << std::endl;

	GameEventLogger & logger = GameEventLogger::getObject();
	logger.sceneStop(current_scene);

    current_state_name = new_state;
    current_scene = getStateNameToId(current_state_name);
	std::cout << "Init state: "<<scenes[current_scene]->getName() << std::endl;
    scenes[current_scene]->init();
	std::cout << "Init state: "<<scenes[current_scene]->getName() << " done" << std::endl;

	logger.sceneStart(current_scene);
}

bool SceneMachine::findTransition(std::string state_name, int status, std::string & result_state)
{
    for(unsigned int i=0; i<transitions.size(); i++) {
        if ( transitions[i].from == state_name && transitions[i].when == status) {
            if ( transitions[i].to == SCENE_STM_STOP) {
                return false;
            }
            else {
                result_state = transitions[i].to;
                return true;
            }
        }
    }
    return false;
}

bool SceneMachine::load_config() {
    try
      {
        cfg.readFile("scenes.cfg");
        return true;
      }
      catch(const FileIOException &fioex)
      {
        std::cerr << "I/O error while reading file." << std::endl;
      }
      catch(const ParseException &pex)
      {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
      }
      return false;
}

bool SceneMachine::copyData(Setting & setting, std::map<std::string, std::string> & aMap, std::string var)
{
    std::string val;

    if (setting.lookupValue(var, val))
        aMap[var] = val;

    return true;
}

map<std::string, std::string> SceneMachine::getSceneInformation(std::string scene) {
    map<std::string, std::string> info;
    
    try {
        const Setting & state_data = cfg.lookup("state_data");
        int count = state_data.getLength();
        std::string name, background, music;
        
        for(int i=0; i<count; i++) {

            copyData(state_data[i], info, "name");

            if (info["name"] != scene)
            {
                continue;
            }

            std::cout << "Found: "<<info["name"] <<std::endl;

            copyData(state_data[i], info, "background");
            copyData(state_data[i], info, "engine");
            copyData(state_data[i], info, "music");
            copyData(state_data[i], info, "letters");
            copyData(state_data[i], info, "limit");
            copyData(state_data[i], info, "letter-r");
            copyData(state_data[i], info, "letter-g");
            copyData(state_data[i], info, "letter-b");
            copyData(state_data[i], info, "fade-in");
            copyData(state_data[i], info, "fade-out");
            copyData(state_data[i], info, "time");
            copyData(state_data[i], info, "slide-text1");
            copyData(state_data[i], info, "slide-text2");
            copyData(state_data[i], info, "slide-text3");
            copyData(state_data[i], info, "cannon-info1");
            copyData(state_data[i], info, "cannon-info2");
            copyData(state_data[i], info, "cannon-info3");
            copyData(state_data[i], info, "cannon-info4");
            copyData(state_data[i], info, "cannon-info5");
            copyData(state_data[i], info, "cannon-info6");
            copyData(state_data[i], info, "cannon-info7");
            copyData(state_data[i], info, "cannon-info8");
            copyData(state_data[i], info, "cannon-info9");
            copyData(state_data[i], info, "cannon-info10");

            std::cout << "Found: "<<info["background"] <<std::endl;
            std::cout << "Found: "<<info["music"] <<std::endl;

            return info;
        }
    }
    catch(const SettingNotFoundException &nfex)      {
        cerr << "State data setting not found: " << nfex.getPath() << endl;
    }

    return info;
}

int SceneMachine::getStateNameToId(std::string name) {
    for(unsigned int i=0; i<scenes.size(); i++)
    {
        if (scenes[i]->getName() == name)
            return i;
    }
    return -1;
}

std::vector<TransitionInfo> SceneMachine::getTransitionData() {

    std::vector<TransitionInfo> result;

    try
    {
        const Setting & trans_data = cfg.lookup("state_transistions");
        int count = trans_data.getLength();
        
        for(int i=0; i<count; i++)
        {
            std::string from, to;
            int when;
            
            trans_data[i].lookupValue("from", from);
            trans_data[i].lookupValue("to", to);
            trans_data[i].lookupValue("when", when);
            
            TransitionInfo info;
            info.when = when;
            info.from = from;
            info.to = to;
            
            result.push_back(info);
        }
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "Transitions setting not found: " << nfex.getPath() << endl;
    }
    
    return result;
}

