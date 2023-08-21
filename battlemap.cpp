/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemap.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMap.
 */
BattleMap::BattleMap() :
    m_numberRows(0U),
    m_numberColumns(0U),
    m_battleMapSquares(QList<QList<BattleMapSquare*>>())
{
}

/*!
 * \brief This function is the destructor of the class BattleMap.
 */
BattleMap::~BattleMap()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquares.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquares[rowIdx].count(); columnIdx++)
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
    return m_numberRows;
}

/*!
 * \brief This function sets the value of the member variable m_numberRows.
 */
void BattleMap::setNumberRows(quint32 numberRows)
{
    m_numberRows = numberRows;
}

/*!
 * \brief This function returns the value of the member variable m_numberColumns.
 */
quint32 BattleMap::getNumberColumns() const
{
    return m_numberColumns;
}

/*!
 * \brief This function sets the value of the member variable m_numberColumns.
 */
void BattleMap::setNumberColumns(quint32 numberColumns)
{
    m_numberColumns = numberColumns;
}

/*!
 * \brief This function returns the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.
 */
QGraphicsPixmapItem *BattleMap::getIndexedBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx) const
{
    return m_battleMapSquares[rowIdx][columnIdx]->getBattleMapSquarePixMap();
}

/*!
 * \brief This function sets the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.
 */
void BattleMap::setIndexedBattleMapSquarePixmap(quint32 rowIdx, QGraphicsPixmapItem *battleMapSquarePixmap)
{
    /* append row to nested QList member variable m_battleMapSquares if row does not already exist */
    if (rowIdx + 1 > m_battleMapSquares.count())
    {
        m_battleMapSquares.append(QList<BattleMapSquare*>());
    }

    BattleMapSquare * battleMapSquare = new BattleMapSquare();
    battleMapSquare->setBattleMapSquarePixMap(battleMapSquarePixmap);

    /* append Battle Map square to row of nested QList member variable m_battleMapSquares */
    m_battleMapSquares[rowIdx].append(battleMapSquare);
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
