/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapscene.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function is the constructor of the class BattleMapScene.                                                                           *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   parent                        Parent of the class BattleMapScene                                                                        *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
BattleMapScene::BattleMapScene(QObject *parent) :
    QGraphicsScene(parent),
    pBattleMapSquareToDraw(new QGraphicsRectItem),
    m_battleMapLinesToDraw(QList<QGraphicsLineItem*>()),
    m_scenePosPress(QPointF()),
    m_scenePosRelease(QPointF())

{
    qDebug() << "..." << __func__;
}

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class BattleMapScene.                                                                            *
 *                                                                                                                                                  *
 * \details This function deletes the object pointed to by pBattleMapSquareToDraw.                                                                  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
BattleMapScene::~BattleMapScene()
{
    qDebug() << "..." << __func__;

    delete pBattleMapSquareToDraw;
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_battleMapLinesToDraw.                                                          *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_battleMapLinesToDraw.                                                          *
 ****************************************************************************************************************************************************/
QList<QGraphicsLineItem*> BattleMapScene::getBattleMapLinesToDraw() const
{
    qDebug() << "..." << __func__;

    return m_battleMapLinesToDraw;
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_scenePosPress.                                                                 *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_scenePosPress.                                                                 *
 ****************************************************************************************************************************************************/
QPointF BattleMapScene::getScenePosPress() const
{
    qDebug() << "..." << __func__;

    return m_scenePosPress;
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_scenePosRelease.                                                               *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_scenePosRelease.                                                               *
 ****************************************************************************************************************************************************/
QPointF BattleMapScene::getScenePosRelease() const
{
    qDebug() << "..." << __func__;

    return m_scenePosRelease;
}

/*!**************************************************************************************************************************************************
 * \brief   This function draws a Battle Map line.                                                                                                  *
 *                                                                                                                                                  *
 * \details This function creates a graphics item from the parameter battleMapLine and appends it to the member variable m_battleMapLinesToDraw.    *
 *          Afterwards, the graphics item is added to the Battle Map scene and the pen properties are set according to the parameter pen.           *
 *                                                                                                                                                  *
 * \param   battleMapLine                 Battle Map line to be drawn                                                                               *
 * \param   pen                           Pen properties                                                                                            *
 *                                                                                                                                                  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void BattleMapScene::drawBattleMapLine(QLineF battleMapLine, QPen pen)
{
    //qDebug() << "..." << __func__;

    QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(battleMapLine);

    m_battleMapLinesToDraw.append(battleMapLineToDraw);

    this->addItem(m_battleMapLinesToDraw.last());
    m_battleMapLinesToDraw.last()->setPen(pen);
}

/*!**************************************************************************************************************************************************
 * \brief   This function removes all Battle Map lines.                                                                                             *
 *                                                                                                                                                  *
 * \details This function removes all Battle Map lines from the Battle Map scene and deletes them from the member variable m_battleMapLinesToDraw.  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
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
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function handles a mouse press event on the Battle Map scene.                                                                      *
 *                                                                                                                                                  *
 * \details This function handles a mouse press event on the Battle Map scene by resetting the member variables m_scenePosPress and                 *
 *          m_scenePosRelease first. Afterwards, the function checks whether the mouse press event is positioned at the Battle Map scene and if so  *
 *          the member variable m_scenePosPress is set according to the position of the parameter event. Moreover, the function adds the member     *
 *          variable pBattleMapSquareToDraw to the Battle Map scene and sets the pen properties.                                                    *
 *                                                                                                                                                  *
 * \param   event                         Mouse press event to be handled                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void BattleMapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "..." << __func__;

    /* reset press position and release position */
    m_scenePosPress = QPointF();
    m_scenePosRelease = QPointF();

    /* check whether the mouse press event is positioned at the Battle Map scene */
    if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) && (0 <= event->scenePos().y()) && (event->scenePos().x() <= this->height()))
    {
        /* set press position */
        m_scenePosPress = event->scenePos();

        this->addItem(pBattleMapSquareToDraw);
        pBattleMapSquareToDraw->setPen(QPen(Qt::black, 3, Qt::DotLine));
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles a mouse move event on the Battle Map scene.                                                                       *
 *                                                                                                                                                  *
 * \details This function handles a mouse move event on the Battle Map scene and checks whether the mouse press event has already been handled      *
 *          while the mouse release event has not been handled. If so, the coordinates of the top left and the bottom right corners of the square   *
 *          that is built from the previous mouse press event position and the mouse move event position are determined. Afterwards, the function   *
 *          sets the rectangle of the member variable pBattleMapSquareToDraw according to the determined corners.                                   *
 *                                                                                                                                                  *
 * \param   event                         Mouse move event to be handled                                                                            *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void BattleMapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "..." << __func__;

    if (!m_scenePosPress.isNull() && m_scenePosRelease.isNull())
    {
        /* determine corners of the square built from mouse press event and mouse move event positions */
        QPointF topLeft = QPointF(qMin(m_scenePosPress.rx(), event->scenePos().rx()), qMin(m_scenePosPress.y(), event->scenePos().ry()));
        QPointF bottomRight = QPointF(qMax(m_scenePosPress.rx(), event->scenePos().rx()), qMax(m_scenePosPress.y(), event->scenePos().ry()));

        pBattleMapSquareToDraw->setRect(topLeft.rx(), topLeft.ry(), (bottomRight - topLeft).rx(), (bottomRight - topLeft).ry());
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles a mouse release event on the Battle Map scene.                                                                    *
 *                                                                                                                                                  *
 * \details This function handles a mouse release event on the Battle Map scene and resets the member variable pBattleMapSquareToDraw and removes   *
 *          it from the Battle Map scene. Afterwards, the function checks whether the mouse release event is positioned at the Battle Map scene and *
 *          if so the member variable m_scenePosRelease is set according to the position of the parameter event. Moreover, the function emits the   *
 *          signal that a Battle Map square has been selected.                                                                                      *
 *                                                                                                                                                  *
 * \param   event                         Mouse release event to be handled                                                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void BattleMapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "..." << __func__;

    pBattleMapSquareToDraw->setRect(0, 0, 0, 0);
    this->removeItem(pBattleMapSquareToDraw);

    /* check whether the mouse release event is positioned at the Battle Map scene */
    if ((0 <= event->scenePos().x()) && (event->scenePos().x() <= this->width()) && (0 <= event->scenePos().y()) && (event->scenePos().x() <= this->height()))
    {
        m_scenePosRelease = event->scenePos();

        emit selected_BattleMapSquare();
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
