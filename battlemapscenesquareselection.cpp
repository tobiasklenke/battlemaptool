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
    pBattleMapSquareToDraw(new QGraphicsRectItem),
    m_battleMapLinesToDraw(QList<QGraphicsLineItem*>())
{
}

/*!
 * \brief This function is the destructor of the class BattleMapSceneSquareSelection
 */
BattleMapSceneSquareSelection::~BattleMapSceneSquareSelection()
{
    delete pBattleMapSquareToDraw;
}

/*!
 * \brief This function returns the value of the member variable m_battleMapLinesToDraw.
 */
QList<QGraphicsLineItem*> BattleMapSceneSquareSelection::getBattleMapLinesToDraw() const
{
    return m_battleMapLinesToDraw;
}

/*!
 * \brief This function draws a Battle Map line.
 */
void BattleMapSceneSquareSelection::drawBattleMapLine(QLineF battleMapLine, QPen pen)
{
    QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(battleMapLine);

    m_battleMapLinesToDraw.append(battleMapLineToDraw);

    this->addItem(m_battleMapLinesToDraw.last());
    m_battleMapLinesToDraw.last()->setPen(pen);
}

/*!
 * \brief This function removes all Battle Map lines.
 */
void BattleMapSceneSquareSelection::removeBattleMapLines()
{
    for(quint32 lineIdx = 0U; lineIdx < m_battleMapLinesToDraw.count(); lineIdx++)
    {
        this->removeItem(m_battleMapLinesToDraw.at(lineIdx));
        delete m_battleMapLinesToDraw.at(lineIdx);
    }

    m_battleMapLinesToDraw.clear();
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
        this->BattleMapScene::mousePressEvent(event);

        /* check whether the mouse press event is positioned at the Battle Map scene */
        if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) && (0 <= event->scenePos().y()) && (event->scenePos().x() <= this->height()))
        {
            this->addItem(pBattleMapSquareToDraw);
            pBattleMapSquareToDraw->setPen(QPen(Qt::black, 3, Qt::DotLine));
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

        pBattleMapSquareToDraw->setRect(topLeft.rx(), topLeft.ry(), (bottomRight - topLeft).rx(), (bottomRight - topLeft).ry());
    }
}

/*!
 * \brief This function handles a mouse release event on the Battle Map scene.
 */
void BattleMapSceneSquareSelection::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        pBattleMapSquareToDraw->setRect(0, 0, 0, 0);
        this->removeItem(pBattleMapSquareToDraw);

        this->BattleMapScene::mouseReleaseEvent(event);

        /* check whether the mouse release event is positioned at the Battle Map scene */
        if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) && (0 <= event->scenePos().y()) && (event->scenePos().x() <= this->height()))
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
