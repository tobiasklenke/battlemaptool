#ifndef BATTLEMAPSCENEPLAYERSCREEN_H
#define BATTLEMAPSCENEPLAYERSCREEN_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsRectItem>

#include "battlemapscene.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for a custom graphics scene for display of the Battle Map on the player screen.
 */
class BattleMapScenePlayerScreen : public BattleMapScene
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class BattleMapScenePlayerScreen.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   parent                        Parent of the class BattleMapScenePlayerScreen                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMapScenePlayerScreen(QObject *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMapScenePlayerScreen.                                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMapScenePlayerScreen();

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event.                                                                                          *
     *                                                                                                                                              *
     * \details This function handles a mouse press event. It calls the base class function in order to set the press position.                     *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse move event.                                                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   event                         Mouse move event to be handled                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event.                                                                                        *
     *                                                                                                                                              *
     * \details This function handles a mouse release event. It calls the base class function in order to set the release position.                 *
     *                                                                                                                                              *
     * \param   event                         Mouse release event to be handled                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals: /* - */

private slots: /* - */

private: /* - */

};

#endif // BATTLEMAPSCENEPLAYERSCREEN_H
