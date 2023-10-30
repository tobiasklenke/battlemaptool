#ifndef BATTLEMAPSCENEMASTERSCREEN_H
#define BATTLEMAPSCENEMASTERSCREEN_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsRectItem>

#include "battlemapscene.h"
#include "defines.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for the display of the Battle Map on the master screen.
 */
class BattleMapSceneMasterScreen : public BattleMapScene
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class BattleMapSceneMasterScreen.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   parent                        Parent of the class BattleMapSceneMasterScreen                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMapSceneMasterScreen(QObject *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMapSceneMasterScreen.                                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMapSceneMasterScreen();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the member variable m_scaleFactor and the pen properties.                                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changed_ScaleFactor(qreal scaleFactor);

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event on the Battle Map scene.                                                                  *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse move event on the Battle Map scene.                                                                   *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   event                         Mouse move event to be handled                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event on the Battle Map scene.                                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   event                         Mouse release event to be handled                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as some Battle Map squares have been selected.                                                         *
     ************************************************************************************************************************************************/
    void selected_BattleMapSquares(void);

private slots: /* - */

private:

    /*!
     * \brief This is the rectangle to be drawn while the selection on the Battle Map.
     */
    QGraphicsRectItem  m_battleMapSelectionSquareToDraw;

    /*!
     * \brief This is the factor that is used for scaling the Battle Map scene while scrolling.
     */
    qreal m_scaleFactor;

};

#endif // BATTLEMAPSCENEMASTERSCREEN_H
