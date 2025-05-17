#ifndef BATTLEMAPSQUARE_H
#define BATTLEMAPSQUARE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QCryptographicHash>
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
     * \details This function initializes the Battle Map square with the image of an empty Battle Map square that is rotated according to the       *
     *          Battle Map orientation and draws the Battle Map grid around the Battle Map square.                                                  *
     *                                                                                                                                              *
     * \param   orientation                   Orientation of the Battle Map square                                                                  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMapSquare(qreal orientation);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMapSquare.                                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMapSquare();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the pixmap of the member variable m_battleMapSquareOriginalPixmap.                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the pixmap of the member variable m_battleMapSquareOriginalPixmap.                                            *
     ************************************************************************************************************************************************/
    QPixmap getBattleMapSquareOriginalPixmap() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the pixmap of the member variable m_battleMapSquareOriginalPixmap and ascertains whether the Battle Map square   *
     *          is disguisable.                                                                                                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   battleMapSquarePixmap         Pixmap of the Battle Map square                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquareOriginalPixmap(QPixmap battleMapSquarePixmap);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the pixmap of the member variable m_battleMapSquareDisguisePixmap.                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the pixmap of the member variable m_battleMapSquareDisguisePixmap.                                            *
     ************************************************************************************************************************************************/
    QPixmap getBattleMapSquareDisguisePixmap() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the pixmap of the member variable m_battleMapSquareOriginalPixmap and ascertains whether the Battle Map square   *
     *          is disguisable.                                                                                                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   battleMapSquarePixmap         Pixmap of the Battle Map square                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSquareDisguisePixmap(QPixmap battleMapSquarePixmap);

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

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_disguised.                                                                 *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_disguised.                                                                 *
     ************************************************************************************************************************************************/
    bool getDisguised() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_disguised.                                                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   disguised                     Information whether the Battle Map square is disguised                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setDisguised(bool disguised);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_disguisable.                                                               *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_disguisable.                                                               *
     ************************************************************************************************************************************************/
    bool getDisguisable() const;

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function ascertains whether the Battle Map square is disguisable and sets the value of the member variable m_disguisable       *
     *          accordingly.                                                                                                                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void ascertainDisguisable();

    /*!
     * \brief This is the original pixmap of the Battle Map square.
     */
    QPixmap m_battleMapSquareOriginalPixmap;

    /*!
     * \brief This is the disguise pixmap of the Battle Map square.
     */
    QPixmap m_battleMapSquareDisguisePixmap;

    /*!
     * \brief This is the information whether the Battle Map square is covered.
     */
    bool m_covered;

    /*!
     * \brief This is the information whether the Battle Map square is disguised.
     */
    bool m_disguised;

    /*!
     * \brief This is the information whether the Battle Map square is disguisable.
     */
    bool m_disguisable;
};

#endif // BATTLEMAPSQUARE_H
