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
BattleMapSquare::BattleMapSquare(qreal orientation) :
    m_covered(false)
{
    /* initialize Battle Map square with image of empty Battle Map square rotated according to Battle Map orientation */
    m_battleMapSquarePixmap = QPixmap::fromImage(QImage((EMPTYBATTLEMAPSQUAREIMAGE_SOURCE))).transformed(QTransform().rotate(orientation));
    m_battleMapSquarePixmap = m_battleMapSquarePixmap.scaled(QSize(CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE));

    /* draw Battle Map grid around Battle Map square */
    QPainter *painter = new QPainter(&m_battleMapSquarePixmap);
    painter->setPen(QPen(CONFIG_BATTLEMAPGRID_COLOR, CONFIG_BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
    painter->drawRect(m_battleMapSquarePixmap.rect());
    delete painter;
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
