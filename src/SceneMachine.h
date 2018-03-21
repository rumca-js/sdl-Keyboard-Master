/*
 * SceneMachine.h
 *
 *  Created on: 21 mar 2018
 *      Author: hunter
 */

#ifndef SCENEMACHINE_H_
#define SCENEMACHINE_H_

#include <vector>
#include "SceneInterface.h"

typedef struct _TrasnitionInfo
{
	unsigned int from;
	unsigned int to;
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
	int current;
	/*!
	 * \brief START indication.
	 */
	static const int SCENE_STM_START=-1;
	/*!
	 * \brief STOP indication.
	 */
	static const int SCENE_STM_STOP=-2;

public:
	SceneMachine();

	/*!
	 * \brief joins <where> scene indication with <to> scene indication, when
	 * <when> is returned by write SceneInterface.write function.
	 */
	void join(unsigned int, unsigned int, unsigned int);
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
};

#endif /* SCENEMACHINE_H_ */
