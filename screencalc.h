#ifndef SCREENCALC_H
#define SCREENCALC_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QtMath>

/****************************************************************************************************************************************************
 * DEFINES                                                                                                                                          *
 ****************************************************************************************************************************************************/

/*!
 * \brief This is the conversion factor between inches and centimeters.
 */
#define INCH_IN_CENTIMETERS                                2.54

/****************************************************************************************************************************************************
 * MACROS                                                                                                                                           *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL TYPE DEFINITIONS                                                                                                                          *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL DECLARATIONS                                                                                                                              *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL FUNCTION DECLARATIONS                                                                                                                     *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * LOCAL FUNCTION DECLARATIONS                                                                                                                      *
 ****************************************************************************************************************************************************/

/*! *************************************************************************************************************************************************
 * \brief   This function calculates the screen width in inches.                                                                                    *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   screenDiagonal                Screen diagonal in inches                                                                                 *
 * \param   resolutionWidth               Screen width in pixels                                                                                    *
 * \param   resolutionHeight              Screen height in pixels                                                                                   *
 *                                                                                                                                                  *
 * \return  This function returns the calculated screen width in inches.                                                                            *
 ****************************************************************************************************************************************************/
qreal calcScreenWidthInInches(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight);

/*! *************************************************************************************************************************************************
 * \brief   This function calculates the screen width in centimeters.                                                                               *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   screenDiagonal                Screen diagonal in inches                                                                                 *
 * \param   resolutionWidth               Screen width in pixels                                                                                    *
 * \param   resolutionHeight              Screen height in pixels                                                                                   *
 *                                                                                                                                                  *
 * \return  This function returns the calculated screen width in centimeters.                                                                       *
 ****************************************************************************************************************************************************/
qreal calcScreenWidthInCentimeters(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight);

/*! *************************************************************************************************************************************************
 * \brief   This function calculates the screen height in inches.                                                                                   *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   screenDiagonal                Screen diagonal in inches                                                                                 *
 * \param   resolutionWidth               Screen width in pixels                                                                                    *
 * \param   resolutionHeight              Screen height in pixels                                                                                   *
 *                                                                                                                                                  *
 * \return  This function returns the calculated screen height in inches.                                                                           *
 ****************************************************************************************************************************************************/
qreal calcScreenHeightInInches(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight);

/*! *************************************************************************************************************************************************
 * \brief   This function calculates the screen height in centimeters.                                                                              *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   screenDiagonal                Screen diagonal in inches                                                                                 *
 * \param   resolutionWidth               Screen width in pixels                                                                                    *
 * \param   resolutionHeight              Screen height in pixels                                                                                   *
 *                                                                                                                                                  *
 * \return  This function returns the calculated screen height in centimeters.                                                                      *
 ****************************************************************************************************************************************************/
qreal calcScreenHeightInCentimeters(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight);

#endif // SCREENCALC_H
