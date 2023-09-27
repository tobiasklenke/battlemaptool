/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "playerscreenhandler.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class PlayerScreenHandler.
 */
PlayerScreenHandler::PlayerScreenHandler() :
    pGraphicsView(nullptr),
    pBattleMap(nullptr),
    pBattleMapScene(new BattleMapScenePlayerScreen()),
    m_battleMapSquaresGraphicsItems(QList<QList<QGraphicsPixmapItem*>>())
{
}

/*!
 * \brief This function is the destructor of the class PlayerScreenHandler.
 */
PlayerScreenHandler::~PlayerScreenHandler()
{
    deleteBattleMapScene();
    deleteBattleMapSquaresGraphicsItems();
}

/*!
 * \brief This function sets the address of the member variable pGraphicsView.
 */
void PlayerScreenHandler::setGraphicsView(QGraphicsView *graphicsView)
{
    pGraphicsView = graphicsView;

    pGraphicsView->setBackgroundBrush(QBrush(Qt::black));
    pGraphicsView->setFrameStyle(QFrame::NoFrame);
    pGraphicsView->setScene(pBattleMapScene);
}

/*!
 * \brief This function sets the address of the member variable pBattleMap.
 */
void PlayerScreenHandler::setBattleMap(BattleMap *battleMap)
{
    pBattleMap = battleMap;

    updateBattleMapSquaresGraphicsItems();
}

/*!
 * \brief This function shows the Battle Map image.
 */
void PlayerScreenHandler::showBattleMapImage()
{
    //TODO
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function deletes the graphics items of the Battle Map squares.
 */
void PlayerScreenHandler::deleteBattleMapSquaresGraphicsItems()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquaresGraphicsItems.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquaresGraphicsItems[rowIdx].count(); columnIdx++)
        {
            delete m_battleMapSquaresGraphicsItems[rowIdx][columnIdx];
        }
    }

    m_battleMapSquaresGraphicsItems.clear();
}

/*!
 * \brief This function updates the graphics items of the Battle Map squares.
 */
void PlayerScreenHandler::updateBattleMapSquaresGraphicsItems()
{
    deleteBattleMapSquaresGraphicsItems();

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        /* append row to nested QList member variable m_battleMapSquaresGraphicsItems if row does not already exist */
        if (rowIdx + 1 > m_battleMapSquaresGraphicsItems.count())
        {
            m_battleMapSquaresGraphicsItems.append(QList<QGraphicsPixmapItem*>());
        }

        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            /* append graphics item of Battle Map square to row of nested QList member variable m_battleMapSquaresGraphicsItems */
            m_battleMapSquaresGraphicsItems[rowIdx].append(new QGraphicsPixmapItem(pBattleMap->getBattleMapSquarePixmap(rowIdx, columnIdx)));
        }
    }
}

/*!
 * \brief This function deletes the Battle Map scene.
 */
void PlayerScreenHandler::deleteBattleMapScene()
{
    for (QGraphicsItem * item : pBattleMapScene->items())
    {
        pBattleMapScene->removeItem(item);
    }

    delete pBattleMapScene;
}
