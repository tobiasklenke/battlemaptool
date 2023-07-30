/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "screencalc.h"

/****************************************************************************************************************************************************
 * Constants
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * Global Variables
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * Global Functions
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * Local Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function calculates the screen width in inches.
 */
qreal calcScreenWidthInInches(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    qDebug() << "..." << __func__;

    qreal screenWidthInInches = qSqrt(qPow(screenDiagonal, 2) / (1 + qPow(static_cast<qreal>(resolutionWidth) / static_cast<qreal>(resolutionHeight), 2)));

    return screenWidthInInches;
}

/*!
 * \brief This function calculates the screen width in centimeters.
 */
qreal calcScreenWidthInCentimeters(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    qDebug() << "..." << __func__;

    qreal screenWidthInCentimeters = calcScreenWidthInInches(screenDiagonal, resolutionWidth, resolutionHeight) * INCH_IN_CENTIMETERS;

    return screenWidthInCentimeters;
}

/*!
 * \brief This function calculates the screen height in inches.
 */
qreal calcScreenHeightInInches(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    qDebug() << "..." << __func__;

    qreal screenHeightInInches = qSqrt(qPow(screenDiagonal, 2) / (1 + qPow(static_cast<qreal>(resolutionHeight) / static_cast<qreal>(resolutionWidth), 2)));

    return screenHeightInInches;
}

/*!
 * \brief This function calculates the screen height in centimeters.
 */
qreal calcScreenHeightInCentimeters(qreal screenDiagonal, quint32 resolutionWidth, quint32 resolutionHeight)
{
    qDebug() << "..." << __func__;

    qreal screenHeightInCentimeters = calcScreenHeightInInches(screenDiagonal, resolutionWidth, resolutionHeight) * INCH_IN_CENTIMETERS;

    return screenHeightInCentimeters;
}
