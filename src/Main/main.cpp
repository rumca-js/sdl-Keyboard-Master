
#include <iostream>
#include "MainController.h"

#define PROGRAM_VERSION "1.0.0"
#define PROGRAM_NAME "sdl-Keyboard-Master"

int main(int argc, char* argv[]) {
	std::cout << "Starting "<<PROGRAM_NAME<<" v"<<PROGRAM_VERSION<<std::endl;

    MainController main;

    main.run();
}
