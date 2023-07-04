#ifndef BATTLEMAPSCENE_H
#define BATTLEMAPSCENE_H

/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

/****************************************************************************************************************************************************
 * Class Declaration
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for the selection of a square on the Battle Map image.
 */
class BattleMapScene : public QGraphicsScene
{
    Q_OBJECT

public:

    /*!
     * \brief This function is the constructor of the class BattleMapScene.
     */
    BattleMapScene(QObject *parent = nullptr);

    /*!
     * \brief This function is the destructor of the class BattleMapScene.
     */
    ~BattleMapScene();

    /*!
     * \brief This function returns the value of the member variable scenePosPress.
     */
    QPointF getScenePosPress() const;

    /*!
     * \brief This function sets the value of the member variable scenePosPress.
     */
    void setScenePosPress(QPointF newScenePosPress);

    /*!
     * \brief This function returns the value of the member variable scenePosRelease.
     */
    QPointF getScenePosRelease() const;

    /*!
     * \brief This function sets the value of the member variable scenePosRelease.
     */
    void setScenePosRelease(QPointF newScenePosRelease);

    /*!
     * \brief This function draws a Battle Map line.
     */
    void drawBattleMapLine(QLineF battleMapLine);

    /*!
     * \brief This function removes all Battle Map lines.
     */
    void removeBattleMapLines();

protected:

    /*!
     * \brief This function handles a mouse press event on BattleMapScene.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief This function handles a mouse move event on BattleMapScene.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief This function handles a mouse release event on BattleMapScene.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

    /*!
     * \brief This signal is emitted as soon as a Battle Map square has been selected.
     */
    void selected_BattleMapSquare(void);


private:

    /*!
     * \brief This is the rectangle to be drawn while the selection of the Battle Map square.
     */
    QGraphicsRectItem *pBattleMapSquareToDraw;

    /*!
     * \brief This is a vector of grid lines to be drawn for control purposes.
     */
    QVector<QGraphicsLineItem*> m_battleMapLinesToDraw;

    /*!
     * \brief This is the position of the cursor while the mouse press event.
     */
    QPointF m_scenePosPress;

    /*!
     * \brief This is the position of the cursor while the mouse release event.
     */
    QPointF m_scenePosRelease;
};

#endif // BATTLEMAPSCENE_H
