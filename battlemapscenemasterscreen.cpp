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
    BattleMapScene(parent)
{
}

/*!
 * \brief This function is the destructor of the class BattleMapSceneMasterScreen
 */
BattleMapSceneMasterScreen::~BattleMapSceneMasterScreen()
{
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a mouse press event on the Battle Map scene.
 */
void BattleMapSceneMasterScreen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->BattleMapScene::mousePressEvent(event);
}

/*!
 * \brief This function handles a mouse move event on the Battle Map scene.
 */
void BattleMapSceneMasterScreen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

/*!
 * \brief This function handles a mouse release event on the Battle Map scene.
 */
void BattleMapSceneMasterScreen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->BattleMapScene::mouseReleaseEvent(event);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
