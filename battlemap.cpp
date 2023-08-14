/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemap.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function is the constructor of the class BattleMap.                                                                                *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
BattleMap::BattleMap() :
    m_numberRows(0U),
    m_numberColumns(0U),
    m_battleMapSquares(QList<QList<BattleMapSquare*>>())
{
    qDebug() << "..." << __func__;
}

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class BattleMap.                                                                                 *
 *                                                                                                                                                  *
 * \details This function deletes the objects pointed to by the nested QList member variable m_battleMapSquares.                                    *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
BattleMap::~BattleMap()
{
    qDebug() << "..." << __func__;

    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquares.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquares[rowIdx].count(); columnIdx++)
        {
            delete m_battleMapSquares[rowIdx][columnIdx];
        }
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_numberRows.                                                                    *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_numberRows.                                                                    *
 ****************************************************************************************************************************************************/
quint32 BattleMap::getNumberRows() const
{
    //qDebug() << "..." << __func__;

    return m_numberRows;
}

/*!**************************************************************************************************************************************************
 * \brief   This function sets the value of the member variable m_numberRows.                                                                       *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   numberRows                    Number of rows                                                                                            *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void BattleMap::setNumberRows(quint32 numberRows)
{
    //qDebug() << "..." << __func__;

    m_numberRows = numberRows;
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_numberColumns.                                                                 *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_numberColumns.                                                                 *
 ****************************************************************************************************************************************************/
quint32 BattleMap::getNumberColumns() const
{
    //qDebug() << "..." << __func__;

    return m_numberColumns;
}

/*!**************************************************************************************************************************************************
 * \brief   This function sets the value of the member variable m_numberColumns.                                                                    *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   m_numberColumns               Number of columns                                                                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void BattleMap::setNumberColumns(quint32 numberColumns)
{
    //qDebug() << "..." << __func__;

    m_numberColumns = numberColumns;
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.                            *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   rowIdx                        Index of the row                                                                                          *
 * \param   columnIdx                     Index of the column                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.                            *
 ****************************************************************************************************************************************************/
QGraphicsPixmapItem *BattleMap::getIndexedBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx) const
{
    //qDebug() << "..." << __func__;

    return m_battleMapSquares[rowIdx][columnIdx]->getBattleMapSquarePixMap();
}

/*!**************************************************************************************************************************************************
 * \brief   This function sets the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.                               *
 *                                                                                                                                                  *
 * \details This function checks if the parameter rowIdx exceeds the current number of rows in the nested QList member variable m_battleMapSquares  *
 *          and appends a new row if this is the case. Afterwards, the function creates a new Battle Map square and sets its pixmap according to    *
 *          the parameter battleMapSquarePixmap. Finally, the function appends this newly created Battle Map square to the row indicated by the     *
 *          parameter rowIdx.                                                                                                                       *
 *                                                                                                                                                  *
 * \param   rowIdx                        Index of the row                                                                                          *
 * \param   battleMapSquarePixmap         Pixmap of the Battle Map square                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void BattleMap::setIndexedBattleMapSquarePixmap(quint32 rowIdx, QGraphicsPixmapItem *battleMapSquarePixmap)
{
    //qDebug() << "..." << __func__;

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
