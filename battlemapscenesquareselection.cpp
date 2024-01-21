/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapscenesquareselection.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapSceneSquareSelection.
 */
BattleMapSceneSquareSelection::BattleMapSceneSquareSelection(QObject *parent) :
    BattleMapScene(parent),
    m_scaleFactor(1.0)
{
}

/*!
 * \brief This function is the destructor of the class BattleMapSceneSquareSelection
 */
BattleMapSceneSquareSelection::~BattleMapSceneSquareSelection()
{
}

/*!
 * \brief This function updates the member variable m_scaleFactor and the pen properties.
 */
void BattleMapSceneSquareSelection::changedScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;

    /* set pen properties with updated scale factor */
    m_battleMapSelectionRectToDraw.setPen(QPen(Qt::black, BATTLEMAPSELECTIONRECT_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine));
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse press event.
 */
void BattleMapSceneSquareSelection::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        /* call base class function in order to set press position */
        BattleMapScene::mousePressEvent(event);

        /* check whether mouse press event is positioned at Battle Map scene */
        if (checkMouseEventScenePos(event))
        {
            /* add selection rectangle to Battle Map scene and set pen properties */
            addItem(&m_battleMapSelectionRectToDraw);
            m_battleMapSelectionRectToDraw.setPen(QPen(BATTLEMAPSELECTIONRECT_COLOR, BATTLEMAPSELECTIONRECT_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine));
        }
    }
}

/*!
 * \brief This function handles a mouse move event.
 */
void BattleMapSceneSquareSelection::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_scenePosPress.isNull() && m_scenePosRelease.isNull())
    {
        /* determine corners of selection rectangle built from mouse press event and mouse move event positions */
        QPointF topLeft = QPointF(qMin(m_scenePosPress.rx(), event->scenePos().rx()), qMin(m_scenePosPress.y(), event->scenePos().ry()));
        QPointF bottomRight = QPointF(qMax(m_scenePosPress.rx(), event->scenePos().rx()), qMax(m_scenePosPress.y(), event->scenePos().ry()));

        /* update selection rectangle */
        m_battleMapSelectionRectToDraw.setRect(topLeft.rx(), topLeft.ry(), (bottomRight - topLeft).rx(), (bottomRight - topLeft).ry());
    }
}

/*!
 * \brief This function handles a mouse release event.
 */
void BattleMapSceneSquareSelection::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        if (!m_scenePosPress.isNull())
        {
            /* reset selection rectangle and remove it from Battle Map scene */
            m_battleMapSelectionRectToDraw.setRect(0, 0, 0, 0);
            removeItem(&m_battleMapSelectionRectToDraw);

            /* call base class function in order to set release position */
            BattleMapScene::mouseReleaseEvent(event);

            /* check whether mouse release event is positioned at Battle Map scene */
            if (checkMouseEventScenePos(event))
            {
                emit selectedBattleMapSquare();
            }
        }
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
