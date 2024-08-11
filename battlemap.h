#ifndef BATTLEMAP_H
#define BATTLEMAP_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapsquare.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for a Battle Map.
 */
class BattleMap
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class BattleMap.                                                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function is the copy constructor of the class BattleMap.                                                                       *
     *                                                                                                                                              *
     * \details This function copies the pixmaps of all the Battle Map squares.                                                                     *
     *                                                                                                                                              *
     * \param   battleMap                     Battle Map to be copied                                                                               *
     *                                                                                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMap(BattleMap &battleMap);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMap.                                                                             *
     *                                                                                                                                              *
     * \details This function deletes the objects created in the constructor.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_numberRows.                                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_numberRows.                                                                *
     ************************************************************************************************************************************************/
    quint32 getNumberRows() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_numberRows.                                                                   *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   numberRows                    Number of rows                                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setNumberRows(quint32 numberRows);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_numberColumns.                                                             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_numberColumns.                                                             *
     ************************************************************************************************************************************************/
    quint32 getNumberColumns() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_numberColumns.                                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   numberColumns                 Number of columns                                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setNumberColumns(quint32 numberColumns);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the pixmap of an entry of the member variable m_battleMapSquares.                                             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the pixmap of an entry of the member variable m_battleMapSquares.                                             *
     ************************************************************************************************************************************************/
    QPixmap getBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx) const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the pixmap of an entry of the member variable m_battleMapSquares.                                                *
     *                                                                                                                                              *
     * \details This function checks if the parameter rowIdx exceeds the current number of rows in the nested QList member variable                 *
     *          m_battleMapSquares and appends a new row if this is the case. Afterwards, the function constructs a new Battle Map square object    *
     *          and sets its pixmap according to the parameter battleMapSquarePixmap. Finally, the function appends this newly created Battle Map   *
     *          square to the row indicated by the parameter rowIdx.                                                                                *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   battleMapSquarePixmap         Pixmap of the Battle Map square                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquarePixmap(quint32 rowIdx, QPixmap battleMapSquarePixmap);

    /*! *********************************************************************************************************************************************
     * \brief   This function scales the pixmap of an entry of the member variable m_battleMapSquares.                                              *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     * \param   newSize                       New size of the pixmap of the Battle Map square                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void scaleBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx, quint32 newSize);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the coverage state of an entry of the member variable m_battleMapSquares.                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the coverage state of an entry of the nested QList member variable m_battleMapSquares.                        *
     ************************************************************************************************************************************************/
    bool getBattleMapSquareCovered(quint32 rowIdx, quint32 columnIdx) const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the coverage state of an entry of the member variable m_battleMapSquares.                                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     * \param   covered                       Coverage state                                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquareCovered(quint32 rowIdx, quint32 columnIdx, bool covered);

    /*! *********************************************************************************************************************************************
     * \brief   This function changes the pixmaps of entries of the member variable m_battleMapSquares.                                             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   firstRowIdx                   Index of the first row                                                                                *
     * \param   firstColumnIdx                Index of the first column                                                                             *
     * \param   battleMapSquarePixmaps        Pixmaps of the Battle Map squares                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changeBattleMapSquarePixmaps(quint32 firstRowIdx, quint32 firstColumnIdx, QList<QList<QPixmap>> battleMapSquarePixmaps);

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new row above the Battle Map.                                                                               *
     *                                                                                                                                              *
     * \details This function inserts a new row above the Battle Map, using the parameter rowAbove. If the parameter rowAbove does not contain any  *
     *          Battle Map squares, it is filled with empty Battle Map squares. Finally, the function increments the number of rows.                *
     *                                                                                                                                              *
     * \param   rowAbove                      Row to insert above                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertRowAbove(QList<BattleMapSquare*> rowAbove);

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new row below the Battle Map.                                                                               *
     *                                                                                                                                              *
     * \details This function inserts a new row below the Battle Map, using the parameter rowBelow. If the parameter rowBelow does not contain any  *
     *          Battle Map squares, it is filled with empty Battle Map squares. Finally, the function increments the number of rows.                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertRowBelow(QList<BattleMapSquare*> rowBelow);

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new column to the left of the Battle Map.                                                                   *
     *                                                                                                                                              *
     * \details This function inserts a new column to the left of the Battle Map. If the parameter columnLeft contains any Battle Map squares,      *
     *          these are inserted to the left of the Battle Map. Otherwise, the new column is built from empty Battle Map squares. Finally, the    *
     *          function increments the number of columns.                                                                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertColumnLeft(QList<BattleMapSquare*> columnLeft);

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new column to the right of the Battle Map.                                                                  *
     *                                                                                                                                              *
     * \details This function inserts a new column to the right of the Battle Map. If the parameter columnRight contains any Battle Map squares,    *
     *          these are inserted to the right of the Battle Map. Otherwise, the new column is built from empty Battle Map squares. Finally, the   *
     *          function increments the number of columns.                                                                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertColumnRight(QList<BattleMapSquare*> columnRight);

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a row above the Battle Map.                                                                                   *
     *                                                                                                                                              *
     * \details This function deletes a row above the Battle Map and decrements the number of rows.                                                 *
     *                                                                                                                                              *
     * \return  This function returns the deleted row.                                                                                              *
     ************************************************************************************************************************************************/
    QList<BattleMapSquare*> deleteRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a row below the Battle Map.                                                                                   *
     *                                                                                                                                              *
     * \details This function deletes a row below the Battle Map and decrements the number of rows.                                                 *
     *                                                                                                                                              *
     * \return  This function returns the deleted row.                                                                                              *
     ************************************************************************************************************************************************/
     QList<BattleMapSquare*> deleteRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a column to the left of the Battle Map.                                                                       *
     *                                                                                                                                              *
     * \details This function deletes a column to the left of the Battle Map and decrements the number of columns.                                  *
     *                                                                                                                                              *
     * \return  This function returns the deleted column.                                                                                           *
     ************************************************************************************************************************************************/
    QList<BattleMapSquare*> deleteColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a column to the right of the Battle Map.                                                                      *
     *                                                                                                                                              *
     * \details This function deletes a column to the right of the Battle Map and decrements the number of columns.                                 *
     *                                                                                                                                              *
     * \return  This function returns the deleted column.                                                                                           *
     ************************************************************************************************************************************************/
    QList<BattleMapSquare*> deleteColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function rotates the Battle Map left.                                                                                          *
     *                                                                                                                                              *
     * \details This function gets the new numbers of rows and columns and resorts the Battle Map squares according to the left rotation. Finally,  *
     *          it updates the variables for the numbers of rows and columns and for the Battle Map squares.                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rotateLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function rotates the Battle Map right.                                                                                         *
     *                                                                                                                                              *
     * \details This function gets the new numbers of rows and columns and resorts the Battle Map squares according to the right rotation. Finally, *
     *          it updates the variables for the numbers of rows and columns and for the Battle Map squares.                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rotateRight();

protected: /* - */

signals: /* - */

private slots: /* - */

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
