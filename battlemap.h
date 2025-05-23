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
     * \details This function initializes the Battle Map squares and copies the pixmaps of all the Battle Map squares.                              *
     *                                                                                                                                              *
     * \param   battleMap                     Battle Map to be copied                                                                               *
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
     * \brief   This function initializes the entries of the member variable m_battleMapSquares.                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void initBattleMapSquares();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map squares.                                                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapSquares();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_initialized.                                                               *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_initialized.                                                               *
     ************************************************************************************************************************************************/
    bool getInitialized() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_initialized to true.                                                          *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setInitialized();

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
     * \brief   This function returns the original pixmap of an entry of the member variable m_battleMapSquares.                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the original pixmap of an entry of the member variable m_battleMapSquares.                                    *
     ************************************************************************************************************************************************/
    QPixmap getBattleMapSquareOriginalPixmap(quint32 rowIdx, quint32 columnIdx) const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the original pixmap of an entry of the member variable m_battleMapSquares.                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     * \param   battleMapSquareOriginalPixmap Original pixmap of the Battle Map square                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquareOriginalPixmap(quint32 rowIdx, quint32 columnIdx, QPixmap battleMapSquareOriginalPixmap);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the disguise pixmap of an entry of the member variable m_battleMapSquares.                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the disguise pixmap of an entry of the member variable m_battleMapSquares.                                    *
     ************************************************************************************************************************************************/
    QPixmap getBattleMapSquareDisguisePixmap(quint32 rowIdx, quint32 columnIdx) const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the disguise pixmap of an entry of the member variable m_battleMapSquares.                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     * \param   battleMapSquareDisguisePixmap Disguise pixmap of the Battle Map square                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquareDisguisePixmap(quint32 rowIdx, quint32 columnIdx, QPixmap battleMapSquareDisguisePixmap);

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
     * \brief   This function returns the disguise state of an entry of the member variable m_battleMapSquares.                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the disguise state of an entry of the nested QList member variable m_battleMapSquares.                        *
     ************************************************************************************************************************************************/
    bool getBattleMapSquareDisguised(quint32 rowIdx, quint32 columnIdx) const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the disguise state of an entry of the member variable m_battleMapSquares.                                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     * \param   disguised                     Disguise state                                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquareDisguised(quint32 rowIdx, quint32 columnIdx, bool disguised);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the disguisability of an entry of the member variable m_battleMapSquares.                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the disguisability of an entry of the nested QList member variable m_battleMapSquares.                        *
     ************************************************************************************************************************************************/
    bool getBattleMapSquareDisguisable(quint32 rowIdx, quint32 columnIdx) const;

    /*! *********************************************************************************************************************************************
     * \brief   This function changes the original pixmaps of entries of the member variable m_battleMapSquares.                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   firstRowIdx                   Index of the first row                                                                                *
     * \param   firstColumnIdx                Index of the first column                                                                             *
     * \param   battleMapSquarePixmaps        Pixmaps of the Battle Map squares                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changeBattleMapSquareOriginalPixmaps(quint32 firstRowIdx, quint32 firstColumnIdx, QList<QList<QPixmap>> battleMapSquarePixmaps);

    /*! *********************************************************************************************************************************************
     * \brief   This function changes the disguise pixmaps of entries of the member variable m_battleMapSquares.                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   firstRowIdx                   Index of the first row                                                                                *
     * \param   firstColumnIdx                Index of the first column                                                                             *
     * \param   battleMapSquarePixmaps        Pixmaps of the Battle Map squares                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changeBattleMapSquareDisguisePixmaps(quint32 firstRowIdx, quint32 firstColumnIdx, QList<QList<QPixmap>> battleMapSquarePixmaps);

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
     *          it updates the variables for the numbers of rows and columns and for the Battle Map squares and the orientation of the Battle Map.  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rotateLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function rotates the Battle Map right.                                                                                         *
     *                                                                                                                                              *
     * \details This function gets the new numbers of rows and columns and resorts the Battle Map squares according to the right rotation. Finally, *
     *          it updates the variables for the numbers of rows and columns and for the Battle Map squares and the orientation of the Battle Map.  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rotateRight();

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*!
     * \brief This is the information whether the Battle Map has been initialized.
     */
    bool m_initialized = false;

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

    /*!
     * \brief This is the orientation of the Battle Map in degrees.
     */
    quint32 m_orientation;
};

#endif // BATTLEMAP_H
