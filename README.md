# Overview
Keyboard-Master is a game in which user has to press keyboard letter to destroy letters that fall from above. It reminds of tetris game.

# Design
The game is divided into several 'scenes'. Each scene follows abstract class SceneInterface.h interface. To provide easy access to all scenes resources all scenes are loaded when the program starts.
We transition from scene to scene until the end of the game. We start with intro scene, then through menu we can reach the game. This mechanism is implemented in the SceneMachine.h file that provides scene state machine implementation.
Each particular section should be as closed entity as possible. There might be some exceptions (like music from the intro could encompass the menu also).

# Implementation
This program is written in SDL2, on Linux Mint. 
Uses the following SDL2 libraries:
 - SDL2
 - SDL2_image
 - SDL2_ttf
 - SDL2_mixer

Developped using eclipse.

# Screenshot
[![Screenshot](https://github.com/rumca-js/Keyboard-Master/raw/master/data/wallpapers/screenshot1.png)]

# License
GPLv3

Program uses graphics from 
https://www.pexels.com
www.freepik.com
