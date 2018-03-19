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

class MainConfiguration {
	unsigned int _w;
	unsigned int _h;
	MainConfiguration();

public:

    /*!
     \brief Returns desired Width.
    */
	unsigned int getWidth();
    /*!
     \brief Returns desired Width.
    */
	unsigned int getHeight();
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
     \brief Returns configuration singleton.
    */
	static MainConfiguration & getConfig();

	virtual ~MainConfiguration();
};

#endif /* MAINCONFIGURATION_H_ */
