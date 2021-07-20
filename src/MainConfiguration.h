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
#include <libconfig.h++>

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
     * Configuration file
     */
    libconfig::Config cfg;

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
     \brief Returns desired Width in pixels
    */
    unsigned int getWinWidth();
    /*!
     \brief Returns desired Width in pixels
    */
    unsigned int getWinHeight();
    /*!
     * \brief For the specified x width specified in percent 0-1 return window width.
     */
    double getXpercent(double x);
    /*!
     * \brief For the specified y width specified in percent 0-1 return window height.
     */
    double getYpercent(double y);
    /*!
     \brief Sets the desired window width in pixels
    */
    void setWinWidth(unsigned int);
    /*!
     \brief Sets the desired window height in pixels
    */
    void setWinHeight(unsigned int);
    /*!
     \brief Sets the desired window dimentions.
    */
    void setWindowSize(unsigned int, unsigned int);
    /*!
     \brief Returns configuration singleton.
    */
    static MainConfiguration & getConfig();
    /*!
     * \brief Returns window size in Rect structure.
     */
    SDL_Rect getFullScreenSize();
    /*!
     * \return config string value (string)
     */
    std::string getConfigString(std::string name);
    /*!
     * \return config string value (int)
     */
    int getConfigInt(std::string name);
    /*!
     * \return configured letter width
     */
    unsigned int getLetterWidth();
    /*!
     * \return configured letter height
     */
    unsigned int getLetterHeight();
    /*!
     * returns default font
     */
    TTF_Font* getDefaultFont();
};

#endif /* MAINCONFIGURATION_H_ */
