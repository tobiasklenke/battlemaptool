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
    m_battleMapSquaresGraphicsItems(QList<QList<CustomGraphicsPixmapItem*>>()),
    m_edgeLengthInPixels(static_cast<quint32>(calcNumberPixelsPerInch(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()))),
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
    deleteBattleMapSquaresGraphicsItems();
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
    updateBattleMapSquaresGraphicsItems();
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
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * m_edgeLengthInPixels, rowIdx * m_edgeLengthInPixels);
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setVisible(false);

            /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setZValue(BACKGROUNDEDGRAPHICSITEM_ZVALUE);

             /* add Battle Map square to Battle Map scene */
            m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]);
        }
    }

    /* initialize Battle Map scene rect according to Battle Map scene section */
    m_battleMapScene->setSceneRect(QRectF(QPointF(m_battleMapSceneSection->getIndexFirstColumnSceneSection(), m_battleMapSceneSection->getIndexFirstRowSceneSection()) * m_edgeLengthInPixels,
                                         QSizeF(m_battleMapSceneSection->getNumberColumnsSceneSection(), m_battleMapSceneSection->getNumberRowsSceneSection()) * m_edgeLengthInPixels));

    /* add and position wind rose graphics item */
    m_battleMapScene->addItem(&m_windRoseGraphicsItem);
    m_windRoseGraphicsItem.setPos((m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection() - WINDROSESIZE_BATTLEMAPSQUARES) * m_edgeLengthInPixels,
                                  m_battleMapSceneSection->getIndexFirstRowSceneSection() * m_edgeLengthInPixels);
}

/*!
 * \brief This function updates the Battle Map image.
 */
void PlayerScreenHandler::updateBattleMapImage()
{
    if (m_repositioningRequired)
    {
        /* reposition Battle Map squares on Battle Map scene */
        for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
        {
            for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
            {
                m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * m_edgeLengthInPixels, rowIdx * m_edgeLengthInPixels);
            }
        }
        m_repositioningRequired = false;
    }

    /* update visibility and opacity of Battle Map squares */
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
 * \brief This function inserts a new Battle Map row.
 */
void PlayerScreenHandler::insertRow(int rowPosition)
{
    /* insert row in nested QList member variable m_battleMapSquaresGraphicsItems */
    m_battleMapSquaresGraphicsItems.insert(rowPosition, QList<CustomGraphicsPixmapItem*>());

    for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
    {
        /* append graphics item of Battle Map square to row of nested QList member variable m_battleMapSquaresGraphicsItems */
        QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(rowPosition, columnIdx).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
        m_battleMapSquaresGraphicsItems[rowPosition].append(new CustomGraphicsPixmapItem(scaledPixmap));
        m_battleMapSquaresGraphicsItems[rowPosition][columnIdx]->setVisible(false);

        /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
        m_battleMapSquaresGraphicsItems[rowPosition][columnIdx]->setZValue(BACKGROUNDEDGRAPHICSITEM_ZVALUE);

        /* add Battle Map square to Battle Map scene */
        m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowPosition][columnIdx]);
    }

    /* reposition of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
}

/*!
 * \brief This function inserts a new Battle Map column.
 */
void PlayerScreenHandler::insertColumn(int columnPosition)
{
    /* insert column in nested QList member variable m_battleMapSquaresGraphicsItems */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* insert graphics item of Battle Map square in row of nested QList member variable m_battleMapSquaresGraphicsItems */
        QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(rowIdx, columnPosition).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
        m_battleMapSquaresGraphicsItems[rowIdx].insert(columnPosition, new CustomGraphicsPixmapItem(scaledPixmap));
        m_battleMapSquaresGraphicsItems[rowIdx][columnPosition]->setVisible(false);

        /* put Battle Map square graphics items to background so that wind rose graphics item is completely visible */
        m_battleMapSquaresGraphicsItems[rowIdx][columnPosition]->setZValue(BACKGROUNDEDGRAPHICSITEM_ZVALUE);

        /* add Battle Map squares to Battle Map scene */
        m_battleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx][columnPosition]);
    }

    /* reposition of Battle Map squares on Battle Map scene is required on next update of Battle Map image */
    m_repositioningRequired = true;
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
void PlayerScreenHandler::deleteBattleMapSquaresGraphicsItems()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquaresGraphicsItems.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquaresGraphicsItems[rowIdx].count(); columnIdx++)
        {
            /* delete graphics items */
            delete m_battleMapSquaresGraphicsItems[rowIdx][columnIdx];
        }
    }

    /* remove all graphics items from list */
    m_battleMapSquaresGraphicsItems.clear();
}

/*!
 * \brief This function updates the graphics items of the Battle Map squares.
 */
void PlayerScreenHandler::updateBattleMapSquaresGraphicsItems()
{
    /* delete Battle Map squares of previous Battle Map */
    deleteBattleMapSquaresGraphicsItems();

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* append row to nested QList member variable m_battleMapSquaresGraphicsItems if row does not already exist */
        if (rowIdx + 1 > m_battleMapSquaresGraphicsItems.count())
        {
            m_battleMapSquaresGraphicsItems.append(QList<CustomGraphicsPixmapItem*>());
        }

        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* append graphics item of Battle Map square to row of nested QList member variable m_battleMapSquaresGraphicsItems */
            QPixmap scaledPixmap = m_battleMap->getBattleMapSquarePixmap(rowIdx, columnIdx).scaled(QSize(m_edgeLengthInPixels, m_edgeLengthInPixels));
            m_battleMapSquaresGraphicsItems[rowIdx].append(new CustomGraphicsPixmapItem(scaledPixmap));
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
                m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setVisible(false);
            }
            else
            {
                /* make Battle Map square visible if it is to be displayed on player screen */
                m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setVisible(true);
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
            if (m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->isVisible())
            {
                /* Battle Map square is visible and therefore located within displayed Battle Map scene section */
                if (m_battleMap->getBattleMapSquareCovered(rowIdx, columnIdx))
                {
                    /* Cover Battle Map square */
                    m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUARECOVERED_OPACITY);
                }
                else
                {
                    if (BATTLEMAPSQUARECOVERED_OPACITY == m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->opacity())
                    {
                        /* Uncover Battle Map square gradually since it is located within displayed Battle Map scene section */
                        QPropertyAnimation * opacityAnimation = new QPropertyAnimation(m_battleMapSquaresGraphicsItems[rowIdx][columnIdx], "opacity");
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
                    m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUARECOVERED_OPACITY);
                }
                else
                {
                    /* Uncover Battle Map square immediately since it is located outside displayed Battle Map scene section */
                    m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUAREUNCOVERED_OPACITY);
                }
            }
        }
    }

    /* start opacity animation and delete it when stopped */
    opacityAnimationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}
