/*
 * MainConfiguration.cpp
 *
 *  Created on: 17 mar 2018
 *      Author: hunter
 */

#include <iostream>
#include "MainConfiguration.h"

using namespace std;
using namespace libconfig;

MainConfiguration::MainConfiguration() {

    try
      {
        cfg.readFile("config.cfg");
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

    _w = getConfigInt("WINDOW_WIDTH");
    _h = getConfigInt("WINDOW_HEIGHT");
}

MainConfiguration & MainConfiguration::getConfig()   {
    static MainConfiguration config;
    return config;
}

MainConfiguration::~MainConfiguration() {
    // TODO Auto-generated destructor stub
}

void MainConfiguration::setWinWidth(unsigned int width)    {
    _w = width;
}

void MainConfiguration::setWinHeight(unsigned int height)    {
    _h = height;
}

unsigned int MainConfiguration::getWinWidth()   {
    return _w;
}

unsigned int MainConfiguration::getWinHeight()   {
    return _h;
}

void MainConfiguration::setWindowSize(unsigned int width, unsigned int height)  {
	setWinHeight(height);
	setWinWidth(width);
}

double MainConfiguration::getXpercent(double x) {
    return x*(double)getWinWidth();
}

double MainConfiguration::getYpercent(double y) {
    return y*(double)getWinHeight();
}

unsigned int MainConfiguration::getLetterWidth() {
    return getXpercent(0.1);
}

unsigned int MainConfiguration::getLetterHeight() {
    return getYpercent(0.1);
}

SDL_Rect MainConfiguration::getFullScreenSize() {
    SDL_Rect rect; rect.x = 0; rect.y = 0; rect.w = this->getWinWidth(); rect.h = this->getWinHeight();
    return rect;
}

std::string MainConfiguration::getConfigString(std::string name) {

    try {
        return cfg.lookup(name);
    }
    catch(const SettingNotFoundException &nfex) {
        cerr << "Setting not found:" << name << endl;
    }

    return std::string();
}

int MainConfiguration::getConfigInt(std::string name) {

    try {
        return cfg.lookup(name);
    }
    catch(const SettingNotFoundException &nfex) {
        cerr << "Setting not found:" << name << endl;
    }

    return 0;
}

TTF_Font* MainConfiguration::getDefaultFont() {
    Sans = TTF_OpenFont(getConfigString("FONT_NAME").c_str(), getConfigInt("FONT_SIZE") );
}
