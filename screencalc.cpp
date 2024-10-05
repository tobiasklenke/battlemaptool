/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "screencalc.h"

/****************************************************************************************************************************************************
 * CONSTANTS                                                                                                                                        *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL VARIABLES                                                                                                                                 *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL FUNCTIONS                                                                                                                                 *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * LOCAL FUNCTIONS                                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function calculates the screen width in inches.
 */
qreal calcScreenWidthInInches(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    return qSqrt(qPow(screenDiagonal, EXPONENT_SQUARE) / (1 + qPow(static_cast<qreal>(resolutionWidth) / static_cast<qreal>(resolutionHeight), EXPONENT_SQUARE)));
}

/*!
 * \brief This function calculates the screen height in inches.
 */
qreal calcScreenHeightInInches(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    return qSqrt(qPow(screenDiagonal, EXPONENT_SQUARE) / (1 + qPow(static_cast<qreal>(resolutionHeight) / static_cast<qreal>(resolutionWidth), EXPONENT_SQUARE)));
}

/*!
 * \brief This function calculates the screen diagonal in inches.
 */
qreal calcScreenDiagonalInInches(quint32 sizeWidth, quint32 sizeHeight)
{
    return qSqrt(qPow(sizeWidth, EXPONENT_SQUARE) + qPow(sizeHeight, EXPONENT_SQUARE)) / MILLIMETERS_PER_INCH;
}

/*!
 * \brief This function calculates the number of pixels per inch.
 */
qreal calcNumberPixelsPerInch(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    return qSqrt(qPow(static_cast<qreal>(resolutionWidth), EXPONENT_SQUARE) + qPow(static_cast<qreal>(resolutionHeight), EXPONENT_SQUARE)) / screenDiagonal;
}

/*!
 * \brief This function rounds the value to the number of decimal places.
 */
qreal roundToDecimalPlaces(qreal value, quint32 decimalPlaces)
{
    return qRound(value * qPow(DECIMAL_BASE, decimalPlaces)) / qPow(DECIMAL_BASE, decimalPlaces);
}
