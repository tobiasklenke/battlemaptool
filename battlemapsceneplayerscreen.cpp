/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapsceneplayerscreen.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapScenePlayerScreen.
 */
BattleMapScenePlayerScreen::BattleMapScenePlayerScreen(QObject *parent) :
    BattleMapScene(parent)
{
}

/*!
 * \brief This function is the destructor of the class BattleMapScenePlayerScreen
 */
BattleMapScenePlayerScreen::~BattleMapScenePlayerScreen()
{
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse press event on the Battle Map scene.
 */
void BattleMapScenePlayerScreen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    BattleMapScene::mousePressEvent(event);
}

/*!
 * \brief This function handles a mouse move event on the Battle Map scene.
 */
void BattleMapScenePlayerScreen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

/*!
 * \brief This function handles a mouse release event on the Battle Map scene.
 */
void BattleMapScenePlayerScreen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    BattleMapScene::mouseReleaseEvent(event);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
