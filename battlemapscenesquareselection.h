#ifndef BATTLEMAPSCENESQUARESELECTION_H
#define BATTLEMAPSCENESQUARESELECTION_H

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
 * \brief This class implements the functionality needed for the selection of a Battle Map square.
 */
class BattleMapSceneSquareSelection : public BattleMapScene
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class BattleMapSceneSquareSelection.                                                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   scaleFactor                   Pointer to the scale factor                                                                           *
     * \param   parent                        Parent of the class BattleMapSceneSquareSelection                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMapSceneSquareSelection(qreal *scaleFactor, QObject *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMapSceneSquareSelection.                                                         *
     *                                                                                                                                              *
     * \details This function deletes the object pointed to by pBattleMapSquareToDraw.                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMapSceneSquareSelection();

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event on the Battle Map scene.                                                                  *
     *                                                                                                                                              *
     * \details This function handles a mouse press event on the Battle Map scene by resetting the member variables m_scenePosPress and             *
     *          m_scenePosRelease first. Afterwards, the function checks whether the mouse press event is positioned at the Battle Map scene and if *
     *          so the member variable m_scenePosPress is set according to the position of the parameter event. Moreover, the function adds the     *
     *          member variable pBattleMapSquareToDraw to the Battle Map scene and sets the pen properties.                                         *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse move event on the Battle Map scene.                                                                   *
     *                                                                                                                                              *
     * \details This function handles a mouse move event on the Battle Map scene and checks whether the mouse press event has already been handled  *
     *          while the mouse release event has not been handled. If so, the coordinates of the top left and the bottom right corners of the      *
     *          square that is built from the previous mouse press event position and the mouse move event position are determined. Afterwards, the *
     *          function sets the rectangle of the member variable pBattleMapSquareToDraw according to the determined corners.                      *
     *                                                                                                                                              *
     * \param   event                         Mouse move event to be handled                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event on the Battle Map scene.                                                                *
     *                                                                                                                                              *
     * \details This function handles a mouse release event on the Battle Map scene and resets the member variable pBattleMapSquareToDraw and       *
     *          removes it from the Battle Map scene. Afterwards, the function checks whether the mouse release event is positioned at the Battle   *
     *          Map scene and if so the member variable m_scenePosRelease is set according to the position of the parameter event. Moreover, the    *
     *          function emits the signal that a Battle Map square has been selected.                                                               *
     *                                                                                                                                              *
     * \param   event                         Mouse release event to be handled                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as a Battle Map square has been selected.                                                              *
     ************************************************************************************************************************************************/
    void selected_BattleMapSquare(void);

private slots: /* - */

private:

    /*!
     * \brief This is the rectangle to be drawn while the selection of the Battle Map square.
     */
    QGraphicsRectItem  m_battleMapSquareToDraw;

    /*!
     * \brief This is a pointer to the factor that is used for scaling the Battle Map view while scrolling.
     */
    qreal *pScaleFactor;
};

#endif // BATTLEMAPSCENESQUARESELECTION_H
