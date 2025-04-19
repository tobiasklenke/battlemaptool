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
    m_battleMapSquares(QList<QList<BattleMapSquare*>>()),
    m_orientation(ORIENTATION_0_DEGREES)
{
}

/*!
 * \brief This function is the copy constructor of the class BattleMap.
 */
BattleMap::BattleMap(BattleMap &battleMap) :
    m_numberRows(battleMap.getNumberRows()),
    m_numberColumns(battleMap.getNumberColumns()),
    m_battleMapSquares(QList<QList<BattleMapSquare*>>()),
    m_orientation(ORIENTATION_0_DEGREES)
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
    deleteBattleMapSquares();
}

/*!
 * \brief This function deletes the Battle Map squares.
 */
void BattleMap::deleteBattleMapSquares()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquares.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquares[rowIdx].count(); columnIdx++)
        {
            delete m_battleMapSquares[rowIdx][columnIdx];
        }
    }
    m_battleMapSquares.clear();
}

/*!
 * \brief This function returns the value of the member variable m_initialized.
 */
bool BattleMap::getInitialized() const
{
    return m_initialized;
}

/*!
 * \brief This function sets the value of the member variable m_initialized to true.
 */
void BattleMap::setInitialized()
{
    m_initialized = true;
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
    BattleMapSquare * battleMapSquare = new BattleMapSquare(m_orientation);
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
 * \brief This function changes the pixmaps of entries of the member variable m_battleMapSquares.
 */
void BattleMap::changeBattleMapSquarePixmaps(quint32 firstRowIdx, quint32 firstColumnIdx, QList<QList<QPixmap>> battleMapSquarePixmaps)
{
    for (quint32 rowIdx = 0U; rowIdx < battleMapSquarePixmaps.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < battleMapSquarePixmaps.first().count(); columnIdx++)
        {
            if ((firstRowIdx + rowIdx < m_numberRows) && (firstColumnIdx + columnIdx < m_numberColumns))
            {
                /* change pixmaps of entries of member variable m_battleMapSquares */
                m_battleMapSquares[firstRowIdx + rowIdx][firstColumnIdx + columnIdx]->setBattleMapSquarePixmap(battleMapSquarePixmaps[rowIdx][columnIdx]);
            }
        }
    }
}

/*!
 * \brief This function inserts a new row above the Battle Map.
 */
void BattleMap::insertRowAbove(QList<BattleMapSquare*> rowAbove)
{
    /* insert new row above Battle Map */
    m_battleMapSquares.prepend(rowAbove);

    if (0U == rowAbove.count())
    {
        for (quint32 columnIdx = 0U; columnIdx < m_numberColumns; columnIdx++)
        {
            /* construct new Battle Map square object */
            BattleMapSquare * battleMapSquare = new BattleMapSquare(static_cast<qreal>(m_orientation));

            /* append empty Battle Map square to row */
            m_battleMapSquares.first().append(battleMapSquare);
        }
    }

    /* increment number of rows */
    m_numberRows++;
}

/*!
 * \brief This function inserts a new row below the Battle Map.
 */
void BattleMap::insertRowBelow(QList<BattleMapSquare*> rowBelow)
{
    /* insert new row below Battle Map */
    m_battleMapSquares.append(rowBelow);

    if (0U == rowBelow.count())
    {
        for (quint32 columnIdx = 0U; columnIdx < m_numberColumns; columnIdx++)
        {
            /* construct new Battle Map square object */
            BattleMapSquare * battleMapSquare = new BattleMapSquare(static_cast<qreal>(m_orientation));

            /* append empty Battle Map square to row */
            m_battleMapSquares.last().append(battleMapSquare);
        }
    }

    /* increment number of rows */
    m_numberRows++;
}

/*!
 * \brief This function inserts a new column to the left of the Battle Map.
 */
void BattleMap::insertColumnLeft(QList<BattleMapSquare*> columnLeft)
{
    /* insert new column to the left of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_numberRows; rowIdx++)
    {
        if (0U == columnLeft.count())
        {
            /* construct new Battle Map square object */
            BattleMapSquare * battleMapSquare = new BattleMapSquare(static_cast<qreal>(m_orientation));

            /* prepend empty Battle Map square to row */
            m_battleMapSquares[rowIdx].prepend(battleMapSquare);
        }
        else
        {
            /* prepend Battle Map square to row */
            m_battleMapSquares[rowIdx].prepend(columnLeft[rowIdx]);
        }

    }

    /* increment number of columns */
    m_numberColumns++;
}

/*!
 * \brief This function inserts a new column to the right of the Battle Map.
 */
void BattleMap::insertColumnRight(QList<BattleMapSquare*> columnRight)
{
    /* insert new column to the right of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_numberRows; rowIdx++)
    {
        if (0U == columnRight.count())
        {
            /* construct new Battle Map square object */
            BattleMapSquare * battleMapSquare = new BattleMapSquare(static_cast<qreal>(m_orientation));

            /* append empty Battle Map square to row */
            m_battleMapSquares[rowIdx].append(battleMapSquare);
        }
        else
        {
            /* append Battle Map square to row */
            m_battleMapSquares[rowIdx].append(columnRight[rowIdx]);
        }

    }

    /* increment number of columns */
    m_numberColumns++;
}

/*!
 * \brief This function deletes a row above the Battle Map.
 */
QList<BattleMapSquare*> BattleMap::deleteRowAbove()
{
    /* store row to delete before deletion from Battle Map */
    QList<BattleMapSquare*> rowToDelete = m_battleMapSquares.first();
    m_battleMapSquares.removeFirst();

    /* decrement number of rows */
    m_numberRows--;

    return rowToDelete;
}

/*!
 * \brief This function deletes a row below the Battle Map.
 */
QList<BattleMapSquare*> BattleMap::deleteRowBelow()
{
    /* store row to delete before deletion from Battle Map */
    QList<BattleMapSquare*> rowToDelete = m_battleMapSquares.last();
    m_battleMapSquares.removeLast();

    /* decrement number of rows */
    m_numberRows--;

    return rowToDelete;
}

/*!
 * \brief This function deletes a column to the left of the Battle Map.
 */
QList<BattleMapSquare*> BattleMap::deleteColumnLeft()
{
    /* store column to delete before deletion from Battle Map */
    QList<BattleMapSquare*> columnToDelete;
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquares.count(); rowIdx++)
    {
        columnToDelete.append(m_battleMapSquares[rowIdx].first());
        m_battleMapSquares[rowIdx].removeFirst();
    }

    /* decrement number of columns */
    m_numberColumns--;

    return columnToDelete;
}

/*!
 * \brief This function deletes a column to the right of the Battle Map.
 */
QList<BattleMapSquare*> BattleMap::deleteColumnRight()
{
    /* store column to delete before deletion from Battle Map */
    QList<BattleMapSquare*> columnToDelete;
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquares.count(); rowIdx++)
    {
        columnToDelete.append(m_battleMapSquares[rowIdx].last());
        m_battleMapSquares[rowIdx].removeLast();
    }

    /* decrement number of columns */
    m_numberColumns--;

    return columnToDelete;
}

/*!
 * \brief This function rotates the Battle Map left.
 */
void BattleMap::rotateLeft()
{
    /* get new number of rows and columns */
    quint32 newNumberRows = m_numberColumns;
    quint32 newNumberColumns = m_numberRows;

    /* resort Battle Map squares */
    QList<QList<BattleMapSquare*>> newBattleMapSquares;
    for (quint32 rowIdx = 0U; rowIdx < newNumberRows; rowIdx++)
    {
        newBattleMapSquares.append(QList<BattleMapSquare*>());

        for (quint32 columnIdx = 0U; columnIdx < newNumberColumns; columnIdx++)
        {
            /* rotate Battle Map square left */
            QPixmap newBattleMapSquarePixmap = m_battleMapSquares[columnIdx][newNumberRows - rowIdx - 1U]->getBattleMapSquarePixmap().transformed(QTransform().rotate(ORIENTATION_270_DEGREES));
            m_battleMapSquares[columnIdx][newNumberRows - rowIdx - 1U]->setBattleMapSquarePixmap(newBattleMapSquarePixmap);

            newBattleMapSquares.last().append(m_battleMapSquares[columnIdx][newNumberRows - rowIdx - 1U]);
        }
    }

    /* update variables */
    m_numberRows = newNumberRows;
    m_numberColumns = newNumberColumns;
    m_battleMapSquares = newBattleMapSquares;

    /* update orientation of Battle Map */
    m_orientation = (m_orientation + static_cast<quint32>(ORIENTATION_270_DEGREES)) % static_cast<quint32>(ORIENTATION_360_DEGREES);
}

/*!
 * \brief This function rotates the Battle Map right.
 */
void BattleMap::rotateRight()
{
    /* get new number of rows and columns */
    quint32 newNumberRows = m_numberColumns;
    quint32 newNumberColumns = m_numberRows;

    /* resort Battle Map squares */
    QList<QList<BattleMapSquare*>> newBattleMapSquares;
    for (quint32 rowIdx = 0U; rowIdx < newNumberRows; rowIdx++)
    {
        newBattleMapSquares.append(QList<BattleMapSquare*>());

        for (quint32 columnIdx = 0U; columnIdx < newNumberColumns; columnIdx++)
        {
            /* rotate Battle Map square left */
            QPixmap newBattleMapSquarePixmap = m_battleMapSquares[newNumberColumns - columnIdx - 1U][rowIdx]->getBattleMapSquarePixmap().transformed(QTransform().rotate(ORIENTATION_90_DEGREES));
            m_battleMapSquares[newNumberColumns - columnIdx - 1U][rowIdx]->setBattleMapSquarePixmap(newBattleMapSquarePixmap);

            newBattleMapSquares.last().append(m_battleMapSquares[newNumberColumns - columnIdx - 1U][rowIdx]);
        }
    }

    /* update variables */
    m_numberRows = newNumberRows;
    m_numberColumns = newNumberColumns;
    m_battleMapSquares = newBattleMapSquares;

    /* update orientation of Battle Map */
    m_orientation = (m_orientation + static_cast<quint32>(ORIENTATION_90_DEGREES)) % static_cast<quint32>(ORIENTATION_360_DEGREES);
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
