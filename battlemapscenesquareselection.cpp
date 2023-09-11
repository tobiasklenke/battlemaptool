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
 * \brief This function updates the member variable m_scaleFactor and updated the pen properties.
 */
void BattleMapSceneSquareSelection::changed_ScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;

    m_battleMapSquareToDraw.setPen(QPen(Qt::black, BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine));
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
        BattleMapScene::mousePressEvent(event);

        /* check whether the mouse press event is positioned at the Battle Map scene */
        if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) &&
                (0 <= event->scenePos().y()) && (event->scenePos().y() <= this->height()))
        {
            addItem(&m_battleMapSquareToDraw);
            m_battleMapSquareToDraw.setPen(QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine));
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

        m_battleMapSquareToDraw.setRect(topLeft.rx(), topLeft.ry(), (bottomRight - topLeft).rx(), (bottomRight - topLeft).ry());
    }
}

/*!
 * \brief This function handles a mouse release event on the Battle Map scene.
 */
void BattleMapSceneSquareSelection::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        m_battleMapSquareToDraw.setRect(0, 0, 0, 0);
        removeItem(&m_battleMapSquareToDraw);

        BattleMapScene::mouseReleaseEvent(event);

        /* check whether the mouse release event is positioned at the Battle Map scene */
        if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) &&
                (0 <= event->scenePos().y()) && (event->scenePos().y() <= this->height()))
        {
            emit selected_BattleMapSquare();
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
