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
 * \brief This function calculates the number of pixels per inch.
 */
qreal calcNumberPixelsPerInch(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    return qSqrt(qPow(static_cast<qreal>(resolutionWidth), EXPONENT_SQUARE) + qPow(static_cast<qreal>(resolutionHeight), EXPONENT_SQUARE)) / screenDiagonal;
}
