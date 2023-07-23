#ifndef BATTLEMAP_H
#define BATTLEMAP_H

/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "battlemapsquare.h"

/****************************************************************************************************************************************************
 * Class Declaration
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality of a Battle Map.
 */
class BattleMap
{

public:

    /*!
     * \brief This function is the constructor of the class BattleMap.
     */
    BattleMap();

    /*!
     * \brief This function is the destructor of the class BattleMap.
     */
    ~BattleMap();

    /*!
     * \brief This function returns the value of the member variable m_numberRows.
     */
    quint32 getNumberRows() const;

    /*!
     * \brief This function sets the value of the member variable m_numberRows.
     */
    void setNumberRows(quint32 newNumberRows);

    /*!
     * \brief This function returns the value of the member variable m_numberColumns.
     */
    quint32 getNumberColumns() const;

    /*!
     * \brief This function sets the value of the member variable m_numberColumns.
     */
    void setNumberColumns(quint32 newNumberColumns);

    /*!
     * \brief This function returns the value of the indexed member variable m_battleMapSquares.
     */
    QGraphicsPixmapItem *getIndexedBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx) const;

    /*!
     * \brief This function sets the pixmap of the indexed member variable m_battleMapSquares.
     */
    void setIndexedBattleMapSquarePixmap(quint32 rowIdx, QGraphicsPixmapItem *newBattleMapSquarePixmap);

private:

    /*!
     * \brief This is the number of rows of the Battle Map.
     */
    quint32 m_numberRows;

    /*!
     * \brief This is the number of columns of the Battle Map.
     */
    quint32 m_numberColumns;

    /*!
     * \brief This is the variable containing the Battle Map squares building the Battle Map.
     */
    QList<QList<BattleMapSquare*>> m_battleMapSquares;
};

#endif // BATTLEMAP_H
