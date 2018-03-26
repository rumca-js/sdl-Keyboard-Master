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

	_high_score = 0;
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
unsigned int MainConfiguration::getXpercent(double x)
{
	return x*(double)getWidth();
}
unsigned int MainConfiguration::getYpercent(double y)
{
	return y*(double)getHeight();
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
void MainConfiguration::setHighScore(unsigned int high_score)
{
	_high_score = high_score;
}
unsigned int MainConfiguration::getHighScore()
{
	return _high_score;
}
SDL_Rect MainConfiguration::getFullScreenSize()
{
	SDL_Rect rect; rect.x = 0; rect.y = 0; rect.w = this->getWidth(); rect.h = this->getHeight();
	return rect;
}
