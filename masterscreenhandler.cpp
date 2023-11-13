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
    pBattleMapSceneSection(nullptr),
    pBattleMapScene(new BattleMapSceneMasterScreen()),
    m_operationMode(Select),
    m_battleMapSquaresGraphicsItems(QList<QList<QGraphicsPixmapItem*>>()),
    m_scaleFactor(1.0)
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
    connect(pGraphicsView, SIGNAL(clicked_RightMouseButton(QPoint)), this, SLOT(clicked_RightMouseButton(QPoint)));

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
 * \brief This function sets the address of the member variable pBattleMapSceneSection.
 */
void MasterScreenHandler::setBattleMapSceneSection(BattleMapSceneSection *battleMapSceneSection)
{
    pBattleMapSceneSection = battleMapSceneSection;
}

/*!
 * \brief This function sets the operation mode.
 */
void MasterScreenHandler::setOperationMode(operationMode_t operationMode)
{
    m_operationMode = operationMode;

    /* Reset selection area */
    for (QGraphicsItem * item : pBattleMapScene->items())
    {
        item->setSelected(false);
        item->setZValue(0.0);
    }

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

    pGraphicsView->viewport()->setCursor(cursor);
}

/*!
 * \brief This function shows the Battle Map image.
 */
void MasterScreenHandler::showBattleMapImage()
{
    /* reset Battle Map scene */
    deleteBattleMapScene();
    pBattleMapScene = new BattleMapSceneMasterScreen();
    connect(pBattleMapScene, SIGNAL(selected_BattleMapSquares()), this, SLOT(selected_BattleMapSquares()));
    pGraphicsView->resetScaling();
    pGraphicsView->setScene(pBattleMapScene);
    pGraphicsView->setEventProcessingEnabled(true);

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

    pGraphicsView->setInteractive(true);
}

/*!
 * \brief This function handles the selection of some Battle Map squares in case of operation modes CoverBattleMap or UncoverBattleMap.
 */
void MasterScreenHandler::handleCoverBattleMap(bool covered)
{
    /* Get index of selected Battle Map squares and cover them */
    quint32 rowIdx = 0U;
    quint32 columnIdx = 0U;
    for (QGraphicsItem * selectedItem : pBattleMapScene->selectedItems())
    {
        for (rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
        {
            if (-1 < m_battleMapSquaresGraphicsItems[rowIdx].indexOf(selectedItem))
            {
                columnIdx = m_battleMapSquaresGraphicsItems[rowIdx].indexOf(selectedItem);
                break;
            }

        }

        /* Update coverage state and pixmap of Battle Map square */
        pBattleMap->setBattleMapSquareCovered(rowIdx, columnIdx, covered);

        QPixmap temporaryPixmap;
        if (covered)
        {
            /* Convert pixmap to grayscale and add transparent black layer in order to darken it */
            temporaryPixmap = QPixmap::fromImage(pBattleMap->getBattleMapSquarePixmap(rowIdx, columnIdx).toImage().convertToFormat(QImage::Format_Grayscale16));

            QPainter *painter = new QPainter(&temporaryPixmap);
            painter->setBrush(QBrush(BATTLEMAPSQUARECOVERED_COLOR));
            painter->drawRect(temporaryPixmap.rect());

            delete painter;
        }
        else
        {
            temporaryPixmap = pBattleMap->getBattleMapSquarePixmap(rowIdx, columnIdx);
        }
        m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setPixmap(temporaryPixmap);
    }

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
 * \brief This function updates the member variable m_scaleFactor and redraws the Battle Map section rect.
 */
void MasterScreenHandler::changed_ScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;

    m_sceneSectionRect.setPen(QPen(Qt::black, BATTLEMAPSECTIONFRAME_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine));

    pBattleMapScene->changed_ScaleFactor(scaleFactor);
}

/*!
 * \brief This function updates the member variables of the Battle Map scene section in case of an appropriate key press.
 */
void MasterScreenHandler::pressed_Key(Qt::Key key)
{
    QPointF scenePosCenter = pGraphicsView->mapToScene(pGraphicsView->viewport()->rect().center());
    qreal difference;

    switch(key)
    {
    case Qt::Key_Left:
        if (0U < pBattleMapSceneSection->getIndexFirstColumnSceneSection())
        {
            pBattleMapSceneSection->setIndexFirstColumnSceneSection(pBattleMapSceneSection->getIndexFirstColumnSceneSection() - 1U);
            updateBattleMapSceneSection();

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            difference = pGraphicsView->mapToScene(pGraphicsView->viewport()->rect().topLeft()).x() -
                    static_cast<qreal>(pBattleMapSceneSection->getIndexFirstColumnSceneSection() * CONFIG_BATTLEMAPSQUARE_SIZE);

            if (0 < difference)
            {
                pGraphicsView->centerOn(scenePosCenter.x() - difference, scenePosCenter.y());
            }
        }
        break;

    case Qt::Key_Up:
        if (0U < pBattleMapSceneSection->getIndexFirstRowSceneSection())
        {
            pBattleMapSceneSection->setIndexFirstRowSceneSection(pBattleMapSceneSection->getIndexFirstRowSceneSection() - 1U);
            updateBattleMapSceneSection();

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            difference = pGraphicsView->mapToScene(pGraphicsView->viewport()->rect().topLeft()).y() -
                     static_cast<qreal>(pBattleMapSceneSection->getIndexFirstRowSceneSection() * CONFIG_BATTLEMAPSQUARE_SIZE);

            if (0 < difference)
            {
                pGraphicsView->centerOn(scenePosCenter.x(), scenePosCenter.y() - difference);
            }
        }
        break;

    case Qt::Key_Right:
        if (pBattleMap->getNumberColumns() > pBattleMapSceneSection->getIndexFirstColumnSceneSection() + pBattleMapSceneSection->getNumberColumnsSceneSection())
        {
            pBattleMapSceneSection->setIndexFirstColumnSceneSection(pBattleMapSceneSection->getIndexFirstColumnSceneSection() + 1U);
            updateBattleMapSceneSection();

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            difference = static_cast<qreal>((pBattleMapSceneSection->getIndexFirstColumnSceneSection() + pBattleMapSceneSection->getNumberColumnsSceneSection())* CONFIG_BATTLEMAPSQUARE_SIZE -
                                            pGraphicsView->mapToScene(pGraphicsView->viewport()->rect().bottomRight()).x());

            if (0 < difference)
            {
                pGraphicsView->centerOn(scenePosCenter.x() + difference, scenePosCenter.y());
            }
        }
        break;

    case Qt::Key_Down:
        if (pBattleMap->getNumberRows() > pBattleMapSceneSection->getIndexFirstRowSceneSection() + pBattleMapSceneSection->getNumberRowsSceneSection())
        {
            pBattleMapSceneSection->setIndexFirstRowSceneSection(pBattleMapSceneSection->getIndexFirstRowSceneSection() + 1U);
            updateBattleMapSceneSection();

            /* center graphics view on new position of scene center if border of Battle Map scene section is moved outside the viewport */
            difference = static_cast<qreal>((pBattleMapSceneSection->getIndexFirstRowSceneSection() + pBattleMapSceneSection->getNumberRowsSceneSection())* CONFIG_BATTLEMAPSQUARE_SIZE) -
                    pGraphicsView->mapToScene(pGraphicsView->viewport()->rect().bottomRight()).y();

            if (0 < difference)
            {
                pGraphicsView->centerOn(scenePosCenter.x(),  scenePosCenter.y() + difference);
            }
        }
        break;

    default:
        break;
    }
}

/*!
 * \brief This function handles a click of the right mouse button.
 */
void MasterScreenHandler::clicked_RightMouseButton(QPoint position)
{
    for (QGraphicsItem * item : pBattleMapScene->items(pGraphicsView->mapToScene(position)))
    {
        if (item->flags().testFlag(QGraphicsItem::ItemIsSelectable) && !item->isSelected())
        {
            handleSelect(pGraphicsView->mapToScene(position), pGraphicsView->mapToScene(position));
        }
    }
}

/*!
 * \brief This function handles the selection of some Battle Map squares.
 */
void MasterScreenHandler::selected_BattleMapSquares()
{
    switch (m_operationMode)
    {
    case Select:
        handleSelect(pBattleMapScene->getScenePosPress(), pBattleMapScene->getScenePosRelease());
        break;
    case CoverBattleMap:
        handleSelect(pBattleMapScene->getScenePosPress(), pBattleMapScene->getScenePosRelease());
        handleCoverBattleMap(true);
        break;
    case UncoverBattleMap:
        handleSelect(pBattleMapScene->getScenePosPress(), pBattleMapScene->getScenePosRelease());
        handleCoverBattleMap(false);
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

            /* make Battle Mal square selectable */
            m_battleMapSquaresGraphicsItems[rowIdx][columnIdx]->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
    }
}

/*!
 * \brief This function updates the Battle Map scene section.
 */
void MasterScreenHandler::updateBattleMapSceneSection()
{
    /* Update the rect that frames the Battle Map scene section to be displayed on the player screen */
    m_sceneSectionRect.setRect(QRectF(QPointF(pBattleMapSceneSection->getIndexFirstColumnSceneSection(), pBattleMapSceneSection->getIndexFirstRowSceneSection()) * CONFIG_BATTLEMAPSQUARE_SIZE,
                                      QSize(pBattleMapSceneSection->getNumberColumnsSceneSection(), pBattleMapSceneSection->getNumberRowsSceneSection()) * CONFIG_BATTLEMAPSQUARE_SIZE));

    /* Update the opacity of the Battle Map squares depending on whether they are displayed on the player screen */
    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            if ((rowIdx < pBattleMapSceneSection->getIndexFirstRowSceneSection()) || (pBattleMapSceneSection->getIndexFirstRowSceneSection() + pBattleMapSceneSection->getNumberRowsSceneSection() - 1U < rowIdx) ||
                    (columnIdx < pBattleMapSceneSection->getIndexFirstColumnSceneSection()) || (pBattleMapSceneSection->getIndexFirstColumnSceneSection() + pBattleMapSceneSection->getNumberColumnsSceneSection() - 1U < columnIdx))
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

/*!
 * \brief This function handles the selection of some Battle Map squares in case of operation mode Select.
 */
void MasterScreenHandler::handleSelect(QPointF positionPress, QPointF positionRelease)
{
    /* Check if Ctrl key on the keyboard is pressed */
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
        /* Select single Battle Map square */
        if (itemSelectionOperation == Qt::ReplaceSelection)
        {
            resetSelectionArea();
        }

        for (QGraphicsItem * item : pBattleMapScene->items(positionPress))
        {
            item->setSelected(true);
        }
    }
    else
    {
        /* Select multiple Battle Map squares */
        QPainterPath path;
        path.addRect(QRectF(positionPress, positionRelease));
        pBattleMapScene->setSelectionArea(path, itemSelectionOperation);
    }

    /* Stack selected items on top of unselected items so that selection rectangle is completely visible */
    for (QGraphicsItem * item : pBattleMapScene->items())
    {
        if (item->isSelected())
        {
            item->setZValue(0.0);
        }
        else
        {
            item->setZValue(-1.0);
        }
    }
}

/*!
 * \brief This function handles resets the selection area.
 */
void MasterScreenHandler::resetSelectionArea()
{
    for (QGraphicsItem * selectedItem : pBattleMapScene->selectedItems())
    {
        selectedItem->setSelected(false);
        selectedItem->setZValue(0.0);
    }
}
