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

unsigned int MainConfiguration::getWidth()   {
    return _w;
}
unsigned int MainConfiguration::getHeight()   {
    return _h;
}
unsigned int MainConfiguration::getXpercent(double x) {
    return x*(double)getWidth();
}
unsigned int MainConfiguration::getYpercent(double y) {
    return y*(double)getHeight();
}
unsigned int MainConfiguration::getLetterWidth() {
    return getXpercent(0.1);
}
unsigned int MainConfiguration::getLetterHeight() {
    return getYpercent(0.1);
}
void MainConfiguration::setWidth(unsigned int width)    {
    _w = width;
}
void MainConfiguration::setHeight(unsigned int height)    {
    _h = height;
}
void MainConfiguration::setWindowSize(unsigned int width, unsigned int height)  {
    _w = width;
    _h = height;
}
SDL_Rect MainConfiguration::getFullScreenSize()
{
    SDL_Rect rect; rect.x = 0; rect.y = 0; rect.w = this->getWidth(); rect.h = this->getHeight();
    return rect;
}

std::string MainConfiguration::getConfigString(std::string name)
{
    try
    {
        return cfg.lookup(name);
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "Setting not found:" << name << endl;
    }

    return std::string();
}

int MainConfiguration::getConfigInt(std::string name)
{
    try
    {
        return cfg.lookup(name);
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "Setting not found:" << name << endl;
    }

    return 0;
}
