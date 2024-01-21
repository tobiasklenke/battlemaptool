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
 * \brief This function handles a mouse press event.
 */
void BattleMapScenePlayerScreen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* call base class function in order to set press position */
    BattleMapScene::mousePressEvent(event);

    /* TODO: functionality to be implemented, no use case so far */
}

/*!
 * \brief This function handles a mouse move event.
 */
void BattleMapScenePlayerScreen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    /* TODO: functionality to be implemented, no use case so far */
}

/*!
 * \brief This function handles a mouse release event.
 */
void BattleMapScenePlayerScreen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* call base class function in order to set release position */
    BattleMapScene::mouseReleaseEvent(event);

    /* TODO: functionality to be implemented, no use case so far */
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
