#ifndef BATTLEMAPSCENE_H
#define BATTLEMAPSCENE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for the selection of a Battle Map square.
 */
class BattleMapScene : public QGraphicsScene
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class BattleMapScene.                                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   parent                        Parent of the class BattleMapScene                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMapScene(QObject *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMapScene.                                                                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_scenePosPress.                                                             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_scenePosPress.                                                             *
     ************************************************************************************************************************************************/
    QPointF getScenePosPress() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_scenePosRelease.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_scenePosRelease.                                                           *
     ************************************************************************************************************************************************/
    QPointF getScenePosRelease() const;

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event on the Battle Map scene.                                                                  *
     *                                                                                                                                              *
     * \details This function handles a mouse press event on the Battle Map scene by resetting the member variables m_scenePosPress and             *
     *          m_scenePosRelease first. Afterwards, the function checks whether the mouse press event is positioned at the Battle Map scene and if *
     *          so the member variable m_scenePosPress is set according to the position of the parameter event.                                     *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event on the Battle Map scene.                                                                *
     *                                                                                                                                              *
     * \details This function handles a mouse release event on the Battle Map scene and checks whether the mouse release event is positioned at the *
     *          Battle Map scene and if so the member variable m_scenePosRelease is set according to the position of the parameter event.           *
     *                                                                                                                                              *
     * \param   event                         Mouse release event to be handled                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief This is the position of the cursor while the mouse press event.
     */
    QPointF m_scenePosPress;

    /*!
     * \brief This is the position of the cursor while the mouse release event.
     */
    QPointF m_scenePosRelease;

signals: /* - */

private slots: /* - */

private: /* - */
};

#endif // BATTLEMAPSCENE_H
