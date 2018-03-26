/*
 * MainConfiguration.h
 *
 *  Created on: 17 mar 2018
 *      Author: hunter
 *
 *  Configuration singleton
 */

#ifndef MAINCONFIGURATION_H_
#define MAINCONFIGURATION_H_

#include <SDL2/SDL.h>

class MainConfiguration {
	/*!
	 * \brief width.
	 */
	unsigned int _w;
	/*!
	 * \brief height.
	 */
	unsigned int _h;
	/*!
	 * \brief The high score.
	 */
	unsigned int _high_score;
	/*!
	 * \brief Constructor.
	 */
	MainConfiguration();

public:
	/*!
	 * \brief Destructor.
	 */
	virtual ~MainConfiguration();
    /*!
     \brief Returns desired Width.
    */
	unsigned int getWidth();
    /*!
     \brief Returns desired Width.
    */
	unsigned int getHeight();
	/*!
	 * \brief For the specified x width specified in percent 0-1 return window width.
	 */
	unsigned int getXpercent(double x);
	/*!
	 * \brief For the specified y width specified in percent 0-1 return window height.
	 */
	unsigned int getYpercent(double y);
    /*!
     \brief Sets the desired window width.
    */
	void setWidth(unsigned int);
    /*!
     \brief Sets the desired window height.
    */
	void setHeight(unsigned int);
    /*!
     \brief Sets the desired window dimentions.
    */
	void setWindowSize(unsigned int, unsigned int);
	/*!
	 * \brief Sets high score - dynamic current value in RAM.
	 */
	void setHighScore(unsigned int);
	/*!
	 * \brief Returns high score value.
	 */
	unsigned int getHighScore();
    /*!
     \brief Returns configuration singleton.
    */
	static MainConfiguration & getConfig();
	/*!
	 * \brief Returns window size in Rect structure.
	 */
	SDL_Rect getFullScreenSize();
};

#endif /* MAINCONFIGURATION_H_ */
