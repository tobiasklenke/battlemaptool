#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

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
 * \brief This class implements the functionality of a custom graphics view.
 */
class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class CustomGraphicsView.                                                                   *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   parent                        Parent of the class CustomGraphicsView                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    CustomGraphicsView(QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class CustomGraphicsView.                                                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~CustomGraphicsView();

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
     * \brief   This function resets the scaling and the scale factor.                                                                              *
     *                                                                                                                                              *
     * \details This function resets the scaling and the scale factor and emits the signal for a changed scale factor.                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void resetScaling();

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse wheel event.                                                                                          *
     *                                                                                                                                              *
     * \details This function processes a mouse wheel event, but only if the event processing is enabled. It sets the transformation anchor under   *
     *          the mouse and resets the scaling. Afterwards, it increments or decrements the scale factor by 10 percent, depending on the          *
     *          scrolling direction, rescales the graphics view with the changed scale factor and emits the signal for a changed scale factor.      *
     *                                                                                                                                              *
     * \param   event                         Mouse wheel event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void wheelEvent(QWheelEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse press event.                                                                                          *
     *                                                                                                                                              *
     * \details This function processes a mouse press event, but only if the event processing is enabled. In case that the middle button has been   *
     *          pressed, it enables the drag mode, sets the cursor accordingly and saves the positions of the current viewport center and the mouse *
     *          press for later processing. In case that the right button has been pressed, it emits the respective signal. Finally, it calls the   *
     *          base class function in order to forward the event to the Battle Map scene.                                                          *
     *                                                                                                                                              *
     * \param   event                         Mouse press event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mousePressEvent(QMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse move event.                                                                                           *
     *                                                                                                                                              *
     * \details This function processes a mouse move event, but only if the event processing is enabled. If the drag mode is enabled, it centers    *
     *          the graphics view on the new position, calculated from the viewport center position while the mouse press, the mouse press position *
     *          and the mouse move position. Finally, it calls the base class function in order to forward the event to the Battle Map scene.       *
     *                                                                                                                                              *
     * \param   event                         Mouse move event to be handled                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseMoveEvent(QMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse release event.                                                                                        *
     *                                                                                                                                              *
     * \details This function processes a mouse release event, but only if the event processing is enabled. In case that the middle button has been *
     *          pressed, it disables the drag mode and resets the cursor. Finally, it calls the base class function in order to forward the event   *
     *          to the Battle Map scene.                                                                                                            *
     *                                                                                                                                              *
     * \param   event                         Mouse release event to be handled                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void mouseReleaseEvent(QMouseEvent *event);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a key press event.                                                                                            *
     *                                                                                                                                              *
     * \details This function processes a key press event, but only if the event processing is enabled. It emits the signal for a pressed key.      *
     *                                                                                                                                              *
     * \param   event                         Key press event to be handled                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void keyPressEvent(QKeyEvent *event);

signals:

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as the scale factor of the graphics view changes.                                                      *
     ************************************************************************************************************************************************/
    void changedScaleFactor(qreal m_scaleFactor);

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as a key is pressed.                                                                                   *
     ************************************************************************************************************************************************/
    void pressedKey(Qt::Key key);

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as the right mouse button is pressed.                                                                  *
     ************************************************************************************************************************************************/
    void pressedRightMouseButton(QPoint position);

private slots: /* - */

private:

    /*!
     * \brief This is the information if the event processing is enabled.
     */
    bool m_eventProcessingEnabled;

    /*!
     * \brief This is the factor that is used for scaling the graphics view while scrolling.
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

#endif // CUSTOMGRAPHICSVIEW_H
