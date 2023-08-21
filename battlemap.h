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
 * \brief This class implements the functionality of a Battle Map.
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
     * \brief   This function is the destructor of the class BattleMap.                                                                             *
     *                                                                                                                                              *
     * \details This function deletes the objects pointed to by the nested QList member variable m_battleMapSquares.                                *
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
     * \brief   This function returns the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   columnIdx                     Index of the column                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.                        *
     ************************************************************************************************************************************************/
    QGraphicsPixmapItem *getIndexedBattleMapSquarePixmap(quint32 rowIdx, quint32 columnIdx) const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the pixmap of an indexed entry of the nested QList member variable m_battleMapSquares.                           *
     *                                                                                                                                              *
     * \details This function checks if the parameter rowIdx exceeds the current number of rows in the nested QList member variable                 *
     *          m_battleMapSquares and appends a new row if this is the case. Afterwards, the function creates a new Battle Map square and sets its *
     *          pixmap according to the parameter battleMapSquarePixmap. Finally, the function appends this newly created Battle Map square to the  *
     *          row indicated by the parameter rowIdx.                                                                                              *
     *                                                                                                                                              *
     * \param   rowIdx                        Index of the row                                                                                      *
     * \param   battleMapSquarePixmap         Pixmap of the Battle Map square                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setIndexedBattleMapSquarePixmap(quint32 rowIdx, QGraphicsPixmapItem *battleMapSquarePixmap);

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
