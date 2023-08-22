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
    return qSqrt(qPow(screenDiagonal, 2) / (1 + qPow(static_cast<qreal>(resolutionWidth) / static_cast<qreal>(resolutionHeight), 2)));
}

/*!
 * \brief This function calculates the screen width in centimeters.
 */
qreal calcScreenWidthInCentimeters(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    return calcScreenWidthInInches(screenDiagonal, resolutionWidth, resolutionHeight) * INCH_IN_CENTIMETERS;
}

/*!
 * \brief This function calculates the screen height in inches.
 */
qreal calcScreenHeightInInches(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    return qSqrt(qPow(screenDiagonal, 2) / (1 + qPow(static_cast<qreal>(resolutionHeight) / static_cast<qreal>(resolutionWidth), 2)));
}

/*!
 * \brief This function calculates the screen height in centimeters.
 */
qreal calcScreenHeightInCentimeters(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    return calcScreenHeightInInches(screenDiagonal, resolutionWidth, resolutionHeight) * INCH_IN_CENTIMETERS;
}
