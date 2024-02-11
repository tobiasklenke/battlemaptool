#ifndef BATTLEMAPSQUARE_H
#define BATTLEMAPSQUARE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QPainter>
#include <QPixmap>

#include "defines.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for a Battle Map square.
 */
class BattleMapSquare
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class BattleMapSquare.                                                                      *
     *                                                                                                                                              *
     * \details This function initializes the Battle Map square with the image of an empty Battle Map square.                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMapSquare();

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMapSquare.                                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMapSquare();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the pixmap of the member variable pBattleMapSquarePixmap.                                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the pixmap of the member variable pBattleMapSquarePixmap.                                                     *
     ************************************************************************************************************************************************/
    QPixmap getBattleMapSquarePixmap() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the pixmap of the member variable pBattleMapSquarePixmap.                                                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   battleMapSquarePixmap         Pixmap of the Battle Map square                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquarePixmap(QPixmap battleMapSquarePixmap);

    /*! *********************************************************************************************************************************************
     * \brief   This function scales the pixmap of the member variable pBattleMapSquarePixmap.                                                      *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   newSize                       New size of the pixmap of the Battle Map square                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void scaleBattleMapSquarePixmap(quint32 newSize);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_covered.                                                                   *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_covered.                                                                   *
     ************************************************************************************************************************************************/
    bool getCovered() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_covered.                                                                      *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   covered                       Information whether the Battle Map square is covered                                                  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setCovered(bool covered);

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*!
     * \brief This is the pixmap of the Battle Map square.
     */
    QPixmap m_battleMapSquarePixmap;

    /*!
     * \brief This is the information whether the Battle Map square is covered.
     */
    bool m_covered;
};

#endif // BATTLEMAPSQUARE_H
