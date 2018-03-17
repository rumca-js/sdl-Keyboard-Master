/*
 * MainConfiguration.cpp
 *
 *  Created on: 17 mar 2018
 *      Author: hunter
 */

#include "MainConfiguration.h"
#include "config.h"

MainConfiguration::MainConfiguration() {
	_w = WIDTH;
	_h = HEIGHT;
}

MainConfiguration & MainConfiguration::getConfig()
{
	static MainConfiguration config;
	return config;
}

MainConfiguration::~MainConfiguration() {
	// TODO Auto-generated destructor stub
}

unsigned int MainConfiguration::getWidth()
{
	return _w;
}
unsigned int MainConfiguration::getHeight()
{
	return _h;
}

void MainConfiguration::setWidth(unsigned int width)
{
	_w = width;
}
void MainConfiguration::setHeight(unsigned int height)
{
	_h = height;
}
void MainConfiguration::setWindowSize(unsigned int width, unsigned int height)
{
	_w = width;
	_h = height;
}
