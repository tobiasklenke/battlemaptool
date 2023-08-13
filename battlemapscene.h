#ifndef BATTLEMAPSCENE_H
#define BATTLEMAPSCENE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief This class implements the functionality needed for the selection of a Battle Map square.                                                  *
 ****************************************************************************************************************************************************/
class BattleMapScene : public QGraphicsScene
{
    Q_OBJECT

public:

/*!**************************************************************************************************************************************************
 * \brief   This function is the constructor of the class BattleMapScene.                                                                           *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \param   parent                        Parent of the class BattleMapScene                                                                        *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    BattleMapScene(QObject *parent = nullptr);

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class BattleMapScene.                                                                            *
 *                                                                                                                                                  *
 * \details This function deletes the object pointed to by pBattleMapSquareToDraw.                                                                  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    ~BattleMapScene();

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_battleMapLinesToDraw.                                                          *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_battleMapLinesToDraw.                                                          *
 ****************************************************************************************************************************************************/
    QList<QGraphicsLineItem*> getBattleMapLinesToDraw() const;

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_scenePosPress.                                                                 *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_scenePosPress.                                                                 *
 ****************************************************************************************************************************************************/
    QPointF getScenePosPress() const;

/*!**************************************************************************************************************************************************
 * \brief   This function returns the value of the member variable m_scenePosRelease.                                                               *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the value of the member variable m_scenePosRelease.                                                               *
 ****************************************************************************************************************************************************/
    QPointF getScenePosRelease() const;

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
    void drawBattleMapLine(QLineF battleMapLine, QPen pen);

/*!**************************************************************************************************************************************************
 * \brief   This function removes all Battle Map lines.                                                                                             *
 *                                                                                                                                                  *
 * \details This function removes all Battle Map lines from the Battle Map scene and deletes them from the member variable m_battleMapLinesToDraw.  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void removeBattleMapLines();

protected:

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
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

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
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

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
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

/*!**************************************************************************************************************************************************
 * \brief This signal is emitted as soon as a Battle Map square has been selected.                                                                  *
 ****************************************************************************************************************************************************/
    void selected_BattleMapSquare(void);


private:

/*!**************************************************************************************************************************************************
 * \brief This is the rectangle to be drawn while the selection of the Battle Map square.                                                           *
 ****************************************************************************************************************************************************/
    QGraphicsRectItem *pBattleMapSquareToDraw;

/*!**************************************************************************************************************************************************
 * \brief This is a list of Battle Map lines building the Battle Map grid to be drawn for control purposes.                                         *
 ****************************************************************************************************************************************************/
    QList<QGraphicsLineItem*> m_battleMapLinesToDraw;

/*!**************************************************************************************************************************************************
 * \brief This is the position of the cursor while the mouse press event.                                                                           *
 ****************************************************************************************************************************************************/
    QPointF m_scenePosPress;

/*!**************************************************************************************************************************************************
 * \brief This is the position of the cursor while the mouse release event.                                                                         *
 ****************************************************************************************************************************************************/
    QPointF m_scenePosRelease;
};

#endif // BATTLEMAPSCENE_H
