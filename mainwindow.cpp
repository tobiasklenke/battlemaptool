/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class MainWindow.
 */
MainWindow::MainWindow(QGraphicsView *playerWindow, QWidget *parent) :
    QMainWindow(parent),
    m_userInterface(new Ui::MainWindow),
    m_operationModeActionGroup(new QActionGroup(this)),
    m_windRoseOrientationActionGroup(new QActionGroup(this)),
    m_dialogNewBattleMap(nullptr),
    m_battleMap(new BattleMap())
{
    /* set up the user interface */
    m_userInterface->setupUi(this);

    /* pass graphics views and Battle Map scene sections to master and player screen handlers */
    m_masterScreenHandler.setGraphicsView(m_userInterface->graphicsViewBattleMapMasterScreen);
    m_masterScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);
    m_playerScreenHandler.setGraphicsView(playerWindow);
    m_playerScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);

    /* create action group for operation mode */
    m_operationModeActionGroup->addAction(m_userInterface->modeSelect);
    m_operationModeActionGroup->addAction(m_userInterface->modeCoverBattleMap);
    m_operationModeActionGroup->addAction(m_userInterface->modeUncoverBattleMap);
    m_operationModeActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);

    /* create action group for wind rose orientation */
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationNorth);
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationEast);
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationSouth);
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationWest);
    m_windRoseOrientationActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);

    /* connect signals and slots of actions from menu File */
    connect(m_userInterface->actionNewBattleMap, SIGNAL(triggered()), this, SLOT(triggeredActionNewBattleMap()));
    connect(m_userInterface->actionQuit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    /* connect signals and slots of actions from menu Edit */
    connect(m_userInterface->actionUndo, SIGNAL(triggered()), this, SLOT(triggeredActionUndo()));
    connect(m_userInterface->actionRedo, SIGNAL(triggered()), this, SLOT(triggeredActionRedo()));

    /* connect signals and slots of actions from menu View */
    connect(m_userInterface->actionUpdatePlayerScreen, SIGNAL(triggered()), this, SLOT(triggeredActionUpdatePlayerScreen()));
    connect(m_userInterface->actionWindRoseOrientationNorth, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->actionWindRoseOrientationEast, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->actionWindRoseOrientationSouth, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->actionWindRoseOrientationWest, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->modeSelect, SIGNAL(toggled(bool)), this, SLOT(toggledModeSelect(bool)));
    connect(m_userInterface->modeCoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggledModeCoverBattleMap(bool)));
    connect(m_userInterface->modeUncoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggledModeUncoverBattleMap(bool)));

    /* connect signals and slots of actions from menu shown on right mouse button click */
    connect(m_userInterface->actionCoverBattleMap, SIGNAL(triggered()), this, SLOT(triggeredActionCoverBattleMap()));
    connect(m_userInterface->actionUncoverBattleMap, SIGNAL(triggered()), this, SLOT(triggeredActionUncoverBattleMap()));

    /* connect signals and slots of other user interface widges */
    connect(m_userInterface->graphicsViewBattleMapMasterScreen, SIGNAL(changedScaleFactor(qreal)), this, SLOT(changedScaleFactor(qreal)));
    connect(m_userInterface->graphicsViewBattleMapMasterScreen, SIGNAL(pressedRightMouseButton(QPoint)), this, SLOT(pressedRightMouseButton(QPoint)));

    /* make labels invisible so that they are not shown initially when there is no Battle Map */
    m_userInterface->labelWindRose->setVisible(false);
    m_userInterface->labelScaleFactor->setVisible(false);

    /* make labels transparent for mouse events so that they do not process them instead of the graphics view */
    m_userInterface->labelWindRose->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_userInterface->labelScaleFactor->setAttribute(Qt::WA_TransparentForMouseEvents);
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    /* delete objects created in the constructor except m_dialogNewBattleMap */
    delete m_userInterface;
    delete m_operationModeActionGroup;
    delete m_windRoseOrientationActionGroup;
    delete m_battleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles the action actionNewBattleMap.
 */
void MainWindow::triggeredActionNewBattleMap()
{
    /* create dialog DialogNewBattleMap */
    m_dialogNewBattleMap = new DialogNewBattleMap(this);

    /* connect signals and slots of the dialog button box actions of the dialog DialogNewBattleMap */
    connect(m_dialogNewBattleMap, SIGNAL(accepted()), this, SLOT(acceptedDialogNewBattleMap()));
    connect(m_dialogNewBattleMap, SIGNAL(rejected()), this, SLOT(rejectedDialogNewBattleMap()));

    /* open dialog DialogNewBattleMap */
    m_dialogNewBattleMap->open();
}

/*!
 * \brief This function handles the acceptance of the dialog DialogNewBattleMap.
 */
void MainWindow::acceptedDialogNewBattleMap()
{
    /* set wait cursor as the following process may take some time */
    setCursor(Qt::WaitCursor);

    /* store Battle Map from accepted dialog DialogNewBattleMap and delete dialog afterwards */
    delete m_battleMap;
    m_battleMap = new BattleMap(*m_dialogNewBattleMap->getBattleMap());
    delete m_dialogNewBattleMap;

    /* reset indexes of first row and column of Battle Map scene section */
    m_battleMapSceneSection.setIndexFirstRowSceneSection(0U);
    m_battleMapSceneSection.setIndexFirstColumnSceneSection(0U);

    /* check whether number of rows displayable on player screen is less than total number of rows of Battle Map and set number of rows of Battle Map scene section to less number */
    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    if (numberRowsOnPlayerScreen < m_battleMap->getNumberRows())
    {
        m_battleMapSceneSection.setNumberRowsSceneSection(numberRowsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection.setNumberRowsSceneSection(m_battleMap->getNumberRows());
    }

    /* check whether number of columns displayable on player screen is less than total number of columns of Battle Map and set number of columns of Battle Map scene section to less number */
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    if (numberColumnsOnPlayerScreen < m_battleMap->getNumberColumns())
    {
        m_battleMapSceneSection.setNumberColumnsSceneSection(numberColumnsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection.setNumberColumnsSceneSection(m_battleMap->getNumberColumns());
    }

    /* share Battle Map with screen handlers */
    m_masterScreenHandler.setBattleMap(m_battleMap);
    m_playerScreenHandler.setBattleMap(m_battleMap);

    /* show Battle Map image on master screen and initialize Battle Map image on player screen */
    m_masterScreenHandler.showBattleMapImage();
    m_playerScreenHandler.initBattleMapImage();

    /* enable actions that shall only be available when Battle Map is shared with screen handlers */
    m_userInterface->actionUpdatePlayerScreen->setEnabled(true);
    m_userInterface->submenuWindRoseOrientation->setEnabled(true);
    for (QAction *action : m_windRoseOrientationActionGroup->actions())
    {
        action->setEnabled(true);
    }
    for (QAction *action : m_operationModeActionGroup->actions())
    {
        action->setEnabled(true);
    }

    /* make label labelScaleFactor visible so that it is shown when Battle Map is shared with screen handlers */
    m_userInterface->labelScaleFactor->setVisible(true);

    /* reset arrow cursor as the process which takes some time is completed */
    setCursor(Qt::ArrowCursor);
}

/*!
 * \brief This function handles the rejection of the dialog Dialog_NewBattleMap.
 */
void MainWindow::rejectedDialogNewBattleMap()
{
    /* delete dialog DialogNewBattleMap */
    delete m_dialogNewBattleMap;
}

/*!
 * \brief This function handles the action actionUndo.
 */
void MainWindow::triggeredActionUndo()
{
    //TODO  implement undo framework

    qDebug() << __func__;
}

/*!
 * \brief This function handles the action actionUndo.
 */
void MainWindow::triggeredActionRedo()
{
    //TODO  implement undo framework

    qDebug() << __func__;
}

/*!
 * \brief This function handles the action actionUpdatePlayerScreen.
 */
void MainWindow::triggeredActionUpdatePlayerScreen()
{
    /*  update Battle Map image on player screen */
    m_playerScreenHandler.updateBattleMapImage();
}

/*!
 * \brief This function handles the actions actionWindRoseOrientationNorth to actionWindRoseOrientationWest.
 */
void MainWindow::triggeredActionWindRoseOrientation()
{
    qreal orientation;

    /* choose wind rose orientation depending on action and update visibility of wind rose on master and player screen */
    if (m_userInterface->actionWindRoseOrientationNorth->isChecked())
    {
        orientation = WINDROSEORIENTATIONNORTH_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (m_userInterface->actionWindRoseOrientationEast->isChecked())
    {
        orientation = WINDROSEORIENTATIONEAST_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (m_userInterface->actionWindRoseOrientationSouth->isChecked())
    {
        orientation = WINDROSEORIENTATIONSOUTH_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (m_userInterface->actionWindRoseOrientationWest->isChecked())
    {
        orientation = WINDROSEORIENTATIONWEST_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else
    {
        orientation = WINDROSEORIENTATIONNORTH_DEGREES;
        m_userInterface->labelWindRose->setVisible(false);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(false);
    }

    /* rotate wind rose image according to chosen wind rose orientation */
    QImage windRoseImage = QImage(WINDROSEIMAGE_SOURCE).transformed(QTransform().rotate(orientation));

    /* set wind rose pixmap to screen handlers */
    m_userInterface->labelWindRose->setPixmap(QPixmap::fromImage(windRoseImage).scaled(m_userInterface->labelWindRose->size()));
    m_playerScreenHandler.setWindRoseGraphicsItemPixmap(QPixmap::fromImage(windRoseImage));
}

/*!
 * \brief This function handles a toggle of modeSelect.
 */
void MainWindow::toggledModeSelect(bool checked)
{
    if(checked)
    {
        /* set operation mode of master and player screen handlers to Select */
        m_masterScreenHandler.setOperationMode(Select);
        m_playerScreenHandler.setOperationMode(Select);
    }
}

/*!
 * \brief This function handles a toggle of modeCoverBattleMap.
 */
void MainWindow::toggledModeCoverBattleMap(bool checked)
{
    if(checked)
    {
        /* set operation mode of master and player screen handlers to CoverBattleMap */
        m_masterScreenHandler.setOperationMode(CoverBattleMap);
        m_playerScreenHandler.setOperationMode(CoverBattleMap);
    }
}

/*!
 * \brief This function handles the action actionCoverBattleMap.
 */
void MainWindow::triggeredActionCoverBattleMap()
{
    /* cover selected Battle Map squares on master screen */
    m_masterScreenHandler.handleCoverBattleMap(true);
}

/*!
 * \brief This function handles a toggle of modeUncoverBattleMap.
 */
void MainWindow::toggledModeUncoverBattleMap(bool checked)
{
    if(checked)
    {
        /* set operation mode of master and player screen handlers to UncoverBattleMap */
        m_masterScreenHandler.setOperationMode(UncoverBattleMap);
        m_playerScreenHandler.setOperationMode(UncoverBattleMap);
    }
}

/*!
 * \brief This function handles the action actionUncoverBattleMap.
 */
void MainWindow::triggeredActionUncoverBattleMap()
{
    /* uncover selected Battle Map squares on master screen */
    m_masterScreenHandler.handleCoverBattleMap(false);
}

/*!
 * \brief This function updates the label that shows the value of the scale factor.
 */
void MainWindow::changedScaleFactor(qreal scaleFactor)
{
    m_userInterface->labelScaleFactor->setText(QString::number(static_cast<quint32>(scaleFactor * HUNDRED_PERCENTAGE)) + QString("%"));
}

/*!
 * \brief This function handles a press of the right mouse button.
 */
void MainWindow::pressedRightMouseButton(QPoint position)
{
    /* check whether the mouse button press was positioned at the Battle Map scene */
    QPointF positionOnScene = m_userInterface->graphicsViewBattleMapMasterScreen->mapToScene(position);
    if ((0 <= positionOnScene.x()) && (positionOnScene.x() <= m_userInterface->graphicsViewBattleMapMasterScreen->scene()->width()) &&
            (0 <= positionOnScene.y()) && (positionOnScene.y() <= m_userInterface->graphicsViewBattleMapMasterScreen->scene()->height()))
    {
        /* create menu, add actions and show it at right mouse button press position */
        QMenu *menu = new QMenu();
        menu->setAttribute(Qt::WA_DeleteOnClose);
        menu->addAction(m_userInterface->actionCoverBattleMap);
        menu->addAction(m_userInterface->actionUncoverBattleMap);
        menu->popup(m_userInterface->graphicsViewBattleMapMasterScreen->viewport()->mapToGlobal(position));
    }
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
