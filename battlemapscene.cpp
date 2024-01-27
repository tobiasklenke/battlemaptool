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

/*!
 * \brief This function checks the mouse event scene position for validity.
 */
bool BattleMapScene::checkMouseEventScenePos(QGraphicsSceneMouseEvent *event)
{
    /* check whether mouse event is positioned at Battle Map scene */
    return ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) && (0 <= event->scenePos().y()) && (event->scenePos().y() <= this->height()));
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse press event.
 */
void BattleMapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        /* reset positions of mouse press and mouse release */
        m_scenePosPress = QPointF();
        m_scenePosRelease = QPointF();

        /* check whether mouse press event is positioned at Battle Map scene */
        if (checkMouseEventScenePos(event))
        {
            /* save position of mouse press for later processing */
            m_scenePosPress = event->scenePos();
        }
    }
}

/*!
 * \brief This function handles a mouse release event.
 */
void BattleMapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        /* check whether mouse release event is positioned at Battle Map scene */
        if (checkMouseEventScenePos(event))
        {
            if (!m_scenePosPress.isNull())
            {
                /* save position of mouse release for later processing */
                m_scenePosRelease = event->scenePos();
            }
        }
        else
        {
            /* reset positions of mouse press and mouse release */
            m_scenePosPress = QPointF();
            m_scenePosRelease = QPointF();
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
