/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "battlemapscene.h"

/****************************************************************************************************************************************************
 * Member Function Definition
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapScene.
 */
BattleMapScene::BattleMapScene(QObject *parent) : QGraphicsScene{parent}
{
    qDebug() << "..." << __func__;

    pBattleMapSquareToDraw = new QGraphicsRectItem();
}

/*!
 * \brief This function is the destructor of the class BattleMapScene.
 */
BattleMapScene::~BattleMapScene()
{
    qDebug() << "..." << __func__;

    delete pBattleMapSquareToDraw;
}

/*!
 * \brief This function handles a mouse press event on BattleMapScene.
 */
void BattleMapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "..." << __func__;

    /* Reset press and release positions */
    m_scenePosPress = QPointF();
    m_scenePosRelease = QPointF();

    m_scenePosPress = event->scenePos();

    this->addItem(pBattleMapSquareToDraw);
    pBattleMapSquareToDraw->setPen(QPen(Qt::black, 3, Qt::DashLine));
}

/*!
 * \brief This function handles a mouse move event on BattleMapScene.
 */
void BattleMapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "..." << __func__;

    if (m_scenePosRelease.isNull())
    {
        QPointF topLeft = QPointF(qMin(m_scenePosPress.rx(), event->scenePos().rx()), qMin(m_scenePosPress.y(), event->scenePos().ry()));
        QPointF bottomRight = QPointF(qMax(m_scenePosPress.rx(), event->scenePos().rx()), qMax(m_scenePosPress.y(), event->scenePos().ry()));

        pBattleMapSquareToDraw->setPos(topLeft);
        pBattleMapSquareToDraw->setRect(0, 0, (bottomRight - topLeft).rx(), (bottomRight - topLeft).ry());
    }
}

/*!
 * \brief This function handles a mouse release event on BattleMapScene.
 */
void BattleMapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "..." << __func__;

    m_scenePosRelease = event->scenePos();

    pBattleMapSquareToDraw->setRect(0, 0, 0, 0);
    this->removeItem(pBattleMapSquareToDraw);

    emit selected_BattleMapSquare();
}

/*!
 * \brief This function returns the value of the member variable scenePosPress.
 */
QPointF BattleMapScene::getScenePosPress() const
{
    qDebug() << "..." << __func__;
    return m_scenePosPress;
}

/*!
 * \brief This function sets the value of the member variable scenePosPress.
 */
void BattleMapScene::setScenePosPress(QPointF newScenePosPress)
{
    qDebug() << "..." << __func__;
    m_scenePosPress = newScenePosPress;
}

/*!
 * \brief This function returns the value of the member variable scenePosRelease.
 */
QPointF BattleMapScene::getScenePosRelease() const
{
    qDebug() << "..." << __func__;
    return m_scenePosRelease;
}

/*!
 * \brief This function sets the value of the member variable scenePosRelease.
 */
void BattleMapScene::setScenePosRelease(QPointF newScenePosRelease)
{
    qDebug() << "..." << __func__;
    m_scenePosRelease = newScenePosRelease;
}
