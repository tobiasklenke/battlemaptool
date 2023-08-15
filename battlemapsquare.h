#ifndef BATTLEMAPSQUARE_H
#define BATTLEMAPSQUARE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsPixmapItem>

#include "defines.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief This class implements the functionality of a Battle Map square.                                                                           *
 ****************************************************************************************************************************************************/
class BattleMapSquare
{

public:

/*!**************************************************************************************************************************************************
 * \brief   This function is the constructor of the class BattleMapSquare.                                                                          *
 *                                                                                                                                                  *
 * \details This function initializes the Battle Map square with the image of an empty Battle Map square.                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    BattleMapSquare();

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class BattleMapSquare.                                                                           *
 *                                                                                                                                                  *
 * \details This function deletes the object pointed to by pBattleMapSquarePixMap.                                                                  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    ~BattleMapSquare();

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable pBattleMapSquarePixMap.                                                          *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable pBattleMapSquarePixMap.                                                          *
 ****************************************************************************************************************************************************/
    QGraphicsPixmapItem *getBattleMapSquarePixMap() const;

/*!**************************************************************************************************************************************************
 * \brief   This function sets the value of the member variable pBattleMapSquarePixMap.                                                             *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   battleMapSquarePixMap         Pixmap of the Battle Map square                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void setBattleMapSquarePixMap(QGraphicsPixmapItem *battleMapSquarePixMap);

private:

/*!**************************************************************************************************************************************************
 * \brief This is the pixmap of the Battle Map square.                                                                                              *
 ****************************************************************************************************************************************************/
    QGraphicsPixmapItem *pBattleMapSquarePixMap;
};

#endif // BATTLEMAPSQUARE_H
