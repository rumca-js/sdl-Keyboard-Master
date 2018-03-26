/*
 * SceneMachine.cpp
 *
 *  Created on: 21 mar 2018
 *      Author: hunter
 */

#include <iostream>

#include "SceneMachine.h"

#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GoodBye.h"


SceneMachine::SceneMachine() {
	current = SCENE_STM_START;
}

void SceneMachine::join(unsigned int from, unsigned int to, unsigned int when)  {
	TransitionInfo val;
	val.from = from;
	val.to = to;
	val.when = when;
	transitions.push_back(val);
}

SceneMachine::~SceneMachine() {
}

void SceneMachine::write()  {

    while(true)   {

		SceneInterface * scene = scenes[current];
		int status = scene->write();

		for(unsigned int i=0; i<transitions.size(); i++)  {
			if ( (int)transitions[i].from == current && transitions[i].when == status)  {
				if ( (int)transitions[i].to == SCENE_STM_STOP)  {
					return;
				}
				else  {
					current = transitions[i].to;
					break;
				}
			}
		}
	}
}

bool SceneMachine::load(SDL_Renderer *renderer, SDL_Window *window)
{
	current = SCENE_STM_START;

	scenes.push_back(new IntroScene(renderer, window) );
	scenes.push_back(new MenuScene(renderer, window) );
	scenes.push_back(new GameScene(renderer, window) );
	scenes.push_back(new GoodBye(renderer, window) );

	join(SCENE_STM_START, 0, SceneInterface::SCENE_FINISHED);
	join(0, 1, SceneInterface::SCENE_FINISHED);
	join(1, 2, SceneInterface::SCENE_FINISHED);
	join(1, 3, SceneInterface::SCENE_EXIT);
	join(2, 1, SceneInterface::SCENE_FINISHED);
	join(2, 1, SceneInterface::SCENE_EXIT);

	join(3, SCENE_STM_STOP, SceneInterface::SCENE_EXIT);
	join(3, SCENE_STM_STOP, SceneInterface::SCENE_FINISHED);

	if (current == SCENE_STM_START)
	{
		current = transitions[0].to;
	}

	for(unsigned int i=0;i<scenes.size();i++)   {
		scenes[i]->init();
	}

	return true;
}

void SceneMachine::close()  {
	for(unsigned int i=0;i<scenes.size();i++)   {
		scenes[i]->close();
		delete scenes[i];
	}

}
