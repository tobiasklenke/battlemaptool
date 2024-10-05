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
 * \brief This is the value representing the square exponent.
 */
#define EXPONENT_SQUARE                                    2

/*!
 * \brief This is the value representing the number of the decimal base.
 */
#define DECIMAL_BASE                                       10.0

/*!
 * \brief This is the value representing the number of millimeters per inch.
 */
#define MILLIMETERS_PER_INCH                               25.4

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
 * \brief   This function calculates the screen diagonal in inches.                                                                                 *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   sizeWidth                     Screen width in millimeters                                                                               *
 * \param   sizeHeight                    Screen height in millimeters                                                                              *
 *                                                                                                                                                  *
 * \return  This function returns the calculated screen height in inches.                                                                           *
 ****************************************************************************************************************************************************/
qreal calcScreenDiagonalInInches(quint32 sizeWidth, quint32 sizeHeight);

/*! *************************************************************************************************************************************************
 * \brief   This function calculates the number of pixels per inch.                                                                                 *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   screenDiagonal                Screen diagonal in inches                                                                                 *
 * \param   resolutionWidth               Screen width in pixels                                                                                    *
 * \param   resolutionHeight              Screen height in pixels                                                                                   *
 *                                                                                                                                                  *
 * \return  This function returns the calculated number of pixels per inch.                                                                         *
 ****************************************************************************************************************************************************/
qreal calcNumberPixelsPerInch(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight);

/*! *************************************************************************************************************************************************
 * \brief   This function rounds the value to the number of decimal places.                                                                         *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   value                         Value to be rounded                                                                                       *
 * \param   decimalPlaces                 Number of decimal places                                                                                  *
 *                                                                                                                                                  *
 * \return  This function returns the rounded value.                                                                                                *
 ****************************************************************************************************************************************************/
qreal roundToDecimalPlaces(qreal value, quint32 decimalPlaces);

#endif // SCREENCALC_H
