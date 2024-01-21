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
 * \brief This class implements the functionality needed for a custom graphics scene for display of the Battle Map on the master screen.
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
    void changedScaleFactor(qreal scaleFactor);

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event.                                                                                          *
     *                                                                                                                                              *
     * \details This function handles a mouse press event. In case that the left button has been pressed, it calls the base class function in order *
     *          to set press position. Afterwards, it checks whether the mouse press event is positioned at the Battle Map scene and if so, it adds *
     *          the selection rectangle to the Battle Map scene and sets its pen properties.                                                        *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse move event.                                                                                           *
     *                                                                                                                                              *
     * \details This function handles a mouse move event. It determines the corners of the selection rectangle built from the mouse press event and *
     *          the mouse move event positions and updates the selection rectangle accordingly.                                                     *
     *                                                                                                                                              *
     * \param   event                         Mouse move event to be handled                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event.                                                                                        *
     *                                                                                                                                              *
     * \details This function handles a mouse release event. In case that the left button has been pressed, it resets the selection rectangle and   *
     *          removes it from the Battle Map scene. Afterwards, it calls the base class function in order to set the release position. Finally,   *
     *          it checks whether the mouse release event is positioned at the Battle Map scene and if so, it emits the signal for the completed    *
     *          selection of Battle Map squares.                                                                                                    *
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
    void selectedBattleMapSquares(void);

private slots: /* - */

private:

    /*!
     * \brief This is the rectangle to be drawn while the selection on the Battle Map.
     */
    QGraphicsRectItem  m_battleMapSelectionRectToDraw;

    /*!
     * \brief This is the factor that is used for scaling the Battle Map scene while scrolling.
     */
    qreal m_scaleFactor;

};

#endif // BATTLEMAPSCENEMASTERSCREEN_H
