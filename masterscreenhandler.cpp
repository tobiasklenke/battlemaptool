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
    m_battleMapSquaresGraphicsItems(QList<QList<QGraphicsPixmapItem*>>()),
    m_scaleFactor(1.0),
    m_indexFirstRowSceneSection(0U),
    m_indexFirstColumnSceneSection(0U),
    m_numberRowsSceneSection(static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()))),
    m_numberColumnsSceneSection(static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width())))
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

    connect(pGraphicsView, SIGNAL(changed_ScaleFactor(qreal)), this, SLOT(changed_ScaleFactor(qreal)));
    connect(pGraphicsView, SIGNAL(pressed_Key(Qt::Key)), this, SLOT(pressed_Key(Qt::Key)));

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

    /* reset Battle Map scene section */
    m_indexFirstRowSceneSection = 0U;
    m_indexFirstColumnSceneSection = 0U;

    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));

    if (numberRowsOnPlayerScreen < pBattleMap->getNumberRows())
    {
        m_numberRowsSceneSection = numberRowsOnPlayerScreen;
    }
    else
    {
        m_numberRowsSceneSection = pBattleMap->getNumberRows();
    }

    if (numberColumnsOnPlayerScreen < pBattleMap->getNumberColumns())
    {
        m_numberColumnsSceneSection = numberColumnsOnPlayerScreen;
    }
    else
    {
        m_numberColumnsSceneSection = pBattleMap->getNumberColumns();
    }

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            pBattleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]);
        }
    }

    updateBattleMapSceneSection();

    /* Add the rect that frames the Battle Map scene section to be displayed on the players screen */
    m_sceneSectionRect.setPen(QPen(Qt::black, BATTLEMAPSECTIONFRAME_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine));
    pBattleMapScene->addItem(&m_sceneSectionRect);

    /* Add the rect that frames the whole Battle Map scene */
    pBattleMapScene->setSceneRect(0, 0, pBattleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, pBattleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);
    m_sceneFrameRect.setRect(pBattleMapScene->sceneRect());
    m_sceneFrameRect.setPen(QPen(Qt::black, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
    pBattleMapScene->addItem(&m_sceneFrameRect);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function updates the member variable m_scaleFactor and redraws the Battle Map section rect.
 */
void MasterScreenHandler::changed_ScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;

    m_sceneSectionRect.setPen(QPen(Qt::black, BATTLEMAPSECTIONFRAME_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine));
}

/*!
 * \brief This function updates the member variables m_indexFirstRowSceneSection and m_indexFirstColumnSceneSection and the Battle Map scene section.
 */
void MasterScreenHandler::pressed_Key(Qt::Key key)
{
    switch(key)
    {
    case Qt::Key_Left:
        if (0U < m_indexFirstColumnSceneSection)
        {
            m_indexFirstColumnSceneSection--;
            updateBattleMapSceneSection();
        }

        break;

    case Qt::Key_Up:
        if (0U < m_indexFirstRowSceneSection)
        {
            m_indexFirstRowSceneSection--;
            updateBattleMapSceneSection();
        }

        break;

    case Qt::Key_Right:
        if (pBattleMap->getNumberColumns() > m_indexFirstColumnSceneSection + m_numberColumnsSceneSection)
        {
            m_indexFirstColumnSceneSection++;
            updateBattleMapSceneSection();
        }

        break;

    case Qt::Key_Down:
        if (pBattleMap->getNumberRows() > m_indexFirstRowSceneSection + m_numberRowsSceneSection)
        {
            m_indexFirstRowSceneSection++;
            updateBattleMapSceneSection();
        }

        break;

    default:
        break;
    }
}

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
 * \brief This function updates the Battle Map scene section.
 */
void MasterScreenHandler::updateBattleMapSceneSection()
{
    /* Update the rect that frames the Battle Map scene section to be displayed on the player screen */
    m_sceneSectionRect.setRect(QRectF(QPointF(m_indexFirstColumnSceneSection, m_indexFirstRowSceneSection) * CONFIG_BATTLEMAPSQUARE_SIZE,
                                      QSize(m_numberColumnsSceneSection, m_numberRowsSceneSection) * CONFIG_BATTLEMAPSQUARE_SIZE));

    /* Update the opacity of the Battle Map squares depending on whether they are displayed on the player screen */
    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            if ((rowIdx < m_indexFirstRowSceneSection) || (m_indexFirstRowSceneSection + m_numberRowsSceneSection - 1U < rowIdx) ||
                    (columnIdx < m_indexFirstColumnSceneSection) || (m_indexFirstColumnSceneSection + m_numberColumnsSceneSection - 1U < columnIdx))
            {
                m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUAREOUTSIDESECTIONFRAME_OPACITY);
            }
            else
            {
                m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUAREWITHINSECTIONFRAME_OPACITY);
            }
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
