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
    pBattleMapSquarePixMap(new QGraphicsPixmapItem())
{
    /* initialize Battle Map square with image of empty Battle Map square */
    pBattleMapSquarePixMap->setPixmap(QPixmap::fromImage(QImage((EMPTYBATTLEMAPSQUAREIMAGE_SOURCE))));
    pBattleMapSquarePixMap->setPixmap(pBattleMapSquarePixMap->pixmap().scaled(QSize(BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE)));
}

/*!
 * \brief This function is the destructor of the class BattleMapSquare.
 */
BattleMapSquare::~BattleMapSquare()
{
    delete pBattleMapSquarePixMap;
}

/*!
 * \brief This function returns the value of the member variable pBattleMapSquarePixMap.
 */
QGraphicsPixmapItem *BattleMapSquare::getBattleMapSquarePixMap() const
{
    return pBattleMapSquarePixMap;
}

/*!
 * \brief This function sets the value of the member variable pBattleMapSquarePixMap.
 */
void BattleMapSquare::setBattleMapSquarePixMap(QGraphicsPixmapItem *battleMapSquarePixMap)
{
    pBattleMapSquarePixMap = battleMapSquarePixMap;
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
