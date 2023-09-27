/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "masterscreenhandler.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class MasterScreenHandler.
 */
MasterScreenHandler::MasterScreenHandler() :
    pGraphicsView(nullptr),
    pBattleMap(nullptr),
    pBattleMapScene(new BattleMapSceneMasterScreen()),
    m_battleMapSquaresGraphicsItems(QList<QList<QGraphicsPixmapItem*>>())
{
}

/*!
 * \brief This function is the destructor of the class MasterScreenHandler.
 */
MasterScreenHandler::~MasterScreenHandler()
{
    deleteBattleMapScene();
    deleteBattleMapSquaresGraphicsItems();
}

/*!
 * \brief This function sets the address of the member variable pGraphicsView.
 */
void MasterScreenHandler::setGraphicsView(GraphicsView_BattleMap *graphicsView)
{
    pGraphicsView = graphicsView;

    QPalette palette;
    pGraphicsView->setBackgroundBrush(QBrush(palette.color(QPalette::Window)));
    pGraphicsView->setScene(pBattleMapScene);

    m_sceneText.setPlainText("New Battle Map\t[Ctrl+N]\nOpen Battle Map\t[Ctrl+O]");
    pBattleMapScene->addItem(&m_sceneText);
}

/*!
 * \brief This function sets the address of the member variable pBattleMap.
 */
void MasterScreenHandler::setBattleMap(BattleMap *battleMap)
{
    pBattleMap = battleMap;

    updateBattleMapSquaresGraphicsItems();
}

/*!
 * \brief This function shows the Battle Map image.
 */
void MasterScreenHandler::showBattleMapImage()
{
    /* reset Battle Map scene */
    deleteBattleMapScene();
    pBattleMapScene = new BattleMapSceneMasterScreen();
    pGraphicsView->resetScaling();
    pGraphicsView->setScene(pBattleMapScene);

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            pBattleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]);
        }
    }

    pBattleMapScene->setSceneRect(0, 0, pBattleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, pBattleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);
    m_sceneRect.setRect(pBattleMapScene->sceneRect());
    m_sceneRect.setPen(QPen(Qt::black, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
    pBattleMapScene->addItem(&m_sceneRect);
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
void MasterScreenHandler::deleteBattleMapSquaresGraphicsItems()
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
void MasterScreenHandler::updateBattleMapSquaresGraphicsItems()
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
void MasterScreenHandler::deleteBattleMapScene()
{
    for (QGraphicsItem * item : pBattleMapScene->items())
    {
        pBattleMapScene->removeItem(item);
    }

    delete pBattleMapScene;
}
