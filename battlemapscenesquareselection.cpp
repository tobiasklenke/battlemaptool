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
void BattleMapSceneSquareSelection::changed_ScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;

    m_battleMapSelectionSquareToDraw.setPen(QPen(Qt::black, BATTLEMAPSELECTIONSQUARE_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine));
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse press event on the Battle Map scene.
 */
void BattleMapSceneSquareSelection::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        /* call function of base class in order to set press position */
        BattleMapScene::mousePressEvent(event);

        /* check whether the mouse press event is positioned at the Battle Map scene */
        if (checkMouseEventScenePos(event))
        {
            addItem(&m_battleMapSelectionSquareToDraw);
            m_battleMapSelectionSquareToDraw.setPen(QPen(BATTLEMAPSELECTIONSQUARE_COLOR, BATTLEMAPSELECTIONSQUARE_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine));
        }
    }
}

/*!
 * \brief This function handles a mouse move event on the Battle Map scene.
 */
void BattleMapSceneSquareSelection::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_scenePosPress.isNull() && m_scenePosRelease.isNull())
    {
        /* determine corners of the square built from mouse press event and mouse move event positions */
        QPointF topLeft = QPointF(qMin(m_scenePosPress.rx(), event->scenePos().rx()), qMin(m_scenePosPress.y(), event->scenePos().ry()));
        QPointF bottomRight = QPointF(qMax(m_scenePosPress.rx(), event->scenePos().rx()), qMax(m_scenePosPress.y(), event->scenePos().ry()));

        m_battleMapSelectionSquareToDraw.setRect(topLeft.rx(), topLeft.ry(), (bottomRight - topLeft).rx(), (bottomRight - topLeft).ry());
    }
}

/*!
 * \brief This function handles a mouse release event on the Battle Map scene.
 */
void BattleMapSceneSquareSelection::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        if (!m_scenePosPress.isNull())
        {
            m_battleMapSelectionSquareToDraw.setRect(0, 0, 0, 0);
            removeItem(&m_battleMapSelectionSquareToDraw);

            /* call function of base class in order to set release position */
            BattleMapScene::mouseReleaseEvent(event);

            /* check whether the mouse release event is positioned at the Battle Map scene */
            if (checkMouseEventScenePos(event))
            {
                emit selected_BattleMapSquare();
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
