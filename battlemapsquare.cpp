/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapsquare.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function is the constructor of the class BattleMapSquare.                                                                          *
 *                                                                                                                                                  *
 * \details This function initializes the Battle Map square with the image of an empty Battle Map square.                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
BattleMapSquare::BattleMapSquare() :
    pBattleMapSquarePixMap(new QGraphicsPixmapItem())
{
    /* initialize Battle Map square with image of empty Battle Map square */
    pBattleMapSquarePixMap->setPixmap(QPixmap::fromImage(QImage((EMPTY_BATTLEMAPSQUARE_SOURCE))));
    pBattleMapSquarePixMap->setPixmap(pBattleMapSquarePixMap->pixmap().scaled(QSize(BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE)));
}

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class BattleMapSquare.                                                                           *
 *                                                                                                                                                  *
 * \details This function deletes the object pointed to by pBattleMapSquarePixMap.                                                                  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
BattleMapSquare::~BattleMapSquare()
{
    delete pBattleMapSquarePixMap;
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable pBattleMapSquarePixMap.                                                          *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable pBattleMapSquarePixMap.                                                          *
 ****************************************************************************************************************************************************/
QGraphicsPixmapItem *BattleMapSquare::getBattleMapSquarePixMap() const
{
    return pBattleMapSquarePixMap;
}

/*!**************************************************************************************************************************************************
 * \brief   This function sets the value of the member variable pBattleMapSquarePixMap.                                                             *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   battleMapSquarePixMap         Pixmap of the Battle Map square                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
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
