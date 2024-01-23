/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "customgraphicsview.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class CustomGraphicsView.
 */
CustomGraphicsView::CustomGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    m_eventProcessingEnabled(false),
    m_scaleFactor(1.0),
    m_dragModeEnabled(false),
    m_cursor(Qt::ArrowCursor),
    m_scenePosCenter(QPointF()),
    m_viewPosPress(QPoint())
{
}

/*!
 * \brief This function is the destructor of the class CustomGraphicsView.
 */
CustomGraphicsView::~CustomGraphicsView()
{
}

/*!
 * \brief This function returns the value of the member variable m_eventProcessingEnabled.
 */
bool CustomGraphicsView::getEventProcessingEnabled() const
{
    return m_eventProcessingEnabled;
}

/*!
 * \brief This function sets the value of the member variable m_eventProcessingEnabled.
 */
void CustomGraphicsView::setEventProcessingEnabled(bool eventProcessingEnabled)
{
    m_eventProcessingEnabled = eventProcessingEnabled;
}

/*!
 * \brief This function resets the scaling and the scale factor.
 */
void CustomGraphicsView::resetScaling()
{
    /* reset scaling of graphics view and scale factor */
    scale(1 / m_scaleFactor, 1 / m_scaleFactor);
    m_scaleFactor = 1.0;

    /* emit signal for changed scale factor */
    emit changedScaleFactor(m_scaleFactor);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse wheel event.
 */
void CustomGraphicsView::wheelEvent(QWheelEvent *event)
{
    /* mouse wheel event is only processed if event processing is enabled */
    if (m_eventProcessingEnabled)
    {
        setTransformationAnchor(AnchorUnderMouse);

        /* reset scaling */
        scale(1 / m_scaleFactor, 1 / m_scaleFactor);

        /* increment or decrement scale factor by 10 percent, depending on scrolling direction */
        if (0 < event->angleDelta().y())
        {
            if (BATTLEMAPVIEW_SCALEFACTOR_MAXVALUE_PERCENTAGE > static_cast<quint32>(m_scaleFactor * HUNDRED_PERCENTAGE))
            {
                m_scaleFactor = m_scaleFactor + BATTLEMAPVIEW_SCALEFACTOR_STEPSIZE;
            }
        }
        else
        {
            if (BATTLEMAPVIEW_SCALEFACTOR_MINVALUE_PERCENTAGE < static_cast<quint32>(m_scaleFactor * HUNDRED_PERCENTAGE))
            {
                m_scaleFactor = m_scaleFactor - BATTLEMAPVIEW_SCALEFACTOR_STEPSIZE;
            }
        }

        /* rescale graphics view with changed scale factor */
        scale(m_scaleFactor, m_scaleFactor);

        /* emit signal for changed scale factor */
        emit changedScaleFactor(m_scaleFactor);
    }
}

/*!
 * \brief This function handles a mouse press event.
 */
void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    /* mouse press event is only processed if event processing is enabled */
    if (m_eventProcessingEnabled)
    {
        /* enable drag mode in case of pressed middle button */
        if (Qt::MiddleButton == event->button())
        {
            m_dragModeEnabled = true;

            /* set cursor according to drag mode */
            m_cursor = viewport()->cursor();
            viewport()->setCursor(Qt::SizeAllCursor);

            /* save positions of current viewport center and mouse press for later processing */
            m_scenePosCenter = mapToScene(viewport()->rect().center());
            m_viewPosPress = event->pos();
        }

        /* emit respective signal in case of pressed right button */
        if (Qt::RightButton == event->button())
        {
            emit pressedRightMouseButton(event->pos());
        }

        /* call base class function in order to forward event to Battle Map scene */
        QGraphicsView::mousePressEvent(event);
    }
}

/*!
 * \brief This function handles a mouse move event.
 */
void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    /* mouse move event is only processed if event processing is enabled */
    if (m_eventProcessingEnabled)
    {
        if (m_dragModeEnabled)
        {
            /* center graphics view on new position, calculated from viewport center position while mouse press, mouse press position and mouse move position */
            centerOn(m_scenePosCenter - (event->pos() - m_viewPosPress) * (1 / m_scaleFactor));
        }

        /* call base class function in order to forward event to Battle Map scene */
        QGraphicsView::mouseMoveEvent(event);
    }
}

/*!
 * \brief This function handles a mouse release event.
 */
void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    /* mouse release event is only processed if event processing is enabled */
    if (m_eventProcessingEnabled)
    {
        /* disable drag mode in case of pressed middle button */
        if (Qt::MiddleButton == event->button())
        {
            m_dragModeEnabled = false;

            /* reset cursor */
            viewport()->setCursor(m_cursor);
        }

        /* call base class function in order to forward event to Battle Map scene */
        QGraphicsView::mouseReleaseEvent(event);
    }
}

/*!
 * \brief This function handles a key press event.
 */
void CustomGraphicsView::keyPressEvent(QKeyEvent *event)
{
    /* key press event is only processed if event processing is enabled */
    if (m_eventProcessingEnabled)
    {
        /* emit signal for pressed key */
        emit pressedKey(static_cast<Qt::Key>(event->key()));
    }
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
