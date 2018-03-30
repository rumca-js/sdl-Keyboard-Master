/*
 * SceneMachine.cpp
 *
 *  Created on: 21 mar 2018
 *      Author: hunter
 */

#include <iostream>

#include "SceneMachine.h"

#include "Scenes/MenuScene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GoodBye.h"

#include "Scenes/HeavenScene.h"
#include "Scenes/CosmosScene.h"


SceneMachine::SceneMachine() {
	current = SCENE_STM_START;
}

SceneMachine::~SceneMachine() {
}

bool SceneMachine::load(SDL_Renderer *renderer, SDL_Window *window) {
	current = SCENE_STM_START;

	scenes.push_back(new IntroScene(renderer, window) );
	scenes.push_back(new MenuScene(renderer, window) );
	scenes.push_back(new GoodBye(renderer, window) );
	scenes.push_back(new GameScene(renderer, window) );
	scenes.push_back(new CosmosScene(renderer, window) );

	const unsigned int SCENE_INTRO = 0;
	const unsigned int SCENE_MENU = 1;
	const unsigned int SCENE_GOODBYE = 2;
	const unsigned int SCENE_HEAVEN = 3;
	const unsigned int SCENE_COSMOS = 4;

	/*
	join(SCENE_STM_START, 1, SceneInterface::SCENE_FINISHED);

	join(0, 1, SceneInterface::SCENE_FINISHED);
	join(1, SCENE_STM_STOP, SceneInterface::SCENE_FINISHED);
	join(1, SCENE_STM_STOP, SceneInterface::SCENE_EXIT);
	*/


	join(SCENE_STM_START, SCENE_INTRO, SceneInterface::SCENE_FINISHED);

	join(SCENE_INTRO, SCENE_MENU, SceneInterface::SCENE_FINISHED);
	join(SCENE_MENU, SCENE_HEAVEN, SceneInterface::SCENE_FINISHED);

	join(SCENE_HEAVEN, SCENE_COSMOS, SceneInterface::SCENE_FINISHED);
	join(SCENE_COSMOS, SCENE_MENU, SceneInterface::SCENE_FINISHED);

	join(SCENE_HEAVEN, SCENE_MENU, SceneInterface::SCENE_EXIT);
	join(SCENE_COSMOS, SCENE_MENU, SceneInterface::SCENE_EXIT);

	join(SCENE_MENU, SCENE_GOODBYE, SceneInterface::SCENE_EXIT);

	join(SCENE_GOODBYE, SCENE_STM_STOP, SceneInterface::SCENE_EXIT);
	join(SCENE_GOODBYE, SCENE_STM_STOP, SceneInterface::SCENE_FINISHED);

	if (current == SCENE_STM_START) {
		current = transitions[0].to;
	}

	for(unsigned int i=0;i<scenes.size();i++) {
		scenes[i]->init();
	}

	return true;
}

void SceneMachine::close() {
	for(unsigned int i=0;i<scenes.size();i++) {
		scenes[i]->close();
		delete scenes[i];
	}

}

void SceneMachine::join(unsigned int from, unsigned int to, unsigned int when) {
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

		for(unsigned int i=0; i<transitions.size(); i++) {
			if ( (int)transitions[i].from == current && transitions[i].when == status) {
				if ( (int)transitions[i].to == SCENE_STM_STOP) {
					return;
				}
				else {
					current = transitions[i].to;
					break;
				}
			}
		}
	}
}


