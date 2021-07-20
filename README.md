# Overview

Keyboard-Master is a game in which user has to press keyboard letter to destroy letters that fall from above. It reminds of tetris game.

# Screenshot

![Screenshot](https://github.com/rumca-js/Keyboard-Master/raw/master/data/wallpapers/screenshot1.png)

## Features

 - Scenes are configurable via scenes.cfg
 - Music can be played in the background of game (SDL music)
 - When letters are destroyed a sound is played (SDL sounds)
 - mp3 files are supported
 - Gifs can be used as textures (and they do animate)
 - Limited button support

# Build

Can be built using:

 - G++ make (just enter src directory and make)
 - Eclipse (I have not updated project file in really long time)

src/install_sdl2.sh can be used to install dependencies on Ubuntu based system.

This program is written in SDL2.
Uses the following libraries:
 - SDL2
 - SDL2_image
 - SDL2_ttf
 - SDL2_mixer
 - libgif
 - libconfig++

# Design

## Scenes

The game is divided into several 'scenes'. Each one follows abstract class representing scene interface.

Each scene provides a method for drawing items in it. Each scene can have different background,
music.

Assets are read on program start, and released when scene ends.

Each scene can define it's timers to perform various tasks (letter movement etc., creating new letters)

## Scene State machine

To provide easy access to all scenes resources all scenes are loaded when the program starts.

Order of scenes:
 - intro
 - menu
 - game, etc.

Transitions are configurable, creating loops is possible (from menu, to story, back to menu).

## Time flow

Time flow is managed for each scene separately.

Exceptions are gifs that are animated by engine.

# Engine

To add a new scene:
 - update scenes.cfg directory
    - add a new scene state
    - add a new state_transition
    - provide scene/state information
 - add a class in Scenes directory (use previous classes to identify what has to be written). SceneInterface.h describes the interface.
    - implement functions like getEngineName in source file
    - add the new game scene engine to the state machine (Scenes/SceneMachine.cpp)

# License

GPLv3

Program uses graphics from 
https://www.pexels.com
www.freepik.com
