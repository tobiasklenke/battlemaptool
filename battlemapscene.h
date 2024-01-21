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
 * \brief This class implements the base functionality needed for a custom graphics scene for display of Battle Map images.
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

    /*! *********************************************************************************************************************************************
     * \brief   This function checks the mouse event scene position for validity.                                                                   *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   event                         Mouse event to be checked                                                                             *
     *                                                                                                                                              *
     * \return  This function returns true if the mouse event is positioned on the Battle Map scene. Otherwise, it returns false.                   *
     ************************************************************************************************************************************************/
    bool checkMouseEventScenePos(QGraphicsSceneMouseEvent *event);

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event.                                                                                          *
     *                                                                                                                                              *
     * \details This function handles a mouse press event. In case that the left button has been pressed, it resets the positions of the mouse      *
     *          press and the mouse release. Afterwards, it checks whether the mouse press event is positioned at the Battle Map scene and if so,   *
	 *          it saves the position of the mouse press for later processing.                                                                      *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event.                                                                                        *
     *                                                                                                                                              *
     * \details This function handles a mouse release event. In case that the left button has been released, it checks whether the mouse release    *
     *          event is positioned at the Battle Map scene and if so, it saves the position of the mouse release for later processing.             *
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
