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
     * \brief The current scene number (index in scenes)
     */
    unsigned int current;
    /*!
     * \brief current scene/state name
     */
    std::string current_state_name;
    /*!
     * \brief START indication.
     */
    std::string SCENE_STM_START;
    /*!
     * \brief STOP indication.
     */
    std::string SCENE_STM_STOP;
    /*!
     * \brief scene configuration file
     */
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
    /*!
     * finds transition from state_name on status result value
     *
     * \param result_state the new scene/state name to which we should transition
     *
     * @return true if a transition can be found, false otherwise
     */
    bool findTransition(std::string state_name, int status, std::string & result_state);
    /*!
     * Loads scene configuration
     */
    bool load_config();
    /*!
     * Retrieves scene information (data)
     */
    std::map<std::string, std::string> getSceneInformation(std::string scene);
    /*!
     * converts scene name to scenes table id
     */
    int getStateNameToId(std::string name);
    /*!
     * Perorms transition to new state "name"
     */
    void performTransition(std::string name);
    /*!
     * returns transition info table
     */
    std::vector<TransitionInfo> getTransitionData();
};

#endif /* SCENEMACHINE_H_ */
