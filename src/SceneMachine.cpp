
#include <iostream>

#include "SceneMachine.h"

#include "Scenes/MenuScene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GoodBye.h"

#include "Scenes/HeavenScene.h"
#include "Scenes/CosmosScene.h"

using namespace std;
using namespace libconfig;

SceneMachine::SceneMachine() {
    SCENE_STM_START = "INIT";
    SCENE_STM_STOP = "QUIT";
    
    current = 0;
    current_state_name = SCENE_STM_START;
}

SceneMachine::~SceneMachine() {
}

bool SceneMachine::load(SDL_Renderer *renderer, SDL_Window *window) {
    current = 0;
    current_state_name = SCENE_STM_START;
    
    load_config();
    
    scenes.push_back(new IntroScene(renderer, window, getSceneInformation("INTRO") ) );
    scenes.push_back(new MenuScene(renderer, window, getSceneInformation("MENU") ) );
    scenes.push_back(new GoodBye(renderer, window, getSceneInformation("GOODBYE")) );
    scenes.push_back(new GameScene(renderer, window, getSceneInformation("HEAVEN")) );
    scenes.push_back(new CosmosScene(renderer, window, getSceneInformation("COSMOS")) );
    
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
    	scenes[current]->init();
    }

    return true;
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

void SceneMachine::write() {

    while(true) {
    	SceneInterface * scene = scenes[current];
    	int status = scene->write();

    	std::string new_state;
    	if (findTransition(current_state_name, status, new_state))
    	{
    		performTransition(new_state);
    	}
    	else
    		break;
    }
}

void SceneMachine::performTransition(std::string name) {
    current_state_name = name;
    current = getStateNameToId(current_state_name);
    scenes[current]->init();
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

map<std::string, std::string> SceneMachine::getSceneInformation(std::string scene) {
    map<std::string, std::string> info;
    
    try {
    	const Setting & state_data = cfg.lookup("state_data");
    	int count = state_data.getLength();
    	std::string name, background, music;
    	
    	for(int i=0; i<count; i++) {


    		state_data[i].lookupValue("name", name);
    		if (name != scene)
    			continue;
    		state_data[i].lookupValue("background", background);
    		state_data[i].lookupValue("music", music);

    		info["name"] = name;
    		info["backkground"] = background;
    		info["music"] = music;
    		
    		return info;
    	}
    }
    catch(const SettingNotFoundException &nfex)  	{
    	cerr << "Setting not found:" << endl;
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
    	cerr << "Setting not found:" << endl;
    }
    
    return result;
}

