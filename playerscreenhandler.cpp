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
    pBattleMapSceneSection(nullptr),
    pBattleMapScene(new BattleMapScenePlayerScreen()),
    m_operationMode(Select),
    m_battleMapSquaresGraphicsItems(QList<QList<CustomGraphicsPixmapItem*>>()),
    m_pixelsPerBattleMapSquare(static_cast<quint32>(calcNumberPixelsPerInch(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width())))
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
    pGraphicsView->setEnabled(false);
    pGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
 * \brief This function sets the address of the member variable pBattleMapSceneSection.
 */
void PlayerScreenHandler::setBattleMapSceneSection(BattleMapSceneSection *battleMapSceneSection)
{
    pBattleMapSceneSection = battleMapSceneSection;
}

/*!
 * \brief This function sets the operation mode.
 */
void PlayerScreenHandler::setOperationMode(operationMode_t operationMode)
{
    m_operationMode = operationMode;

    QCursor cursor;

    switch (operationMode)
    {
    case Select:
        cursor = Qt::ArrowCursor;
        break;
    case CoverBattleMap:
        /* This mode is not supported on the player screen. */
        cursor = Qt::ArrowCursor;
        break;
    case UncoverBattleMap:
        /* This mode is not supported on the player screen. */
        cursor = Qt::ArrowCursor;
        break;
    default:
        cursor = Qt::ArrowCursor;
        break;
    }

    pGraphicsView->viewport()->setCursor(cursor);
}

/*!
 * \brief This function initializes the Battle Map image without showing it.
 */
void PlayerScreenHandler::initBattleMapImage()
{
    /* reset Battle Map scene */
    deleteBattleMapScene();
    pBattleMapScene = new BattleMapScenePlayerScreen();
    pGraphicsView->setScene(pBattleMapScene);



    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * m_pixelsPerBattleMapSquare, rowIdx * m_pixelsPerBattleMapSquare);
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setVisible(false);
            pBattleMapScene->addItem(m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]);
        }
    }

    pBattleMapScene->setSceneRect(QRectF(QPointF(pBattleMapSceneSection->getIndexFirstColumnSceneSection(), pBattleMapSceneSection->getIndexFirstRowSceneSection()) * m_pixelsPerBattleMapSquare,
                                         QSizeF(pBattleMapSceneSection->getNumberColumnsSceneSection(), pBattleMapSceneSection->getNumberRowsSceneSection()) * m_pixelsPerBattleMapSquare));
}

/*!
 * \brief This function updates the Battle Map image.
 */
void PlayerScreenHandler::updateBattleMapImage()
{
    pGraphicsView->setEnabled(true);

    updateBattleMapSquaresVisibility();

    updateBattleMapSquaresOpacity();
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
            m_battleMapSquaresGraphicsItems.append(QList<CustomGraphicsPixmapItem*>());
        }

        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            /* append graphics item of Battle Map square to row of nested QList member variable m_battleMapSquaresGraphicsItems */
            QPixmap scaledPixmap = pBattleMap->getBattleMapSquarePixmap(rowIdx, columnIdx).scaled(QSize(m_pixelsPerBattleMapSquare, m_pixelsPerBattleMapSquare));
            m_battleMapSquaresGraphicsItems[rowIdx].append(new CustomGraphicsPixmapItem(scaledPixmap));
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

/*!
 * \brief This function updates the visibility of the Battle Map squares depending on whether they are displayed on the player screen.
 */
void PlayerScreenHandler::updateBattleMapSquaresVisibility()
{
    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            if ((rowIdx < pBattleMapSceneSection->getIndexFirstRowSceneSection()) || (pBattleMapSceneSection->getIndexFirstRowSceneSection() + pBattleMapSceneSection->getNumberRowsSceneSection() - 1U < rowIdx) ||
                    (columnIdx < pBattleMapSceneSection->getIndexFirstColumnSceneSection()) || (pBattleMapSceneSection->getIndexFirstColumnSceneSection() + pBattleMapSceneSection->getNumberColumnsSceneSection() - 1U < columnIdx))
            {
                m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setVisible(false);
            }
            else
            {
                m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setVisible(true);
            }
        }
    }

    pBattleMapScene->setSceneRect(QRectF(QPointF(pBattleMapSceneSection->getIndexFirstColumnSceneSection(), pBattleMapSceneSection->getIndexFirstRowSceneSection()) * m_pixelsPerBattleMapSquare,
                                         QSizeF(pBattleMapSceneSection->getNumberColumnsSceneSection(), pBattleMapSceneSection->getNumberRowsSceneSection()) * m_pixelsPerBattleMapSquare));
}

/*!
 * \brief This function updates the opacity of the Battle Map squares depending on whether they are covered.
 */
void PlayerScreenHandler::updateBattleMapSquaresOpacity()
{
    QParallelAnimationGroup *opacityAnimationGroup = new QParallelAnimationGroup();
    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            if (m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->isVisible())
            {
                /* Battle Map square is visible and therefore located within the displayed Battle Map scene section */
                if (pBattleMap->getBattleMapSquareCovered(rowIdx, columnIdx))
                {
                    /* Cover Battle Map square */
                    m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUARECOVERED_OPACITY);
                }
                else
                {
                    if (BATTLEMAPSQUARECOVERED_OPACITY == m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->opacity())
                    {
                        /* Uncover Battle Map square gradually since it is located within the displayed Battle Map scene section */
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
                /* Battle Map square is invisible and therefore located outside the displayed Battle Map scene section */
                if (pBattleMap->getBattleMapSquareCovered(rowIdx, columnIdx))
                {
                    /* Cover Battle Map square */
                    m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUARECOVERED_OPACITY);
                }
                else
                {
                    /* Uncover Battle Map square immediately since it is located outside the displayed Battle Map scene section */
                    m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUAREUNCOVERED_OPACITY);
                }
            }
        }
    }

    opacityAnimationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}
