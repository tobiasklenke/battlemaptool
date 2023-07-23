/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "battlemapsquare.h"

/****************************************************************************************************************************************************
 * Definition of Public Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapSquare.
 */
BattleMapSquare::BattleMapSquare() :
    pBattleMapSquarePixMap(NULL)
{
    //qDebug() << "..." << __func__;
}

/*!
 * \brief This function is the destructor of the class BattleMapSquare.
 */
BattleMapSquare::~BattleMapSquare()
{
    qDebug() << "..." << __func__;
    delete pBattleMapSquarePixMap;
}

/*!
 * \brief This function returns the value of the member variable pBattleMapSquarePixMap.
 */
QGraphicsPixmapItem *BattleMapSquare::getBattleMapSquarePixMap() const
{
    //qDebug() << "..." << __func__;
    return pBattleMapSquarePixMap;
}

/*!
 * \brief This function sets the value of the member variable pBattleMapSquarePixMap.
 */
void BattleMapSquare::setBattleMapSquarePixMap(QGraphicsPixmapItem *newBattleMapSquarePixMap)
{
    //qDebug() << "..." << __func__;
    pBattleMapSquarePixMap = newBattleMapSquarePixMap;
}

/****************************************************************************************************************************************************
 * Definition of Protected Functions
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * Definition of Private Slot Functions
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * Definition of Private Functions
 ****************************************************************************************************************************************************/

/* - */
