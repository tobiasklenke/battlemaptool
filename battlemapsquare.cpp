/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapsquare.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapSquare.
 */
BattleMapSquare::BattleMapSquare() :
    m_covered(false)
{
    /* initialize Battle Map square with image of empty Battle Map square */
    m_battleMapSquarePixmap = QPixmap::fromImage(QImage((EMPTYBATTLEMAPSQUAREIMAGE_SOURCE)));
    m_battleMapSquarePixmap = m_battleMapSquarePixmap.scaled(QSize(CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE));
}

/*!
 * \brief This function is the destructor of the class BattleMapSquare.
 */
BattleMapSquare::~BattleMapSquare()
{
}

/*!
 * \brief This function returns the pixmap of the member variable m_battleMapSquarePixmap.
 */
QPixmap BattleMapSquare::getBattleMapSquarePixmap() const
{
    return m_battleMapSquarePixmap;
}

/*!
 * \brief This function sets the pixmap of the member variable pBattleMapSquarePixmap.
 */
void BattleMapSquare::setBattleMapSquarePixmap(QPixmap battleMapSquarePixMap)
{
    m_battleMapSquarePixmap = battleMapSquarePixMap;
}

/*!
 * \brief This function scales the pixmap of the member variable pBattleMapSquarePixmap.
 */
void BattleMapSquare::scaleBattleMapSquarePixmap(quint32 newSize)
{
    m_battleMapSquarePixmap = m_battleMapSquarePixmap.scaled(QSize(newSize, newSize));
}

/*!
 * \brief This function returns the value of the member variable m_covered.
 */
bool BattleMapSquare::getCovered() const
{
    return m_covered;
}

/*!
 * \brief This function sets the value of the member variable m_covered.
 */
void BattleMapSquare::setCovered(bool covered)
{
    m_covered = covered;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
