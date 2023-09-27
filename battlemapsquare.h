#ifndef BATTLEMAPSQUARE_H
#define BATTLEMAPSQUARE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QPixmap>

#include "defines.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality of a Battle Map square.
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
     * \brief   This function returns the pixmap of the member variable pBattleMapSquarePixmap                                                      *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the pixmap of the member variable pBattleMapSquarePixmap.                                                     *
     ************************************************************************************************************************************************/
    QPixmap getBattleMapSquarePixmap() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the pixmap of the member variable pBattleMapSquarePixmap                                                         *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   battleMapSquarePixmap         Pixmap of the Battle Map square                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquarePixmap(QPixmap battleMapSquarePixmap);

    /*! *********************************************************************************************************************************************
     * \brief   This function scales the pixmap of the member variable pBattleMapSquarePixmap                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   newSize                       New size of the pixmap of the Battle Map square                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void scaleBattleMapSquarePixmap(quint32 newSize);

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*!
     * \brief This is the pixmap of the Battle Map square.
     */
    QPixmap m_battleMapSquarePixmap;
};

#endif // BATTLEMAPSQUARE_H
