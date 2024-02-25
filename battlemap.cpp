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
 * \brief This function is the copy constructor of the class BattleMap.
 */
BattleMap::BattleMap(BattleMap &battleMap) :
    m_numberRows(battleMap.getNumberRows()),
    m_numberColumns(battleMap.getNumberColumns()),
    m_battleMapSquares(QList<QList<BattleMapSquare*>>())
{
    /* copy pixmaps of all Battle Map squares */
    for (quint32 rowIdx = 0U; rowIdx < m_numberRows; rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_numberColumns; columnIdx++)
        {
            setBattleMapSquarePixmap(rowIdx, battleMap.getBattleMapSquarePixmap(rowIdx, columnIdx));
        }
    }
}

/*!
 * \brief This function is the destructor of the class BattleMap.
 */
BattleMap::~BattleMap()
{
    /* delete all Battle Map squares */
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
 * \brief This function returns the pixmap of an entry of the member variable m_battleMapSquares.
 */
QPixmap BattleMap::getBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx) const
{
    return m_battleMapSquares[rowIdx][columnIdx]->getBattleMapSquarePixmap();
}

/*!
 * \brief This function sets the pixmap of an entry of the member variable m_battleMapSquares.
 */
void BattleMap::setBattleMapSquarePixmap(quint32 rowIdx, QPixmap battleMapSquarePixmap)
{
    /* append row to nested QList member variable m_battleMapSquares if row does not already exist */
    if (rowIdx + 1 > m_battleMapSquares.count())
    {
        m_battleMapSquares.append(QList<BattleMapSquare*>());
    }

    /* construct new Battle Map square object and set pixmap */
    BattleMapSquare * battleMapSquare = new BattleMapSquare();
    battleMapSquare->setBattleMapSquarePixmap(battleMapSquarePixmap);

    /* append Battle Map square to row of nested QList member variable m_battleMapSquares */
    m_battleMapSquares[rowIdx].append(battleMapSquare);
}

/*!
 * \brief This function scales the pixmap of an entry of the member variable m_battleMapSquares.
 */
void BattleMap::scaleBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx, quint32 newSize)
{
    m_battleMapSquares[rowIdx][columnIdx]->scaleBattleMapSquarePixmap(newSize);
}

/*!
 * \brief This function returns the coverage state of an entry of the member variable m_battleMapSquares.
 */
bool BattleMap::getBattleMapSquareCovered(quint32 rowIdx, quint32 columnIdx) const
{
    return m_battleMapSquares[rowIdx][columnIdx]->getCovered();
}

/*!
 * \brief This function sets the coverage state of an entry of the member variable m_battleMapSquares.
 */
void BattleMap::setBattleMapSquareCovered(quint32 rowIdx, quint32 columnIdx, bool covered)
{
    m_battleMapSquares[rowIdx][columnIdx]->setCovered(covered);
}

/*!
 * \brief This function inserts a new row above the Battle Map.
 */
void BattleMap::insertRowAbove()
{
    /* insert new row above Battle Map */
    m_battleMapSquares.prepend(QList<BattleMapSquare*>());
    for (quint32 columnIdx = 0U; columnIdx < m_numberColumns; columnIdx++)
    {
        /* construct new Battle Map square object */
        BattleMapSquare * battleMapSquare = new BattleMapSquare();

        /* append Battle Map square to row */
        m_battleMapSquares.first().append(battleMapSquare);
    }

    /* increment number of rows */
    m_numberRows++;
}

/*!
 * \brief This function inserts a new row below the Battle Map.
 */
void BattleMap::insertRowBelow()
{
    /* insert new row below Battle Map */
    m_battleMapSquares.append(QList<BattleMapSquare*>());
    for (quint32 columnIdx = 0U; columnIdx < m_numberColumns; columnIdx++)
    {
        /* construct new Battle Map square object */
        BattleMapSquare * battleMapSquare = new BattleMapSquare();

        /* append Battle Map square to row */
        m_battleMapSquares.last().append(battleMapSquare);
    }

    /* increment number of rows */
    m_numberRows++;
}

/*!
 * \brief This function inserts a new column to the left of the Battle Map.
 */
void BattleMap::insertColumnLeft()
{
    /* insert new column to the left of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_numberRows; rowIdx++)
    {
        /* construct new Battle Map square object */
        BattleMapSquare * battleMapSquare = new BattleMapSquare();

        /* prepend Battle Map square to row */
        m_battleMapSquares[rowIdx].prepend(battleMapSquare);
    }

    /* increment number of columns */
    m_numberColumns++;
}

/*!
 * \brief This function inserts a new column to the right of the Battle Map.
 */
void BattleMap::insertColumnRight()
{
    /* insert new column to the right of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_numberRows; rowIdx++)
    {
        /* construct new Battle Map square object */
        BattleMapSquare * battleMapSquare = new BattleMapSquare();

        /* append Battle Map square to row */
        m_battleMapSquares[rowIdx].append(battleMapSquare);
    }

    /* increment number of columns */
    m_numberColumns++;
}

/*!
 * \brief This function deletes a row above the Battle Map.
 */
void BattleMap::deleteRowAbove()
{
    /* delete row above Battle Map */
    for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquares.first().count(); columnIdx++)
    {
        delete m_battleMapSquares.first()[columnIdx];
    }
    m_battleMapSquares.removeFirst();

    /* decrement number of rows */
    m_numberRows--;
}

/*!
 * \brief This function deletes a row below the Battle Map.
 */
void BattleMap::deleteRowBelow()
{
    /* delete row below Battle Map */
    for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquares.last().count(); columnIdx++)
    {
        delete m_battleMapSquares.last()[columnIdx];
    }
    m_battleMapSquares.removeLast();

    /* decrement number of rows */
    m_numberRows--;
}

/*!
 * \brief This function deletes a column to the left of the Battle Map.
 */
void BattleMap::deleteColumnLeft()
{
    /* delete column to the left of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquares.count(); rowIdx++)
    {
        delete m_battleMapSquares[rowIdx].first();
        m_battleMapSquares[rowIdx].removeFirst();
    }

    /* decrement number of columns */
    m_numberColumns--;
}

/*!
 * \brief This function deletes a column to the right of the Battle Map.
 */
void BattleMap::deleteColumnRight()
{
    /* delete column to the right of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquares.count(); rowIdx++)
    {
        delete m_battleMapSquares[rowIdx].last();
        m_battleMapSquares[rowIdx].removeLast();
    }

    /* decrement number of columns */
    m_numberColumns--;
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
