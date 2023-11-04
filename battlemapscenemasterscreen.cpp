/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapscenemasterscreen.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapSceneMasterScreen.
 */
BattleMapSceneMasterScreen::BattleMapSceneMasterScreen(QObject *parent) :
    BattleMapScene(parent),
    m_scaleFactor(1.0)
{
}

/*!
 * \brief This function is the destructor of the class BattleMapSceneMasterScreen
 */
BattleMapSceneMasterScreen::~BattleMapSceneMasterScreen()
{
}

/*!
 * \brief This function updates the member variable m_scaleFactor and the pen properties.
 */
void BattleMapSceneMasterScreen::changed_ScaleFactor(qreal scaleFactor)
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
void BattleMapSceneMasterScreen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        BattleMapScene::mousePressEvent(event);

        /* check whether the mouse press event is positioned at the Battle Map scene */
        if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) &&
                (0 <= event->scenePos().y()) && (event->scenePos().y() <= this->height()))
        {
            addItem(&m_battleMapSelectionSquareToDraw);
            m_battleMapSelectionSquareToDraw.setPen(QPen(BATTLEMAPSELECTIONSQUARE_COLOR, BATTLEMAPSELECTIONSQUARE_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine));
        }
    }
}

/*!
 * \brief This function handles a mouse move event on the Battle Map scene.
 */
void BattleMapSceneMasterScreen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
void BattleMapSceneMasterScreen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        /* check whether the mouse release event is positioned at the Battle Map scene */
        if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) &&
                (0 <= event->scenePos().y()) && (event->scenePos().y() <= this->height()))
        {
            m_battleMapSelectionSquareToDraw.setRect(0, 0, 0, 0);
            removeItem(&m_battleMapSelectionSquareToDraw);

            BattleMapScene::mouseReleaseEvent(event);

            emit selected_BattleMapSquares();
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
