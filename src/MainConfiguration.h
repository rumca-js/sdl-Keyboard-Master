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


	unsigned int getWidth();
	unsigned int getHeight();

	void setWidth(unsigned int);
	void setHeight(unsigned int);

	void setWindowSize(unsigned int, unsigned int);

	static MainConfiguration & getConfig();

	virtual ~MainConfiguration();
};

#endif /* MAINCONFIGURATION_H_ */
