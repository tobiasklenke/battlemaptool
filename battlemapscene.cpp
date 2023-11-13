/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapscene.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapScene.
 */
BattleMapScene::BattleMapScene(QObject *parent) :
    QGraphicsScene(parent),
    m_scenePosPress(QPointF()),
    m_scenePosRelease(QPointF())
{
}

/*!
 * \brief This function is the destructor of the class BattleMapScene.
 */
BattleMapScene::~BattleMapScene()
{
}

/*!
 * \brief This function returns the value of the member variable m_scenePosPress.
 */
QPointF BattleMapScene::getScenePosPress() const
{
    return m_scenePosPress;
}

/*!
 * \brief This function returns the value of the member variable m_scenePosRelease.
 */
QPointF BattleMapScene::getScenePosRelease() const
{
    return m_scenePosRelease;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse press event on the Battle Map scene.
 */
void BattleMapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        /* reset press position and release position */
        m_scenePosPress = QPointF();
        m_scenePosRelease = QPointF();

        /* check whether the mouse press event is positioned at the Battle Map scene */
        if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) &&
                (0 <= event->scenePos().y()) && (event->scenePos().y() <= this->height()))
        {
            /* set press position */
            m_scenePosPress = event->scenePos();
        }
    }
}

/*!
 * \brief This function handles a mouse release event on the Battle Map scene.
 */
void BattleMapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        if (!m_scenePosPress.isNull())
        {
            /* check whether the mouse release event is positioned at the Battle Map scene */
            if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) &&
                    (0 <= event->scenePos().y()) && (event->scenePos().y() <= this->height()))
            {
                m_scenePosRelease = event->scenePos();
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
