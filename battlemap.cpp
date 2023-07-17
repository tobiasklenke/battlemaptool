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
    m_battleMapSquares(QList<QList<BattleMapSquare>>())
{
    qDebug() << "..." << __func__;
}

/*!
 * \brief This function is the destructor of the class BattleMap.
 */
BattleMap::~BattleMap()
{
    qDebug() << "..." << __func__;
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
