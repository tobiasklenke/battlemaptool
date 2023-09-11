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
BattleMapSquare::BattleMapSquare():
    pBattleMapSquarePixmap(new QGraphicsPixmapItem())
{
    /* initialize Battle Map square with image of empty Battle Map square */
    pBattleMapSquarePixmap->setPixmap(QPixmap::fromImage(QImage((EMPTYBATTLEMAPSQUAREIMAGE_SOURCE))));
    pBattleMapSquarePixmap->setPixmap(pBattleMapSquarePixmap->pixmap().scaled(QSize(CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE)));
}

/*!
 * \brief This function is the destructor of the class BattleMapSquare.
 */
BattleMapSquare::~BattleMapSquare()
{
    delete pBattleMapSquarePixmap;
}

/*!
 * \brief This function returns the member variable pBattleMapSquarePixmap.
 */
QGraphicsPixmapItem * BattleMapSquare::getBattleMapSquare() const
{
    return pBattleMapSquarePixmap;
}

/*!
 * \brief This function returns the pixmap of the member variable pBattleMapSquarePixmap.
 */
QPixmap BattleMapSquare::getBattleMapSquarePixmap() const
{
    return pBattleMapSquarePixmap->pixmap();
}

/*!
 * \brief This function sets the pixmap of the member variable pBattleMapSquarePixmap.
 */
void BattleMapSquare::setBattleMapSquarePixmap(QPixmap battleMapSquarePixMap)
{
    pBattleMapSquarePixmap->setPixmap(battleMapSquarePixMap);
}

/*!
 * \brief This function scales the pixmap of the member variable pBattleMapSquarePixmap.
 */
void BattleMapSquare::scaleBattleMapSquarePixmap(quint32 newSize)
{
    pBattleMapSquarePixmap->setPixmap(pBattleMapSquarePixmap->pixmap().scaled(QSize(newSize, newSize)));
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
