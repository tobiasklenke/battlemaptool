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
BattleMapScene::BattleMapScene(QObject *parent) :
    QGraphicsScene(parent),
    pBattleMapSquareToDraw(new QGraphicsRectItem),
    m_battleMapLinesToDraw(QVector<QGraphicsLineItem*>()),
    m_scenePosPress(QPointF()),
    m_scenePosRelease(QPointF())

{
    qDebug() << "..." << __func__;
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

        pBattleMapSquareToDraw->setRect(topLeft.rx(), topLeft.ry(), (bottomRight - topLeft).rx(), (bottomRight - topLeft).ry());
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

/*!
 * \brief This function draws a Battle Map line.
 */
void BattleMapScene::drawBattleMapLine(QLineF battleMapLine)
{
    //qDebug() << "..." << __func__;

    QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem();

    m_battleMapLinesToDraw.append(battleMapLineToDraw);

    this->addItem(m_battleMapLinesToDraw.last());
    m_battleMapLinesToDraw.last()->setLine(battleMapLine);
    m_battleMapLinesToDraw.last()->setPen(QPen(Qt::black, 3, Qt::DashLine));
}

/*!
 * \brief This function removes all Battle Map lines.
 */
void BattleMapScene::removeBattleMapLines()
{
    qDebug() << "..." << __func__;

    for(qint32 lineIdx = 0; lineIdx < m_battleMapLinesToDraw.count(); lineIdx++)
    {
        m_battleMapLinesToDraw.at(lineIdx)->setLine(0, 0, 0, 0);
        this->removeItem(m_battleMapLinesToDraw.at(lineIdx));
    }

    m_battleMapLinesToDraw.clear();
}
