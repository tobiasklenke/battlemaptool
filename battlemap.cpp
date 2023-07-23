/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "battlemap.h"

/****************************************************************************************************************************************************
 * Definition of Public Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMap.
 */
BattleMap::BattleMap() :
    m_numberRows(0U),
    m_numberColumns(0U),
    m_battleMapSquares(QList<QList<BattleMapSquare*>>())
{
    qDebug() << "..." << __func__;
}

/*!
 * \brief This function is the destructor of the class BattleMap.
 */
BattleMap::~BattleMap()
{
    qDebug() << "..." << __func__;

    for (quint32 rowIdx = 0U; rowIdx < m_numberRows; rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_numberColumns; columnIdx++)
        {
            delete m_battleMapSquares[rowIdx][columnIdx];
        }
    }
}

/*!
 * \brief This function returns the value of the member variable m_numberRows.
 */
quint32 BattleMap::getNumberRows() const
{
    //qDebug() << "..." << __func__;
    return m_numberRows;
}

/*!
 * \brief This function sets the value of the member variable m_numberRows.
 */
void BattleMap::setNumberRows(quint32 newNumberRows)
{
    //qDebug() << "..." << __func__;
    m_numberRows = newNumberRows;
}

/*!
 * \brief This function returns the value of the member variable m_numberColumns.
 */
quint32 BattleMap::getNumberColumns() const
{
    //qDebug() << "..." << __func__;
    return m_numberColumns;
}

/*!
 * \brief This function sets the value of the member variable m_numberColumns.
 */
void BattleMap::setNumberColumns(quint32 newNumberColumns)
{
    //qDebug() << "..." << __func__;
    m_numberColumns = newNumberColumns;
}

/*!
 * \brief This function returns the pixmap of the indexed member variable m_battleMapSquares.
 */
QGraphicsPixmapItem *BattleMap::getIndexedBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx) const
{
    //qDebug() << "..." << __func__;
    return m_battleMapSquares[rowIdx][columnIdx]->getBattleMapSquarePixMap();
}

/*!
 * \brief This function sets the pixmap of the indexed member variable m_battleMapSquares.
 */
void BattleMap::setIndexedBattleMapSquarePixmap(quint32 rowIdx, QGraphicsPixmapItem *newBattleMapSquarePixmap)
{
    //qDebug() << "..." << __func__;

    if (rowIdx + 1 > m_battleMapSquares.count())
    {
        qDebug() << "rows: " << rowIdx << m_battleMapSquares.count();
        m_battleMapSquares.append(QList<BattleMapSquare*>());

    }

    BattleMapSquare * battleMapSquare = new BattleMapSquare();
    battleMapSquare->setBattleMapSquarePixMap(newBattleMapSquarePixmap);

    m_battleMapSquares[rowIdx].append(battleMapSquare);
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
