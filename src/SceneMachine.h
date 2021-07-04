/*
 * SceneMachine.h
 *
 *  Created on: 21 mar 2018
 *      Author: hunter
 */

#ifndef SCENEMACHINE_H_
#define SCENEMACHINE_H_

#include <vector>
#include <map>
#include "SceneInterface.h"
#include <libconfig.h++>

typedef struct _TrasnitionInfo
{
	std::string from;
	std::string to;
	int when;
} TransitionInfo;

class SceneMachine {
	/*!
	 * \brief Scenes in the machine state.
	 */
	std::vector<SceneInterface*> scenes;
	/*!
	 * \brief
	 */
	std::vector<TransitionInfo> transitions;
	/*!
	 * \brief The state machine current state (scene indication).
	 */
	unsigned int current;
	std::string current_state_name;
	/*!
	 * \brief START indication.
	 */
	std::string SCENE_STM_START;
	/*!
	 * \brief STOP indication.
	 */
	std::string SCENE_STM_STOP;
        libconfig::Config cfg;

public:
	SceneMachine();

	/*!
	 * \brief joins <where> scene indication with <to> scene indication, when
	 * <when> is returned by write SceneInterface.write function.
	 */
	void join(std::string, std::string, unsigned int);
	/*!
	 * \brief Loads scenes.
	 */
	bool load(SDL_Renderer *renderer, SDL_Window *window);
	/*!
	 * \brief Writes the scenes.
	 */
	void write();
	/*!
	 * \brief Disposes the scenes.
	 */
	void close();
	/*!
	 * Closes the scene state machine.
	 */
	virtual ~SceneMachine();
	bool findTransition(std::string state_name, int status, std::string & result_state);
	bool load_config();
	std::map<std::string, std::string> getSceneInformation(std::string scene);
	int getStateNameToId(std::string name);
	void performTransition(std::string name);
	std::vector<TransitionInfo> getTransitionData();
};

#endif /* SCENEMACHINE_H_ */
