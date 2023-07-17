#ifndef BATTLEMAPSQUARE_H
#define BATTLEMAPSQUARE_H

/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include <QGraphicsPixmapItem>

/****************************************************************************************************************************************************
 * Class Declaration
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality of a Battle Map square.
 */
class BattleMapSquare
{

public:

    /*!
     * \brief This function is the constructor of the class BattleMapSquare.
     */
    BattleMapSquare();

    /*!
     * \brief This function is the destructor of the class BattleMapSquare.
     */
    ~BattleMapSquare();

    /*!
     * \brief This function returns the value of the member variable pBattleMapSquarePixMap.
     */
    QGraphicsPixmapItem *getBattleMapSquarePixMap() const;

    /*!
     * \brief This function sets the value of the member variable pBattleMapSquarePixMap.
     */
    void setBattleMapSquarePixMap(QGraphicsPixmapItem *newBattleMapSquarePixMap);

private:

    /*!
     * \brief This is the pixmap of the Battle Map square.
     */
    QGraphicsPixmapItem *pBattleMapSquarePixMap;
};

#endif // BATTLEMAPSQUARE_H
