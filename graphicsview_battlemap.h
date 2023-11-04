#ifndef GRAPHICSVIEW_BATTLEMAP_H
#define GRAPHICSVIEW_BATTLEMAP_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

#include "defines.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the custom functionality of a Battle Map view.
 */
class GraphicsView_BattleMap : public QGraphicsView
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class GraphicsView_BattleMap.                                                               *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    GraphicsView_BattleMap(QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class GraphicsView_BattleMap.                                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~GraphicsView_BattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_eventProcessingEnabled.                                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_eventProcessingEnabled.                                                    *
     ************************************************************************************************************************************************/
    bool getEventProcessingEnabled() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_eventProcessingEnabled.                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   eventProcessingEnabled        Information whether the event processing shall be enabled                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setEventProcessingEnabled(bool eventProcessingEnabled);

    /*! *********************************************************************************************************************************************
     * \brief   This function resets the scaling.                                                                                                   *
     *                                                                                                                                              *
     * \details This function scales the view to the original size, resets the scale factor and emits the signal that the scale factor has been     *
     *          changed.                                                                                                                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void resetScaling();

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse wheel event on the Battle Map view.                                                                   *
     *                                                                                                                                              *
     * \details This function handles a mouse wheel event on the Battle Map view by incrementing or decrementing the scale factor by 10 percent,    *
     *          depending on the scrolling direction. The scale factor can take values in the range of 10 percent to 200 percent. Afterwards, the   *
     *          function emits the signal that the scale factor has been changed.                                                                   *
     *                                                                                                                                              *
     * \param   event                         Mouse wheel event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void wheelEvent(QWheelEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event on the Battle Map view.                                                                   *
     *                                                                                                                                              *
     * \details This function handles a mouse press event on the Battle Map view by enabling the drag mode, saving the current cursor in the member *
     *          variable m_cursor and changing it. Afterwards, the member variable m_scenePosCenter is set according to the current position of the *
     *          Battle Map scene center and the member variable m_viewPosPress is set according to the position of the parameter event. If the      *
     *          event button is the right mouse button, the function emits the signal clicked_RightMouseButton. Finally, the event is forwarded to  *
     *          the Battle Map scene by calling the base class implementation of the function mousePressEvent().                                    *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse move event on the Battle Map view.                                                                    *
     *                                                                                                                                              *
     * \details This function handles a mouse move event on the Battle Map view by centering the Battle Map view on the new position of the Battle  *
     *          Map scene center, resulting from the previous position of the Battle Map scene center from the member variable m_scenePosCenter and *
     *          the vector from the previous position from the member variable m_viewPosPress to the new position of the parameter event. Finally,  *
     *          the event is forwarded to the Battle Map scene by calling the base class implementation of the function mouseMoveEvent().           *
     *                                                                                                                                              *
     * \param   event                         Mouse move event to be handled                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseMoveEvent(QMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event on the Battle Map view.                                                                 *
     *                                                                                                                                              *
     * \details This function handles a mouse release event on the Battle Map view by disabling the drag mode and resetting the cursor to the       *
     *          previously saved cursor from the member variable m_cursor. Finally, the event is forwarded to the Battle Map scene by calling the   *
	 *          base class implementation of the function mouseReleaseEvent().                                                                      *
     *                                                                                                                                              *
     * \param   event                         Mouse release event to be handled                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseReleaseEvent(QMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a key press event on the Battle Map view.                                                                     *
     *                                                                                                                                              *
     * \details This function emits the signal pressed_Key.                                                                                         *
     *                                                                                                                                              *
     * \param   event                         Key press event to be handled                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void keyPressEvent(QKeyEvent *event);

signals:

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as the scale factor of the Battle Map view changes.                                                    *
     ************************************************************************************************************************************************/
    void changed_ScaleFactor(qreal m_scaleFactor);

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as a key is pressed.                                                                                   *
     ************************************************************************************************************************************************/
    void pressed_Key(Qt::Key key);

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as the right mouse button is pressed.                                                                  *
     ************************************************************************************************************************************************/
    void clicked_RightMouseButton(QPoint position);

private slots: /* - */

private:

    /*!
     * \brief This is the information if the event processing is enabled.
     */
    bool m_eventProcessingEnabled;

    /*!
     * \brief This is the factor that is used for scaling the Battle Map view while scrolling.
     */
    qreal m_scaleFactor;

    /*!
     * \brief This is the information if the drag mode is enabled.
     */
    bool m_dragModeEnabled;

    /*!
     * \brief This is the cursor to be reset after the drag mode has been disabled.
     */
    QCursor m_cursor;

    /*!
     * \brief This is the position of the scene center while the mouse press event.
     */
    QPointF m_scenePosCenter;

    /*!
     * \brief This is the position of the cursor while the mouse press event.
     */
    QPoint m_viewPosPress;
};

#endif // GRAPHICSVIEW_BATTLEMAP_H
