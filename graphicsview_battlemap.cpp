/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "graphicsview_battlemap.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class GraphicsView_BattleMap.
 */
GraphicsView_BattleMap::GraphicsView_BattleMap(QWidget *parent) :
    QGraphicsView(parent),
    m_scaleFactor(1.0),
    m_dragModeEnabled(false),
    m_cursor(Qt::ArrowCursor),
    m_scenePosCenter(QPointF()),
    m_viewPosPress(QPoint())
{
}

/*!
 * \brief This function is the destructor of the class GraphicsView_BattleMap.
 */
GraphicsView_BattleMap::~GraphicsView_BattleMap()
{
}

/*!
 * \brief This function resets the scaling.
 */
void GraphicsView_BattleMap::resetScaling()
{
    scale(1 / m_scaleFactor, 1 / m_scaleFactor);

    m_scaleFactor = 1.0;

    emit changed_ScaleFactor(m_scaleFactor);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse wheel event on the Battle Map view.
 */
void GraphicsView_BattleMap::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(AnchorUnderMouse);

    scale(1 / m_scaleFactor, 1 / m_scaleFactor);

    /* incrementing or decrementing the scale factor by 10 percent, depending on the scrolling direction */
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

    scale(m_scaleFactor, m_scaleFactor);

    emit changed_ScaleFactor(m_scaleFactor);
}

/*!
 * \brief This function handles a mouse press event on the Battle Map view.
 */
void GraphicsView_BattleMap::mousePressEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button())
    {
        m_dragModeEnabled = true;

        m_cursor = viewport()->cursor();
        viewport()->setCursor(Qt::SizeAllCursor);

        m_scenePosCenter = mapToScene(viewport()->rect().center());
        m_viewPosPress = event->pos();
    }

    QGraphicsView::mousePressEvent(event);
}

/*!
 * \brief This function handles a mouse move event on the Battle Map view.
 */
void GraphicsView_BattleMap::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragModeEnabled)
    {
        centerOn(m_scenePosCenter - (event->pos() - m_viewPosPress) * (1 / m_scaleFactor));
    }

    QGraphicsView::mouseMoveEvent(event);
}

/*!
 * \brief This function handles a mouse release event on the Battle Map view.
 */
void GraphicsView_BattleMap::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button())
    {
        m_dragModeEnabled = false;

        viewport()->setCursor(m_cursor);
    }

    QGraphicsView::mouseReleaseEvent(event);
}

/*!
 * \brief This function handles a key press event on the Battle Map view.
 */
void GraphicsView_BattleMap::keyPressEvent(QKeyEvent *event)
{
    emit pressed_Key(static_cast<Qt::Key>(event->key()));
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
