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
    m_graphicsView(nullptr),
    m_battleMap(nullptr),
    m_battleMapSceneSection(nullptr),
    m_battleMapScene(new BattleMapSceneMasterScreen()),
    m_operationMode(Select),
    m_battleMapSquaresGraphicsItems(QList<QList<QGraphicsPixmapItem*>>()),
    m_coverageGraphicsItems(QList<QList<QGraphicsRectItem*>>()),
    m_scaleFactor(1.0)
{
}

/*!
 * \brief This function is the destructor of the class MasterScreenHandler.
 */
MasterScreenHandler::~MasterScreenHandler()
{
    /* delete objects created in the constructor */
    deleteBattleMapScene();
    deleteBattleMapSquaresGraphicsItems();
}

/*!
 * \brief This function sets the address of the member variable m_graphicsView.
 */
void MasterScreenHandler::setGraphicsView(CustomGraphicsView *graphicsView)
{
    m_graphicsView = graphicsView;

    /* connect signals and slots of graphics view */
    connect(m_graphicsView, SIGNAL(changedScaleFactor(qreal)), this, SLOT(changedScaleFactor(qreal)));
    connect(m_graphicsView, SIGNAL(pressedKey(Qt::Key)), this, SLOT(pressedKey(Qt::Key)));
    connect(m_graphicsView, SIGNAL(pressedRightMouseButton(QPoint)), this, SLOT(pressedRightMouseButton(QPoint)));

    /* set background color of graphics view to window color */
    QPalette palette;
    m_graphicsView->setBackgroundBrush(QBrush(palette.color(QPalette::Window)));

    /* set Battle Map scene to graphics view and add text asking user to create new Battle Map or open existing Battle Map */
    m_graphicsView->setScene(m_battleMapScene);
    m_sceneText.setPlainText("New Battle Map\t[Ctrl+N]\nOpen Battle Map\t[Ctrl+O]");
    m_battleMapScene->addItem(&m_sceneText);
}

/*!
 * \brief This function sets the address of the member variable m_battleMap.
 */
void MasterScreenHandler::setBattleMap(BattleMap *battleMap)
{
    m_battleMap = battleMap;

    /* update Battle Map square graphics items according to set Battle Map */
    updateBattleMapSquaresGraphicsItems();
}

/*!
 * \brief This function sets the address of the member variable m_battleMapSceneSection.
 */
void MasterScreenHandler::setBattleMapSceneSection(BattleMapSceneSection *battleMapSceneSection)
{
    m_battleMapSceneSection = battleMapSceneSection;
}

/*!
 * \brief This function sets the member variable m_operationMode.
 */
void MasterScreenHandler::setOperationMode(operationMode_t operationMode)
{
    m_operationMode = operationMode;

    /* reset selection area when operation mode is changed */
    resetSelectionArea();

    /* set cursor according to operation mode */
    QCursor cursor;
    switch (operationMode)
    {
    case Select:
        cursor = Qt::ArrowCursor;
        break;
    case CoverBattleMap:
        cursor = QCursor(QPixmap::fromImage(QImage(COVERBATTLEMAPICON_SOURCE)).scaled(QSize(CUSTOMPIXMAPCURSOR_SIZE, CUSTOMPIXMAPCURSOR_SIZE)));
        break;
    case UncoverBattleMap:
        cursor = QCursor(QPixmap::fromImage(QImage(UNCOVERBATTLEMAPICON_SOURCE)).scaled(QSize(CUSTOMPIXMAPCURSOR_SIZE, CUSTOMPIXMAPCURSOR_SIZE)));
        break;
    default:
        cursor = Qt::ArrowCursor;
        break;
    }
    m_graphicsView->viewport()->setCursor(cursor);
}

/*!
 * \brief This function returns the pixmaps of the Battle Map squares from the selection area.
 */
QList<QList<QPixmap>> MasterScreenHandler::getPixmapsFromSelectionArea()
{
    QList<QList<QPixmap>> pixmapsFromSelectionArea;

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* append new row of pixmaps */
        pixmapsFromSelectionArea.append(QList<QPixmap>());

        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* append new pixmap to row if corresponding Battle Map square is selected */
            if (m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->isSelected())
            {
                pixmapsFromSelectionArea.last().append(m_battleMap->getBattleMapSquarePixmap(rowIdx, columnIdx));
            }
        }

        /* remove row of pixmaps if no pixmaps have been appended */
        if (0U == pixmapsFromSelectionArea.last().count())
        {
            pixmapsFromSelectionArea.removeLast();
        }
    }

    return pixmapsFromSelectionArea;
}

/*!
 * \brief This function returns the indexes of the first selected Battle Map square via its parameters.
 */
void MasterScreenHandler::getIndexesOfFirstBattleMapSquareFromSelectionArea(quint32 *firstSelectedRowIdx, quint32 *firstSelectedColumnIdx)
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* check for first selected Battle Map square */
            if (m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->isSelected())
            {
                /* set indexes of first selected Battle Map square */
                *firstSelectedRowIdx = rowIdx;
                *firstSelectedColumnIdx = columnIdx;

                return;
            }
        }
    }
}

/*!
 * \brief This function shows the Battle Map image.
 */
void MasterScreenHandler::showBattleMapImage()
{
    /* reset and reconnect Battle Map scene */
    deleteBattleMapScene();
    m_battleMapScene = new BattleMapSceneMasterScreen();
    connect(m_battleMapScene, SIGNAL(selectedBattleMapSquares()), this, SLOT(selectedBattleMapSquares()));
    connect(m_battleMapScene, SIGNAL(unselectedBattleMapSquares()), this, SLOT(unselectedBattleMapSquares()));
    m_graphicsView->setScene(m_battleMapScene);

    /* reset scaling of graphics view */
    m_graphicsView->resetScaling();

    /* add Battle Map squares and coverage rectangles to Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]);

            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_battleMapScene->addItem(m_coverageGraphicsItems[rowIdx][columnIdx]);
        }
    }
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* update Battle Map scene section and add frame */
    updateBattleMapSceneSection();
    m_sceneSectionRect.setPen(QPen(Qt::black, BATTLEMAPSECTIONFRAME_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine));
    m_battleMapScene->addItem(&m_sceneSectionRect);

    /* enable event processing of graphics view as soon as Battle Map image is shown */
    m_graphicsView->setEventProcessingEnabled(true);
    m_graphicsView->setInteractive(true);
}

/*!
 * \brief This function updates the pixmaps of the Battle Map squares according to the Battle Map.
 */
void MasterScreenHandler::updatePixmapsAccordingBattleMap()
{
    /* update pixmaps of Battle Map squares according to Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPixmap(m_battleMap->getBattleMapSquarePixmap(rowIdx, columnIdx));
        }
    }
}

/*!
 * \brief This function inserts a new row above the Battle Map.
 */
void MasterScreenHandler::insertRowAbove()
{
    /* insert new row above Battle Map */
    m_battleMapSquaresGraphicsItems.prepend(QList<QGraphicsPixmapItem*>());
    m_coverageGraphicsItems.prepend(QList<QGraphicsRectItem*>());

    for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
    {
        /* append graphics item of Battle Map square to row */
        m_battleMapSquaresGraphicsItems.first().append(new QGraphicsPixmapItem(m_battleMap->getBattleMapSquarePixmap(0U, columnIdx)));

        /* make Battle Map square selectable */
        m_battleMapSquaresGraphicsItems.first()[columnIdx]->setFlag(QGraphicsItem::ItemIsSelectable, true);

        /* set graphics item of Battle Map square to background layer */
        m_battleMapSquaresGraphicsItems.first()[columnIdx]->setZValue(ZValueBackgroundedGraphicsItem);

        /* add Battle Map square to Battle Map scene */
        m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems.first()[columnIdx]);

        /* append graphics item of coverage rectangle to row */
        m_coverageGraphicsItems.first().append(new QGraphicsRectItem(m_battleMap->getBattleMapSquarePixmap(0U, columnIdx).rect()));
        m_coverageGraphicsItems.first()[columnIdx]->setBrush(QBrush(BATTLEMAPSQUARECOVERED_COLOR));
        m_coverageGraphicsItems.first()[columnIdx]->setPen(Qt::NoPen);
        m_coverageGraphicsItems.first()[columnIdx]->setVisible(false);

        /* set graphics item of coverage rectangle to coverage layer */
        m_coverageGraphicsItems.first()[columnIdx]->setZValue(ZValueCoverageGraphicsItem);

        /* add coverage rectangle to Battle Map scene */
        m_battleMapScene->addItem(m_coverageGraphicsItems.first()[columnIdx]);

        /* set visibility state of coverage rectangle according to coverage state of Battle Map square */
        m_coverageGraphicsItems.first()[columnIdx]->setVisible(m_battleMap->getBattleMapSquareCovered(0U, columnIdx));
    }

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function inserts a new row below the Battle Map.
 */
void MasterScreenHandler::insertRowBelow()
{
    /* insert new row below Battle Map */
    m_battleMapSquaresGraphicsItems.append(QList<QGraphicsPixmapItem*>());
    m_coverageGraphicsItems.append(QList<QGraphicsRectItem*>());

    for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
    {
        /* append graphics item of Battle Map square to row */
        m_battleMapSquaresGraphicsItems.last().append(new QGraphicsPixmapItem(m_battleMap->getBattleMapSquarePixmap(m_battleMap->getNumberRows() - 1U, columnIdx)));

        /* make Battle Map square selectable */
        m_battleMapSquaresGraphicsItems.last()[columnIdx]->setFlag(QGraphicsItem::ItemIsSelectable, true);

        /* set graphics item of Battle Map square to background layer */
        m_battleMapSquaresGraphicsItems.last()[columnIdx]->setZValue(ZValueBackgroundedGraphicsItem);

        /* add Battle Map square to Battle Map scene */
        m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems.last()[columnIdx]);

        /* append graphics item of coverage rectangle to row */
        m_coverageGraphicsItems.last().append(new QGraphicsRectItem(m_battleMap->getBattleMapSquarePixmap(m_battleMap->getNumberRows() - 1U, columnIdx).rect()));
        m_coverageGraphicsItems.last()[columnIdx]->setBrush(QBrush(BATTLEMAPSQUARECOVERED_COLOR));
        m_coverageGraphicsItems.last()[columnIdx]->setPen(Qt::NoPen);
        m_coverageGraphicsItems.last()[columnIdx]->setVisible(false);

        /* set graphics item of coverage rectangle to coverage layer */
        m_coverageGraphicsItems.last()[columnIdx]->setZValue(ZValueCoverageGraphicsItem);

        /* add coverage rectangle to Battle Map scene */
        m_battleMapScene->addItem(m_coverageGraphicsItems.last()[columnIdx]);

        /* set visibility state of coverage rectangle according to coverage state of Battle Map square */
        m_coverageGraphicsItems.last()[columnIdx]->setVisible(m_battleMap->getBattleMapSquareCovered(m_battleMap->getNumberRows() - 1U, columnIdx));
    }

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function inserts a new column to the left of the Battle Map.
 */
void MasterScreenHandler::insertColumnLeft()
{
    /* insert new column to the left of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* prepend graphics item of Battle Map square to row */
        m_battleMapSquaresGraphicsItems[rowIdx].prepend(new QGraphicsPixmapItem(m_battleMap->getBattleMapSquarePixmap(rowIdx, 0U)));

        /* make Battle Map square selectable */
        m_battleMapSquaresGraphicsItems[rowIdx].first()->setFlag(QGraphicsItem::ItemIsSelectable, true);

        /* set graphics item of Battle Map square to background layer */
        m_battleMapSquaresGraphicsItems[rowIdx].first()->setZValue(ZValueBackgroundedGraphicsItem);

        /* add Battle Map square to Battle Map scene */
        m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx].first());

        /* prepend graphics item of coverage rectangle to row */
        m_coverageGraphicsItems[rowIdx].prepend(new QGraphicsRectItem(m_battleMap->getBattleMapSquarePixmap(rowIdx, 0U).rect()));
        m_coverageGraphicsItems[rowIdx].first()->setBrush(QBrush(BATTLEMAPSQUARECOVERED_COLOR));
        m_coverageGraphicsItems[rowIdx].first()->setPen(Qt::NoPen);
        m_coverageGraphicsItems[rowIdx].first()->setVisible(false);

        /* set graphics item of Battle Map square to coverage layer */
        m_coverageGraphicsItems[rowIdx].first()->setZValue(ZValueCoverageGraphicsItem);

        /* add coverage rectangle to Battle Map scene */
        m_battleMapScene->addItem(m_coverageGraphicsItems[rowIdx].first());

        /* set visibility state of coverage rectangle according to coverage state of Battle Map square */
        m_coverageGraphicsItems[rowIdx].first()->setVisible(m_battleMap->getBattleMapSquareCovered(rowIdx, 0U));
    }

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function inserts a new column to the right of the Battle Map.
 */
void MasterScreenHandler::insertColumnRight()
{
    /* insert new column to the right of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* append graphics item of Battle Map square to row */
        m_battleMapSquaresGraphicsItems[rowIdx].append(new QGraphicsPixmapItem(m_battleMap->getBattleMapSquarePixmap(rowIdx, m_battleMap->getNumberColumns() - 1U)));

        /* make Battle Map square selectable */
        m_battleMapSquaresGraphicsItems[rowIdx].last()->setFlag(QGraphicsItem::ItemIsSelectable, true);

        /* set graphics item of Battle Map square to background layer */
        m_battleMapSquaresGraphicsItems[rowIdx].last()->setZValue(ZValueBackgroundedGraphicsItem);

        /* add Battle Map square to Battle Map scene */
        m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx].last());

        /* append graphics item of coverage rectangle to row */
        m_coverageGraphicsItems[rowIdx].append(new QGraphicsRectItem(m_battleMap->getBattleMapSquarePixmap(rowIdx, m_battleMap->getNumberColumns() - 1U).rect()));
        m_coverageGraphicsItems[rowIdx].last()->setBrush(QBrush(BATTLEMAPSQUARECOVERED_COLOR));
        m_coverageGraphicsItems[rowIdx].last()->setPen(Qt::NoPen);
        m_coverageGraphicsItems[rowIdx].last()->setVisible(false);

        /* set graphics item of Battle Map square to coverage layer */
        m_coverageGraphicsItems[rowIdx].last()->setZValue(ZValueCoverageGraphicsItem);

        /* add coverage rectangle to Battle Map scene */
        m_battleMapScene->addItem(m_coverageGraphicsItems[rowIdx].last());

        /* set visibility state of coverage rectangle according to coverage state of Battle Map square */
        m_coverageGraphicsItems[rowIdx].last()->setVisible(m_battleMap->getBattleMapSquareCovered(rowIdx, m_battleMap->getNumberColumns() - 1U));
    }

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function deletes a row above the Battle Map.
 */
void MasterScreenHandler::deleteRowAbove()
{
    /* delete row above Battle Map */
    for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquaresGraphicsItems.first().count(); columnIdx++)
    {
        /* remove Battle Map square and coverage rectangle from Battle Map scene */
        m_battleMapScene->removeItem(m_battleMapSquaresGraphicsItems.first()[columnIdx]);
        m_battleMapScene->removeItem(m_coverageGraphicsItems.first()[columnIdx]);
        delete m_battleMapSquaresGraphicsItems.first()[columnIdx];
        delete m_coverageGraphicsItems.first()[columnIdx];
    }
    m_battleMapSquaresGraphicsItems.removeFirst();
    m_coverageGraphicsItems.removeFirst();

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function deletes a row below the Battle Map.
 */
void MasterScreenHandler::deleteRowBelow()
{
    /* delete row below Battle Map */
    for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquaresGraphicsItems.last().count(); columnIdx++)
    {
        /* remove Battle Map square and coverage rectangle from Battle Map scene */
        m_battleMapScene->removeItem(m_battleMapSquaresGraphicsItems.last()[columnIdx]);
        m_battleMapScene->removeItem(m_coverageGraphicsItems.last()[columnIdx]);
        delete m_battleMapSquaresGraphicsItems.last()[columnIdx];
        delete m_coverageGraphicsItems.last()[columnIdx];
    }
    m_battleMapSquaresGraphicsItems.removeLast();
    m_coverageGraphicsItems.removeLast();

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function deletes a column to the left of the Battle Map.
 */
void MasterScreenHandler::deleteColumnLeft()
{
    /* delete column to the left of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquaresGraphicsItems.count(); rowIdx++)
    {
        /* remove Battle Map square and coverage rectangle from Battle Map scene */
        m_battleMapScene->removeItem(m_battleMapSquaresGraphicsItems[rowIdx].first());
        m_battleMapScene->removeItem(m_coverageGraphicsItems[rowIdx].first());
        delete m_battleMapSquaresGraphicsItems[rowIdx].first();
        delete m_coverageGraphicsItems[rowIdx].first();

        m_battleMapSquaresGraphicsItems[rowIdx].removeFirst();
        m_coverageGraphicsItems[rowIdx].removeFirst();
    }

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function deletes a column to the right of the Battle Map.
 */
void MasterScreenHandler::deleteColumnRight()
{
    /* delete column to the right of Battle Map */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquaresGraphicsItems.count(); rowIdx++)
    {
        /* remove Battle Map square and coverage rectangle from Battle Map scene */
        m_battleMapScene->removeItem(m_battleMapSquaresGraphicsItems[rowIdx].last());
        m_battleMapScene->removeItem(m_coverageGraphicsItems[rowIdx].last());
        delete m_battleMapSquaresGraphicsItems[rowIdx].last();
        delete m_coverageGraphicsItems[rowIdx].last();

        m_battleMapSquaresGraphicsItems[rowIdx].removeLast();
        m_coverageGraphicsItems[rowIdx].removeLast();
    }

    /* reposition Battle Map squares and coverage rectangles on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
        }
    }

    /* update Battle Map scene section and frame */
    updateBattleMapSceneSection();
    m_battleMapScene->setSceneRect(0, 0, m_battleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);

    /* reset selection area when editing of Battle Map is finished */
    resetSelectionArea();
}

/*!
 * \brief This function updates the coverage state of Battle Map squares.
 */
void MasterScreenHandler::handleCoverBattleMap(bool covered)
{
    quint32 rowIdx = 0U;
    quint32 columnIdx = 0U;
    for (QGraphicsItem * selectedItem : m_battleMapScene->selectedItems())
    {
        /* get row and column indexes of selected Battle Map squares */
        for (rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
        {
            if (-1 < m_battleMapSquaresGraphicsItems[rowIdx].indexOf(selectedItem))
            {
                columnIdx = m_battleMapSquaresGraphicsItems[rowIdx].indexOf(selectedItem);
                break;
            }

        }

        /* update coverage state of selected Battle Map square and visibility state of corresponding coverage rectangle */
        m_battleMap->setBattleMapSquareCovered(rowIdx, columnIdx, covered);
        m_coverageGraphicsItems[rowIdx][columnIdx]->setVisible(covered);
    }

    /* reset selection area when update of coverage state is finished */
    resetSelectionArea();
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function updates the member variable m_scaleFactor.
 */
void MasterScreenHandler::changedScaleFactor(qreal scaleFactor)
{
    /* update scale factor of master screen handler */
    m_scaleFactor = scaleFactor;

    /* update scale factor of Battle Map scene */
    m_battleMapScene->changedScaleFactor(scaleFactor);

    /* redraw Battle Map scene section rect */
    m_sceneSectionRect.setPen(QPen(Qt::black, BATTLEMAPSECTIONFRAME_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine));
}

/*!
 * \brief This function handles a key press.
 */
void MasterScreenHandler::pressedKey(Qt::Key key)
{
    /* determine viewport center position in scene coordinates */
    QPointF scenePosCenter = m_graphicsView->mapToScene(m_graphicsView->viewport()->rect().center());

    switch(key)
    {
    case Qt::Key_Left:
        if (0U < m_battleMapSceneSection->getIndexFirstColumnSceneSection())
        {
            /* decrement index of first column of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstColumnSceneSection(m_battleMapSceneSection->getIndexFirstColumnSceneSection() - 1U);

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            qreal difference = m_graphicsView->mapToScene(m_graphicsView->viewport()->rect().topLeft()).x() -
                    static_cast<qreal>(m_battleMapSceneSection->getIndexFirstColumnSceneSection() * CONFIG_BATTLEMAPSQUARE_SIZE);

            if (0 < difference)
            {
                m_graphicsView->centerOn(scenePosCenter.x() - difference, scenePosCenter.y());
            }
        }
        break;

    case Qt::Key_Up:
        if (0U < m_battleMapSceneSection->getIndexFirstRowSceneSection())
        {
            /* decrement index of first row of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstRowSceneSection(m_battleMapSceneSection->getIndexFirstRowSceneSection() - 1U);

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            qreal difference = m_graphicsView->mapToScene(m_graphicsView->viewport()->rect().topLeft()).y() -
                     static_cast<qreal>(m_battleMapSceneSection->getIndexFirstRowSceneSection() * CONFIG_BATTLEMAPSQUARE_SIZE);

            if (0 < difference)
            {
                m_graphicsView->centerOn(scenePosCenter.x(), scenePosCenter.y() - difference);
            }
        }
        break;

    case Qt::Key_Right:
        if (m_battleMap->getNumberColumns() > m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection())
        {
            /* increment index of first column of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstColumnSceneSection(m_battleMapSceneSection->getIndexFirstColumnSceneSection() + 1U);

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            qreal difference = static_cast<qreal>((m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection()) * CONFIG_BATTLEMAPSQUARE_SIZE -
                                            m_graphicsView->mapToScene(m_graphicsView->viewport()->rect().bottomRight()).x());

            if (0 < difference)
            {
                m_graphicsView->centerOn(scenePosCenter.x() + difference, scenePosCenter.y());
            }
        }
        break;

    case Qt::Key_Down:
        if (m_battleMap->getNumberRows() > m_battleMapSceneSection->getIndexFirstRowSceneSection() + m_battleMapSceneSection->getNumberRowsSceneSection())
        {
            /* increment index of first row of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstRowSceneSection(m_battleMapSceneSection->getIndexFirstRowSceneSection() + 1U);

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            qreal difference = static_cast<qreal>((m_battleMapSceneSection->getIndexFirstRowSceneSection() + m_battleMapSceneSection->getNumberRowsSceneSection()) * CONFIG_BATTLEMAPSQUARE_SIZE) -
                    m_graphicsView->mapToScene(m_graphicsView->viewport()->rect().bottomRight()).y();

            if (0 < difference)
            {
                m_graphicsView->centerOn(scenePosCenter.x(),  scenePosCenter.y() + difference);
            }
        }
        break;

    default:
        break;
    }

    updateBattleMapSceneSection();
}

/*!
 * \brief This function handles a press of the right mouse button.
 */
void MasterScreenHandler::pressedRightMouseButton(QPoint position)
{
    /* handle only graphics items positioned at right mouse button press position */
    for (QGraphicsItem * item : m_battleMapScene->items(m_graphicsView->mapToScene(position)))
    {
        /* handle only selectable graphics items that are not selected */
        if (item->flags().testFlag(QGraphicsItem::ItemIsSelectable) && !item->isSelected())
        {
            /* handle selection of Battle Map squares */
            handleSelect(m_graphicsView->mapToScene(position), m_graphicsView->mapToScene(position));
        }
    }
}

/*!
 * \brief This function handles the selection of some Battle Map squares.
 */
void MasterScreenHandler::selectedBattleMapSquares()
{
    /* handle selection of Battle Map squares with respective operation mode */
    switch (m_operationMode)
    {
    case Select:
        handleSelect(m_battleMapScene->getScenePosPress(), m_battleMapScene->getScenePosRelease());
        break;
    case CoverBattleMap:
        handleSelect(m_battleMapScene->getScenePosPress(), m_battleMapScene->getScenePosRelease());
        handleCoverBattleMap(true);
        break;
    case UncoverBattleMap:
        handleSelect(m_battleMapScene->getScenePosPress(), m_battleMapScene->getScenePosRelease());
        handleCoverBattleMap(false);
        break;
    default:
        break;
    }
}

/*!
 * \brief This function handles the unselection of all Battle Map squares.
 */
void MasterScreenHandler::unselectedBattleMapSquares()
{
    resetSelectionArea();
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function deletes the graphics items of the Battle Map squares and coverage rectangles.
 */
void MasterScreenHandler::deleteBattleMapSquaresGraphicsItems()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquaresGraphicsItems.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquaresGraphicsItems[rowIdx].count(); columnIdx++)
        {
            /* delete graphics items */
            delete m_battleMapSquaresGraphicsItems[rowIdx][columnIdx];
            delete m_coverageGraphicsItems[rowIdx][columnIdx];
        }
    }

    /* remove all graphics items from list */
    m_battleMapSquaresGraphicsItems.clear();
    m_coverageGraphicsItems.clear();
}

/*!
 * \brief This function updates the graphics items of the Battle Map squares and coverage rectangles.
 */
void MasterScreenHandler::updateBattleMapSquaresGraphicsItems()
{
    /* delete Battle Map squares and coverage rectangles of previous Battle Map */
    deleteBattleMapSquaresGraphicsItems();

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* append row to nested QList member variables m_battleMapSquaresGraphicsItems and m_coverageGraphicsItems if row does not already exist */
        if (rowIdx + 1 > m_battleMapSquaresGraphicsItems.count())
        {
            m_battleMapSquaresGraphicsItems.append(QList<QGraphicsPixmapItem*>());
            m_coverageGraphicsItems.append(QList<QGraphicsRectItem*>());
        }

        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* append graphics item of Battle Map square to row of nested QList member variable m_battleMapSquaresGraphicsItems */
            m_battleMapSquaresGraphicsItems[rowIdx].append(new QGraphicsPixmapItem(m_battleMap->getBattleMapSquarePixmap(rowIdx, columnIdx)));

            /* make Battle Mal square selectable */
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setFlag(QGraphicsItem::ItemIsSelectable, true);

            /* set graphics item of Battle Map square to background layer */
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setZValue(ZValueBackgroundedGraphicsItem);

            /* append graphics item of coverage rectangle to row of nested QList member variable m_coverageGraphicsItems */
            m_coverageGraphicsItems[rowIdx].append(new QGraphicsRectItem(m_battleMap->getBattleMapSquarePixmap(rowIdx, columnIdx).rect()));
            m_coverageGraphicsItems[rowIdx][columnIdx]->setBrush(QBrush(BATTLEMAPSQUARECOVERED_COLOR));
            m_coverageGraphicsItems[rowIdx][columnIdx]->setPen(Qt::NoPen);
            m_coverageGraphicsItems[rowIdx][columnIdx]->setVisible(false);

            /* set graphics item of Battle Map square to coverage layer */
            m_coverageGraphicsItems[rowIdx][columnIdx]->setZValue(ZValueCoverageGraphicsItem);

        }
    }
}

/*!
 * \brief This function updates the Battle Map scene section.
 */
void MasterScreenHandler::updateBattleMapSceneSection()
{
    /* update rect that frames the Battle Map scene section to be displayed on the player screen */
    m_sceneSectionRect.setRect(QRectF(QPointF(m_battleMapSceneSection->getIndexFirstColumnSceneSection(), m_battleMapSceneSection->getIndexFirstRowSceneSection()) * CONFIG_BATTLEMAPSQUARE_SIZE,
                                      QSize(m_battleMapSceneSection->getNumberColumnsSceneSection(), m_battleMapSceneSection->getNumberRowsSceneSection()) * CONFIG_BATTLEMAPSQUARE_SIZE));

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* update opacity of Battle Map squares depending on whether they are displayed on the player screen */
            if ((rowIdx < m_battleMapSceneSection->getIndexFirstRowSceneSection()) || (m_battleMapSceneSection->getIndexFirstRowSceneSection() + m_battleMapSceneSection->getNumberRowsSceneSection() - 1U < rowIdx) ||
                    (columnIdx < m_battleMapSceneSection->getIndexFirstColumnSceneSection()) || (m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection() - 1U < columnIdx))
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
    /* remove all graphics items from Battle Map scene */
    for (QGraphicsItem * item : m_battleMapScene->items())
    {
        m_battleMapScene->removeItem(item);
    }

    delete m_battleMapScene;
}

/*!
 * \brief This function handles the selection of some Battle Map squares.
 */
void MasterScreenHandler::handleSelect(QPointF positionPress, QPointF positionRelease)
{
    /* check whether Ctrl key on keyboard is pressed and set item selection operation accordingly */
    Qt::ItemSelectionOperation itemSelectionOperation;
    if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier))
    {
        itemSelectionOperation = Qt::AddToSelection;
    }
    else
    {
        itemSelectionOperation = Qt::ReplaceSelection;
    }

    if (positionPress == positionRelease)
    {
        /* reset selection area if single Battle Map square has been selected and respective item selection operation is set */
        if (itemSelectionOperation == Qt::ReplaceSelection)
        {
            resetSelectionArea();
        }

        /* select single Battle Map square positioned at mouse button click position */
        for (QGraphicsItem * item : m_battleMapScene->items(positionPress))
        {
            item->setSelected(true);
        }
    }
    else
    {
        /* select multiple Battle Map squares positioned in selection area */
        QPainterPath path;
        path.addRect(QRectF(positionPress, positionRelease));
        m_battleMapScene->setSelectionArea(path, itemSelectionOperation);
    }

    /* stack selected items on top of unselected items so that selection rectangle is completely visible */
    for (QGraphicsItem * item : m_battleMapScene->items())
    {
        if (item->isSelected())
        {
            item->setZValue(ZValueSelectedGraphicsItem);
        }
        else
        {
            if (item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
            {
                item->setZValue(ZValueBackgroundedGraphicsItem);
            }
        }
    }

    /* stack Battle Map scene section rectangle on top of all other items */
    m_sceneSectionRect.setZValue(ZValueForegroundedGraphicsItem);

    /* determine indexes of rows and columns limiting selection area */
    qint32 firstSelectedRowIdx = -1;
    qint32 lastSelectedRowIdx = -1;
    qint32 firstSelectedColumnIdx = -1;
    qint32 lastSelectedColumnIdx = -1;
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            if (m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->isSelected())
            {
                /* set index of first selected row, no update required */
                if (0 > firstSelectedRowIdx)
                {
                    firstSelectedRowIdx = rowIdx;
                }

                /* set index of last selected row, update for each selected graphics item */
                lastSelectedRowIdx = rowIdx;

                /* set index of first selected column, update if selected graphics item is left to previous index of first selected column */
                if (0 > firstSelectedColumnIdx || static_cast<qint32>(columnIdx) < firstSelectedColumnIdx)
                {
                    firstSelectedColumnIdx = columnIdx;
                }

                /* set index of last selected column, update if selected graphics item is right to previous index of last selected column */
                if (lastSelectedColumnIdx < static_cast<qint32>(columnIdx))
                {
                    lastSelectedColumnIdx = columnIdx;
                }
            }
        }
    }

    /* check if selection is copyable */
    bool selectionCopyable = (lastSelectedRowIdx - firstSelectedRowIdx + 1) * (lastSelectedColumnIdx - firstSelectedColumnIdx + 1) == m_battleMapScene->selectedItems().count();

    emit changedSelection(selectionCopyable);
}

/*!
 * \brief This function resets the selection area.
 */
void MasterScreenHandler::resetSelectionArea()
{
    /* unselect selected graphics items and set unselected items to background layer */
    for (QGraphicsItem * selectedItem : m_battleMapScene->selectedItems())
    {
        selectedItem->setSelected(false);
        selectedItem->setZValue(ZValueBackgroundedGraphicsItem);
    }

    emit changedSelection(false);
}
