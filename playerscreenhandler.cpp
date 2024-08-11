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
    m_graphicsView(nullptr),
    m_battleMap(nullptr),
    m_battleMapSceneSection(nullptr),
    m_battleMapScene(new BattleMapScenePlayerScreen()),
    m_operationMode(Select),
    m_battleMapSquareGraphicsItems(QList<QList<CustomGraphicsPixmapItem*>>()),
    m_deleteRowsOnUpdate(QList<bool>()),
    m_deleteColumnsOnUpdate(QList<bool>()),
    m_edgeLengthInPixels(static_cast<quint32>(calcNumberPixelsPerInch(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()))),
    m_deletionRequired(false),
    m_repositioningRequired(false)
{
    m_windRoseGraphicsItem.setVisible(false);
}

/*!
 * \brief This function is the destructor of the class PlayerScreenHandler.
 */
PlayerScreenHandler::~PlayerScreenHandler()
{
    /* delete objects created in the constructor */
    deleteBattleMapScene();
    deleteBattleMapSquareGraphicsItems();
}

/*!
 * \brief This function sets the address of the member variable m_graphicsView.
 */
void PlayerScreenHandler::setGraphicsView(QGraphicsView *graphicsView)
{
    m_graphicsView = graphicsView;

    /* set background color of graphics view to black and remove frame */
    m_graphicsView->setBackgroundBrush(QBrush(Qt::black));
    m_graphicsView->setFrameStyle(QFrame::NoFrame);

    /* remove scroll bars from graphics view */
    m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* set Battle Map scene to graphics view */
    m_graphicsView->setScene(m_battleMapScene);
}

/*!
 * \brief This function sets the address of the member variable m_battleMap.
 */
void PlayerScreenHandler::setBattleMap(BattleMap *battleMap)
{
    m_battleMap = battleMap;

    /* update Battle Map square graphics items according to set Battle Map */
    updateBattleMapSquareGraphicsItems();
}

/*!
 * \brief This function sets the address of the member variable m_battleMapSceneSection.
 */
void PlayerScreenHandler::setBattleMapSceneSection(BattleMapSceneSection *battleMapSceneSection)
{
    m_battleMapSceneSection = battleMapSceneSection;
}

/*!
 * \brief This function sets the operation mode.
 */
void PlayerScreenHandler::setOperationMode(operationMode_t operationMode)
{
    m_operationMode = operationMode;

    /* set cursor according to operation mode */
    QCursor cursor;
    switch (operationMode)
    {
    case Select:
        cursor = Qt::ArrowCursor;
        break;
    case CoverBattleMap:
        /* mode is not supported on the player screen */
        cursor = Qt::ArrowCursor;
        break;
    case UncoverBattleMap:
        /* mode is not supported on the player screen */
        cursor = Qt::ArrowCursor;
        break;
    default:
        cursor = Qt::ArrowCursor;
        break;
    }
    m_graphicsView->viewport()->setCursor(cursor);
}

/*!
 * \brief This function initializes the Battle Map image without showing it.
 */
void PlayerScreenHandler::initBattleMapImage()
{
    /* reset Battle Map scene */
    deleteBattleMapScene();
    m_battleMapScene = new BattleMapScenePlayerScreen();
    m_graphicsView->setScene(m_battleMapScene);

    /* add Battle Map squares to Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* position Battle Map square on Battle Map scene and make Battle Map square invisible */
            m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * m_edgeLengthInPixels, rowIdx * m_edgeLengthInPixels);
            m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setVisible(false);

            /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
            m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setZValue(ZValueBackgroundedGraphicsItem);

             /* add Battle Map square to Battle Map scene */
            m_battleMapScene->addItem(m_battleMapSquareGraphicsItems[rowIdx][columnIdx]);
        }
    }

    /* initialize Battle Map scene rect according to Battle Map scene section */
    m_battleMapScene->setSceneRect(QRectF(QPointF(m_battleMapSceneSection->getIndexFirstColumnSceneSection(), m_battleMapSceneSection->getIndexFirstRowSceneSection()) * m_edgeLengthInPixels,
                                         QSizeF(m_battleMapSceneSection->getNumberColumnsSceneSection(), m_battleMapSceneSection->getNumberRowsSceneSection()) * m_edgeLengthInPixels));

    /* initialize m_deleteRowsOnUpdate and m_deleteColumnsOnUpdate */
    m_deleteRowsOnUpdate.clear();
    m_deleteColumnsOnUpdate.clear();
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        m_deleteRowsOnUpdate.append(false);
    }
    for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
    {
        m_deleteColumnsOnUpdate.append(false);
    }

    /* add and position wind rose graphics item */
    m_battleMapScene->addItem(&m_windRoseGraphicsItem);
    m_windRoseGraphicsItem.setPos((m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection() - WINDROSESIZE_BATTLEMAPSQUARES) * m_edgeLengthInPixels,
                                  m_battleMapSceneSection->getIndexFirstRowSceneSection() * m_edgeLengthInPixels);

    /* put wind rose graphics items to foreground */
    m_windRoseGraphicsItem.setZValue(ZValueForegroundedGraphicsItem);
}

/*!
 * \brief This function updates the Battle Map image.
 */
void PlayerScreenHandler::updateBattleMapImage()
{
    if (m_deletionRequired)
    {
        /* delete Battle Map squares to be deleted from Battle Map scene */
        deleteGraphicsItemsFromBattleMapScene();

        /* deletion is done */
        m_deletionRequired = false;
    }

    if (m_repositioningRequired)
    {
        /* reposition Battle Map squares on Battle Map scene */
        repositionGraphicsItemsOnBattleMapScene();

        /* repositioning is done */
        m_repositioningRequired = false;
    }

    /* update pixmaps, visibility and opacity of Battle Map squares */
    updateBattleMapSquaresPixmaps();
    updateBattleMapSquaresVisibility();
    updateBattleMapSquaresOpacity();

    /* update Battle Map scene rect according to Battle Map scene section */
    m_battleMapScene->setSceneRect(QRectF(QPointF(m_battleMapSceneSection->getIndexFirstColumnSceneSection(), m_battleMapSceneSection->getIndexFirstRowSceneSection()) * m_edgeLengthInPixels,
                                         QSizeF(m_battleMapSceneSection->getNumberColumnsSceneSection(), m_battleMapSceneSection->getNumberRowsSceneSection()) * m_edgeLengthInPixels));

    /* update position of wind rose graphics item */
    m_windRoseGraphicsItem.setPos((m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection() - WINDROSESIZE_BATTLEMAPSQUARES) * m_edgeLengthInPixels,
                                  m_battleMapSceneSection->getIndexFirstRowSceneSection() * m_edgeLengthInPixels);
}

/*!
 * \brief This function inserts a new row above the Battle Map.
 */
void PlayerScreenHandler::insertRowAbove()
{
    /* insert new row above Battle Map */
    m_battleMapSquareGraphicsItems.prepend(QList<CustomGraphicsPixmapItem*>());

    /* columnIdx only considers columns that shall not be deleted on update */
    quint32 columnIdx = 0U;

    /* totalColumnIdx considers all columns, including those that shall be deleted on update */
    for (quint32 totalColumnIdx = 0U; totalColumnIdx < m_deleteColumnsOnUpdate.count(); totalColumnIdx++)
    {
        if (m_deleteColumnsOnUpdate[totalColumnIdx])
        {
            /* append empty graphics item since row shall be deleted on update */
            m_battleMapSquareGraphicsItems.first().append(new CustomGraphicsPixmapItem());
        }
        else
        {
            /* append graphics item of Battle Map square to row */
            QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(0U, columnIdx).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
            m_battleMapSquareGraphicsItems.first().append(new CustomGraphicsPixmapItem(scaledPixmap));
            m_battleMapSquareGraphicsItems.first()[totalColumnIdx]->setVisible(false);

            /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
            m_battleMapSquareGraphicsItems.first()[totalColumnIdx]->setZValue(ZValueBackgroundedGraphicsItem);

            /* add Battle Map square to Battle Map scene */
            m_battleMapScene->addItem(m_battleMapSquareGraphicsItems.first()[totalColumnIdx]);

            /* increment column index of Battle Map */
            columnIdx++;
        }
    }

    /* add row to m_deleteRowsOnUpdate that shall not be deleted on update */
    m_deleteRowsOnUpdate.prepend(false);

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function inserts a new row below the Battle Map.
 */
void PlayerScreenHandler::insertRowBelow()
{
    /* insert new row below Battle Map */
    m_battleMapSquareGraphicsItems.append(QList<CustomGraphicsPixmapItem*>());

    /* columnIdx only considers columns that shall not be deleted on update */
    quint32 columnIdx = 0U;

    /* totalColumnIdx considers all columns, including those that shall be deleted on update */
    for (quint32 totalColumnIdx = 0U; totalColumnIdx < m_deleteColumnsOnUpdate.count(); totalColumnIdx++)
    {
        if (m_deleteColumnsOnUpdate[totalColumnIdx])
        {
            /* append empty graphics item since row shall be deleted on update */
            m_battleMapSquareGraphicsItems.last().append(new CustomGraphicsPixmapItem());
        }
        else
        {
            /* append graphics item of Battle Map square to row */
            QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(m_battleMap->getNumberRows() - 1U, columnIdx).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
            m_battleMapSquareGraphicsItems.last().append(new CustomGraphicsPixmapItem(scaledPixmap));
            m_battleMapSquareGraphicsItems.last()[totalColumnIdx]->setVisible(false);

            /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
            m_battleMapSquareGraphicsItems.last()[totalColumnIdx]->setZValue(ZValueBackgroundedGraphicsItem);

            /* add Battle Map square to Battle Map scene */
            m_battleMapScene->addItem(m_battleMapSquareGraphicsItems.last()[totalColumnIdx]);

            /* increment column index of Battle Map */
            columnIdx++;
        }
    }

    /* add row to m_deleteRowsOnUpdate that shall not be deleted on update */
    m_deleteRowsOnUpdate.append(false);

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function inserts a new column to the left of the Battle Map.
 */
void PlayerScreenHandler::insertColumnLeft()
{
    /* rowIdx only considers rows that shall not be deleted on update */
    quint32 rowIdx = 0U;

    /* insert new column to the left of Battle Map */
    /* totalRowIdx considers all rows, including those that shall be deleted on update */
    for (quint32 totalRowIdx = 0U; totalRowIdx < m_deleteRowsOnUpdate.count(); totalRowIdx++)
    {
        if (m_deleteRowsOnUpdate[totalRowIdx])
        {
            /* prepend empty graphics item since row shall be deleted on update */
            m_battleMapSquareGraphicsItems[totalRowIdx].prepend(new CustomGraphicsPixmapItem());
        }
        else
        {
            /* prepend graphics item of Battle Map square to column */
            QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(rowIdx, 0U).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
            m_battleMapSquareGraphicsItems[totalRowIdx].prepend(new CustomGraphicsPixmapItem(scaledPixmap));
            m_battleMapSquareGraphicsItems[totalRowIdx].first()->setVisible(false);

            /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
            m_battleMapSquareGraphicsItems[totalRowIdx].first()->setZValue(ZValueBackgroundedGraphicsItem);

            /* add Battle Map square to Battle Map scene */
            m_battleMapScene->addItem(m_battleMapSquareGraphicsItems[totalRowIdx].first());

            /* increment row index of Battle Map */
            rowIdx++;
        }
    }

    /* add column to m_deleteColumnsOnUpdate that shall not be deleted on update */
    m_deleteColumnsOnUpdate.prepend(false);

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function inserts a new column to the right of the Battle Map.
 */
void PlayerScreenHandler::insertColumnRight()
{
    /* rowIdx only considers rows that shall not be deleted on update */
    quint32 rowIdx = 0U;

    /* insert new column to the left of Battle Map */
    /* totalRowIdx considers all rows, including those that shall be deleted on update */
    for (quint32 totalRowIdx = 0U; totalRowIdx < m_deleteRowsOnUpdate.count(); totalRowIdx++)
    {
        if (m_deleteRowsOnUpdate[totalRowIdx])
        {
            /* append empty graphics item since row shall be deleted on update */
            m_battleMapSquareGraphicsItems[totalRowIdx].append(new CustomGraphicsPixmapItem());
        }
        else
        {
            /* append graphics item of Battle Map square to column */
            QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(rowIdx, m_battleMap->getNumberColumns() - 1U).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
            m_battleMapSquareGraphicsItems[totalRowIdx].append(new CustomGraphicsPixmapItem(scaledPixmap));
            m_battleMapSquareGraphicsItems[totalRowIdx].last()->setVisible(false);

            /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
            m_battleMapSquareGraphicsItems[totalRowIdx].last()->setZValue(ZValueBackgroundedGraphicsItem);

            /* add Battle Map square to Battle Map scene */
            m_battleMapScene->addItem(m_battleMapSquareGraphicsItems[totalRowIdx].last());

            /* increment row index of Battle Map */
            rowIdx++;
        }
    }

    /* add column to m_deleteColumnsOnUpdate that shall not be deleted on update */
    m_deleteColumnsOnUpdate.append(false);

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function prepares the deletion of a row above the Battle Map.
 */
void PlayerScreenHandler::deleteRowAbove()
{
    /* set row from m_deleteRowsOnUpdate that shall be deleted on update */
    for (quint32 rowIdx = 0U; rowIdx < m_deleteRowsOnUpdate.count(); rowIdx++)
    {
        /* search first row in list that shall not be deleted until now */
        if (!m_deleteRowsOnUpdate[rowIdx])
        {
            m_deleteRowsOnUpdate[rowIdx] = true;
            break;
        }
    }

    /* deletion of Battle Map squares from Battle Map scene is required on next update of Battle Map image */
    m_deletionRequired = true;

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function prepares the deletion of a row below the Battle Map.
 */
void PlayerScreenHandler::deleteRowBelow()
{
    /* set row from m_deleteRowsOnUpdate that shall be deleted on update */
    for (quint32 rowIdx = 0U; rowIdx < m_deleteRowsOnUpdate.count(); rowIdx++)
    {
        /* search last row in list that shall not be deleted until now */
        if (!m_deleteRowsOnUpdate[m_deleteRowsOnUpdate.count() -1U - rowIdx])
        {
            m_deleteRowsOnUpdate[m_deleteRowsOnUpdate.count() -1U - rowIdx] = true;
            break;
        }
    }

    /* deletion of Battle Map squares from Battle Map scene is required on next update of Battle Map image */
    m_deletionRequired = true;

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function prepares the deletion of a column to the left of the Battle Map.
 */
void PlayerScreenHandler::deleteColumnLeft()
{
    /* set column from m_deleteColumnsOnUpdate that shall be deleted on update */
    for (quint32 columnIdx = 0U; columnIdx < m_deleteColumnsOnUpdate.count(); columnIdx++)
    {
        /* search first column in list that shall not be deleted until now */
        if (!m_deleteColumnsOnUpdate[columnIdx])
        {
            m_deleteColumnsOnUpdate[columnIdx] = true;
            break;
        }
    }

    /* deletion of Battle Map squares from Battle Map scene is required on next update of Battle Map image */
    m_deletionRequired = true;

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function prepares the deletion of a column to the right of the Battle Map.
 */
void PlayerScreenHandler::deleteColumnRight()
{
    /* set column from m_deleteColumnsOnUpdate that shall be deleted on update */
    for (quint32 columnIdx = 0U; columnIdx < m_deleteColumnsOnUpdate.count(); columnIdx++)
    {
        /* search last column in list that shall not be deleted until now */
        if (!m_deleteColumnsOnUpdate[m_deleteColumnsOnUpdate.count() - 1U - columnIdx])
        {
            m_deleteColumnsOnUpdate[m_deleteColumnsOnUpdate.count() - 1U - columnIdx] = true;
            break;
        }
    }

    /* deletion of Battle Map squares from Battle Map scene is required on next update of Battle Map image */
    m_deletionRequired = true;

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function prepares the left rotation of the Battle Map.
 */
void PlayerScreenHandler::rotateBattleMapLeft()
{
    /* get new lists of rows and columns to be deleted */
    QList<bool> newDeleteRowsOnUpdate = m_deleteColumnsOnUpdate;
    QList<bool> newDeleteColumnsOnUpdate = m_deleteRowsOnUpdate;

    /* resort Battle Map squares  */
    QList<QList<CustomGraphicsPixmapItem*>> newBattleMapSquareGraphicsItems;
    for (quint32 rowIdx = 0U; rowIdx < newDeleteRowsOnUpdate.count(); rowIdx++)
    {
        newBattleMapSquareGraphicsItems.append(QList<CustomGraphicsPixmapItem*>());
        for (quint32 columnIdx = 0U; columnIdx < newDeleteColumnsOnUpdate.count(); columnIdx++)
        {
            newBattleMapSquareGraphicsItems.last().append(m_battleMapSquareGraphicsItems[columnIdx][newDeleteRowsOnUpdate.count() - rowIdx - 1U]);
        }
    }

    /* update variables */
    m_deleteRowsOnUpdate = newDeleteRowsOnUpdate;
    m_deleteColumnsOnUpdate = newDeleteColumnsOnUpdate;
    m_battleMapSquareGraphicsItems = newBattleMapSquareGraphicsItems;

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function prepares the right rotation of the Battle Map.
 */
void PlayerScreenHandler::rotateBattleMapRight()
{
    /* get new lists of rows and columns to be deleted */
    QList<bool> newDeleteRowsOnUpdate = m_deleteColumnsOnUpdate;
    QList<bool> newDeleteColumnsOnUpdate = m_deleteRowsOnUpdate;

    /* resort Battle Map squares  */
    QList<QList<CustomGraphicsPixmapItem*>> newBattleMapSquareGraphicsItems;
    for (quint32 rowIdx = 0U; rowIdx < newDeleteRowsOnUpdate.count(); rowIdx++)
    {
        newBattleMapSquareGraphicsItems.append(QList<CustomGraphicsPixmapItem*>());
        for (quint32 columnIdx = 0U; columnIdx < newDeleteColumnsOnUpdate.count(); columnIdx++)
        {
            newBattleMapSquareGraphicsItems.last().append(m_battleMapSquareGraphicsItems[newDeleteColumnsOnUpdate.count() - columnIdx - 1U][rowIdx]);
        }
    }

    /* update variables */
    m_deleteRowsOnUpdate = newDeleteRowsOnUpdate;
    m_deleteColumnsOnUpdate = newDeleteColumnsOnUpdate;
    m_battleMapSquareGraphicsItems = newBattleMapSquareGraphicsItems;

    /* repositioning of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function deletes the Battle Map squares to be deleted from the Battle Map scene.
 */
void PlayerScreenHandler::deleteGraphicsItemsFromBattleMapScene()
{
    /* determine numbers of rows and columns in lists m_deleteRowsOnUpdate and m_deleteColumnsOnUpdate since numbers can alter in case of deletion */
    quint32 numberRows = m_deleteRowsOnUpdate.count();
    quint32 numberColumns = m_deleteColumnsOnUpdate.count();

    /* delete Battle Map rows from Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < numberRows; rowIdx++)
    {
        /* handle rows from behind so that indexing is not affected afterwards */
        quint32 rowToHandle = numberRows - 1U - rowIdx;

        if (m_deleteRowsOnUpdate[rowToHandle])
        {
            for (quint32 columnIdx = 0U; columnIdx < numberColumns; columnIdx++)
            {
                /* handle columns from behind so that indexing is not affected afterwards */
                quint32 columnToHandle = numberColumns - 1U - columnIdx;

                /* remove Battle Map square from Battle Map scene */
                if (m_battleMapScene->items().contains(m_battleMapSquareGraphicsItems[rowToHandle][columnToHandle]))
                {
                    m_battleMapScene->removeItem(m_battleMapSquareGraphicsItems[rowToHandle][columnToHandle]);
                }

                delete m_battleMapSquareGraphicsItems[rowToHandle][columnToHandle];
            }

            m_battleMapSquareGraphicsItems.removeAt(rowToHandle);
            m_deleteRowsOnUpdate.removeAt(rowToHandle);
        }
    }

    /* update number of rows in list m_deleteRowsOnUpdate since number could habe altered in case of deletion */
    numberRows = m_deleteRowsOnUpdate.count();

    /* delete Battle Map columns from Battle Map scene */
    for (quint32 columnIdx = 0U; columnIdx < numberColumns; columnIdx++)
    {
        /* handle columns from behind so that indexing is not affected afterwards */
        quint32 columnToHandle = numberColumns - 1U - columnIdx;

        if (m_deleteColumnsOnUpdate[columnToHandle])
        {
            for (quint32 rowIdx = 0U; rowIdx < numberRows; rowIdx++)
            {
                /* handle rows from behind so that indexing is not affected afterwards */
                quint32 rowToHandle = numberRows - 1U - rowIdx;

                /* remove Battle Map square from Battle Map scene */
                if (m_battleMapScene->items().contains(m_battleMapSquareGraphicsItems[rowToHandle][columnToHandle]))
                {
                    m_battleMapScene->removeItem(m_battleMapSquareGraphicsItems[rowToHandle][columnToHandle]);
                }

                delete m_battleMapSquareGraphicsItems[rowToHandle][columnToHandle];
                m_battleMapSquareGraphicsItems[rowToHandle].removeAt(columnToHandle);
            }

            m_deleteColumnsOnUpdate.removeAt(columnToHandle);
        }
    }
}

/*!
 * \brief This function repositions the Battle Map squares on the Battle Map scene.
 */
void PlayerScreenHandler::repositionGraphicsItemsOnBattleMapScene()
{
    /* reposition Battle Map squares on Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * m_edgeLengthInPixels, rowIdx * m_edgeLengthInPixels);
        }
    }
}

/*!
 * \brief This function sets the visibility state of wind rose graphics item.
 */
void PlayerScreenHandler::setWindRoseGraphicsItemVisibility(bool visibile)
{
    m_windRoseGraphicsItem.setVisible(visibile);
}

/*!
 * \brief This function sets the pixmap of the wind rose graphics item.
 */
void PlayerScreenHandler::setWindRoseGraphicsItemPixmap(QPixmap pixmap)
{
    m_windRoseGraphicsItem.setPixmap(pixmap.scaled(WINDROSESIZE_BATTLEMAPSQUARES * QSize(m_edgeLengthInPixels, m_edgeLengthInPixels)));
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
void PlayerScreenHandler::deleteBattleMapSquareGraphicsItems()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquareGraphicsItems.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquareGraphicsItems[rowIdx].count(); columnIdx++)
        {
            /* delete graphics items */
            delete m_battleMapSquareGraphicsItems[rowIdx][columnIdx];
        }
    }

    /* remove all graphics items from list */
    m_battleMapSquareGraphicsItems.clear();
}

/*!
 * \brief This function updates the graphics items of the Battle Map squares.
 */
void PlayerScreenHandler::updateBattleMapSquareGraphicsItems()
{
    /* delete Battle Map squares of previous Battle Map */
    deleteBattleMapSquareGraphicsItems();

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* append row to nested QList member variable m_battleMapSquaresGraphicsItems if row does not already exist */
        if (rowIdx + 1 > m_battleMapSquareGraphicsItems.count())
        {
            m_battleMapSquareGraphicsItems.append(QList<CustomGraphicsPixmapItem*>());
        }

        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* append graphics item of Battle Map square to row of nested QList member variable m_battleMapSquaresGraphicsItems */
            QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(rowIdx, columnIdx).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
            m_battleMapSquareGraphicsItems[rowIdx].append(new CustomGraphicsPixmapItem(scaledPixmap));
        }
    }
}

/*!
 * \brief This function deletes the Battle Map scene.
 */
void PlayerScreenHandler::deleteBattleMapScene()
{
    /* remove all graphics items from Battle Map scene */
    for (QGraphicsItem * item : m_battleMapScene->items())
    {
        m_battleMapScene->removeItem(item);
    }

    delete m_battleMapScene;
}

/*!
 * \brief This function updates the pixmaps of the Battle Map squares.
 */
void PlayerScreenHandler::updateBattleMapSquaresPixmaps()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* update pixmaps of Battle Map squares */
            QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(rowIdx, columnIdx).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
            m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setPixmap(scaledPixmap);
        }
    }
}

/*!
 * \brief This function updates the visibility of the Battle Map squares depending on whether they are displayed on the player screen.
 */
void PlayerScreenHandler::updateBattleMapSquaresVisibility()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            if ((rowIdx < m_battleMapSceneSection->getIndexFirstRowSceneSection()) || (m_battleMapSceneSection->getIndexFirstRowSceneSection() + m_battleMapSceneSection->getNumberRowsSceneSection() - 1U < rowIdx) ||
                    (columnIdx < m_battleMapSceneSection->getIndexFirstColumnSceneSection()) || (m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection() - 1U < columnIdx))
            {
                /* make Battle Map square invisible if it is not to be displayed on player screen */
                m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setVisible(false);
            }
            else
            {
                /* make Battle Map square visible if it is to be displayed on player screen */
                m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setVisible(true);
            }
        }
    }
}

/*!
 * \brief This function updates the opacity of the Battle Map squares depending on whether they are covered.
 */
void PlayerScreenHandler::updateBattleMapSquaresOpacity()
{
    QParallelAnimationGroup *opacityAnimationGroup = new QParallelAnimationGroup();
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            if (m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->isVisible())
            {
                /* Battle Map square is visible and therefore located within displayed Battle Map scene section */
                if (m_battleMap->getBattleMapSquareCovered(rowIdx, columnIdx))
                {
                    /* Cover Battle Map square */
                    m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUARECOVERED_OPACITY);
                }
                else
                {
                    if (BATTLEMAPSQUARECOVERED_OPACITY == m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->opacity())
                    {
                        /* Uncover Battle Map square gradually since it is located within displayed Battle Map scene section */
                        QPropertyAnimation * opacityAnimation = new QPropertyAnimation(m_battleMapSquareGraphicsItems[rowIdx][columnIdx], "opacity");
                        opacityAnimation->setDuration(BATTLEMAPSQUAREOPACITYANIMATION_DURATION);
                        opacityAnimation->setStartValue(BATTLEMAPSQUARECOVERED_OPACITY);
                        opacityAnimation->setEndValue(BATTLEMAPSQUAREUNCOVERED_OPACITY);
                        opacityAnimationGroup->addAnimation(opacityAnimation);
                    }
                }
            }
            else
            {
                /* Battle Map square is invisible and therefore located outside displayed Battle Map scene section */
                if (m_battleMap->getBattleMapSquareCovered(rowIdx, columnIdx))
                {
                    /* Cover Battle Map square */
                    m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUARECOVERED_OPACITY);
                }
                else
                {
                    /* Uncover Battle Map square immediately since it is located outside displayed Battle Map scene section */
                    m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUAREUNCOVERED_OPACITY);
                }
            }
        }
    }

    /* start opacity animation and delete it when stopped */
    opacityAnimationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}
