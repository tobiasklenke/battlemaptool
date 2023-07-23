/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "battlemapscene.h"

/****************************************************************************************************************************************************
 * Definition of Public Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapScene.
 */
BattleMapScene::BattleMapScene(QObject *parent) :
    QGraphicsScene(parent),
    pBattleMapSquareToDraw(new QGraphicsRectItem),
    m_battleMapLinesToDraw(QList<QGraphicsLineItem*>()),
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
 * \brief This function returns the value of the member variable m_battleMapLinesToDraw.
 */
QList<QGraphicsLineItem*> BattleMapScene::getBattleMapLinesToDraw() const
{
    qDebug() << "..." << __func__;
    return m_battleMapLinesToDraw;
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
void BattleMapScene::drawBattleMapLine(QLineF battleMapLine, QPen pen)
{
    //qDebug() << "..." << __func__;

    QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem();

    m_battleMapLinesToDraw.append(battleMapLineToDraw);

    this->addItem(m_battleMapLinesToDraw.last());
    m_battleMapLinesToDraw.last()->setLine(battleMapLine);
    m_battleMapLinesToDraw.last()->setPen(pen);
}

/*!
 * \brief This function removes all Battle Map lines.
 */
void BattleMapScene::removeBattleMapLines()
{
    qDebug() << "..." << __func__;

    for(quint32 lineIdx = 0U; lineIdx < m_battleMapLinesToDraw.count(); lineIdx++)
    {
        this->removeItem(m_battleMapLinesToDraw.at(lineIdx));
        delete m_battleMapLinesToDraw.at(lineIdx);
    }

    m_battleMapLinesToDraw.clear();
}

/****************************************************************************************************************************************************
 * Definition of Protected Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse press event on BattleMapScene.
 */
void BattleMapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "..." << __func__;

    /* Set press position and reset release position */
    m_scenePosPress = event->scenePos();
    m_scenePosRelease = QPointF();

    this->addItem(pBattleMapSquareToDraw);
    pBattleMapSquareToDraw->setPen(QPen(Qt::black, 3, Qt::DashLine));
}

/*!
 * \brief This function handles a mouse move event on BattleMapScene.
 */
void BattleMapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "..." << __func__;

    if (!m_scenePosPress.isNull() && m_scenePosRelease.isNull())
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

/****************************************************************************************************************************************************
 * Definition of Private Slot Functions
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * Definition of Private Functions
 ****************************************************************************************************************************************************/

/* - */
