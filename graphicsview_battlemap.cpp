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
    m_scaleFactor(1.0)
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

    if (0 < event->angleDelta().y())
    {
        if (200U > static_cast<quint32>(m_scaleFactor * 100))
        {
            m_scaleFactor = m_scaleFactor + 0.1;
        }
    }
    else
    {
        if (10U < static_cast<quint32>(m_scaleFactor * 100))
        {
            m_scaleFactor = m_scaleFactor - 0.1;
        }
    }

    scale(m_scaleFactor, m_scaleFactor);

    emit changed_ScaleFactor(m_scaleFactor);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
