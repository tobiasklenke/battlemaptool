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
    pUserInterface(new Ui::MainWindow),
    pOperationModeActionGroup(new QActionGroup(this)),
    pWindRoseOrientationActionGroup(new QActionGroup(this)),
    pDialog_NewBattleMap(nullptr),
    pBattleMap(new BattleMap())
{
    pUserInterface->setupUi(this);

    m_masterScreenHandler.setGraphicsView(pUserInterface->GraphicsView_BattleMapMasterScreen);
    m_masterScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);
    m_playerScreenHandler.setGraphicsView(playerWindow);
    m_playerScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);

    /* create exclusive action group for operation mode */
    pOperationModeActionGroup->addAction(pUserInterface->Mode_Select);
    pOperationModeActionGroup->addAction(pUserInterface->Mode_CoverBattleMap);
    pOperationModeActionGroup->addAction(pUserInterface->Mode_UncoverBattleMap);
    pOperationModeActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);

    /* create exclusive action group for wind rose orientation */
    pWindRoseOrientationActionGroup->addAction(pUserInterface->Action_WindRoseOrientationNorth);
    pWindRoseOrientationActionGroup->addAction(pUserInterface->Action_WindRoseOrientationEast);
    pWindRoseOrientationActionGroup->addAction(pUserInterface->Action_WindRoseOrientationSouth);
    pWindRoseOrientationActionGroup->addAction(pUserInterface->Action_WindRoseOrientationWest);
    pWindRoseOrientationActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);

    /* connect signals and slots of the main window actions */
    connect(pUserInterface->Action_NewBattleMap, SIGNAL(triggered()), this, SLOT(triggered_Action_NewBattleMap()));
    connect(pUserInterface->Action_Quit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    connect(pUserInterface->Action_UpdatePlayerScreen, SIGNAL(triggered()), this, SLOT(triggered_Action_UpdatePlayerScreen()));
    connect(pUserInterface->Action_WindRoseOrientationNorth, SIGNAL(triggered()), this, SLOT(triggered_Action_WindRoseOrientation()));
    connect(pUserInterface->Action_WindRoseOrientationEast, SIGNAL(triggered()), this, SLOT(triggered_Action_WindRoseOrientation()));
    connect(pUserInterface->Action_WindRoseOrientationSouth, SIGNAL(triggered()), this, SLOT(triggered_Action_WindRoseOrientation()));
    connect(pUserInterface->Action_WindRoseOrientationWest, SIGNAL(triggered()), this, SLOT(triggered_Action_WindRoseOrientation()));
    connect(pUserInterface->Mode_Select, SIGNAL(toggled(bool)), this, SLOT(toggled_Mode_Select(bool)));
    connect(pUserInterface->Mode_CoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_Mode_CoverBattleMap(bool)));
    connect(pUserInterface->Action_CoverBattleMap, SIGNAL(triggered()), this, SLOT(triggered_Action_CoverBattleMap()));
    connect(pUserInterface->Mode_UncoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_Mode_UncoverBattleMap(bool)));
    connect(pUserInterface->Action_UncoverBattleMap, SIGNAL(triggered()), this, SLOT(triggered_Action_UncoverBattleMap()));

    connect(pUserInterface->GraphicsView_BattleMapMasterScreen, SIGNAL(changed_ScaleFactor(qreal)), this, SLOT(changed_ScaleFactor(qreal)));
    connect(pUserInterface->GraphicsView_BattleMapMasterScreen, SIGNAL(clicked_RightMouseButton(QPoint)), this, SLOT(clicked_RightMouseButton(QPoint)));

    pUserInterface->Label_WindRose->setVisible(false);
    pUserInterface->Label_ScaleFactor->setVisible(false);
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    delete pUserInterface;
    delete pOperationModeActionGroup;
    delete pWindRoseOrientationActionGroup;
    delete pBattleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles the action Action_NewBattleMap and opens the dialog Dialog_NewBattleMap.
 */
void MainWindow::triggered_Action_NewBattleMap()
{
    pDialog_NewBattleMap = new Dialog_NewBattleMap(this);

    /* connect signals and slots of the dialog button box actions of the dialog */
    connect(pDialog_NewBattleMap, SIGNAL(accepted()), this, SLOT(accepted_Dialog_NewBattleMap()));
    connect(pDialog_NewBattleMap, SIGNAL(rejected()), this, SLOT(rejected_Dialog_NewBattleMap()));

    pDialog_NewBattleMap->open();
}

/*!
 * \brief This function handles the acceptance of the dialog Dialog_NewBattleMap.
 */
void MainWindow::accepted_Dialog_NewBattleMap()
{
    setCursor(Qt::WaitCursor);

    /* reset Battle Map */
    delete pBattleMap;
    pBattleMap = new BattleMap(*pDialog_NewBattleMap->getBattleMap());
    delete pDialog_NewBattleMap;

    /* set parameters of Battle Map scene section */
    m_battleMapSceneSection.setIndexFirstRowSceneSection(0U);
    m_battleMapSceneSection.setIndexFirstColumnSceneSection(0U);
    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));

    if (numberRowsOnPlayerScreen < pBattleMap->getNumberRows())
    {
        m_battleMapSceneSection.setNumberRowsSceneSection(numberRowsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection.setNumberRowsSceneSection(pBattleMap->getNumberRows());
    }

    if (numberColumnsOnPlayerScreen < pBattleMap->getNumberColumns())
    {
        m_battleMapSceneSection.setNumberColumnsSceneSection(numberColumnsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection.setNumberColumnsSceneSection(pBattleMap->getNumberColumns());
    }

    /* share Battle Map with screen handlers */
    m_masterScreenHandler.setBattleMap(pBattleMap);
    m_playerScreenHandler.setBattleMap(pBattleMap);
    m_masterScreenHandler.showBattleMapImage();
    m_playerScreenHandler.initBattleMapImage();

    pUserInterface->Action_UpdatePlayerScreen->setEnabled(true);

    pUserInterface->SubMenu_WindRoseOrientation->setEnabled(true);
    for (QAction *action : pWindRoseOrientationActionGroup->actions())
    {
        action->setEnabled(true);
    }

    for (QAction *action : pOperationModeActionGroup->actions())
    {
        action->setEnabled(true);
    }
    pUserInterface->Mode_Select->setChecked(true);

    pUserInterface->Label_ScaleFactor->setVisible(true);

    setCursor(Qt::ArrowCursor);
}

/*!
 * \brief This function handles the rejection of the dialog Dialog_NewBattleMap.
 */
void MainWindow::rejected_Dialog_NewBattleMap()
{
    delete pDialog_NewBattleMap;
}

/*!
 * \brief This function handles the action Action_UpdatePlayerScreen and updates the player screen.
 */
void MainWindow::triggered_Action_UpdatePlayerScreen()
{
    m_playerScreenHandler.updateBattleMapImage();
}

/*!
 * \brief This function handles the actions Action_WindRoseOrientationNorth to Action_WindRoseOrientationWest.
 */
void MainWindow::triggered_Action_WindRoseOrientation()
{
    qreal orientation;

    if (pUserInterface->Action_WindRoseOrientationNorth->isChecked())
    {
        orientation = WINDROSEORIENTATIONNORTH_DEGREES;
        pUserInterface->Label_WindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (pUserInterface->Action_WindRoseOrientationEast->isChecked())
    {
        orientation = WINDROSEORIENTATIONEAST_DEGREES;
        pUserInterface->Label_WindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (pUserInterface->Action_WindRoseOrientationSouth->isChecked())
    {
        orientation = WINDROSEORIENTATIONSOUTH_DEGREES;
        pUserInterface->Label_WindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (pUserInterface->Action_WindRoseOrientationWest->isChecked())
    {
        orientation = WINDROSEORIENTATIONWEST_DEGREES;
        pUserInterface->Label_WindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else
    {
        orientation = WINDROSEORIENTATIONNORTH_DEGREES;
        pUserInterface->Label_WindRose->setVisible(false);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(false);
    }

    /* rotate the wind rose image according to the chosen wind rose orientation */
    QImage windRoseImage = QImage(WINDROSEIMAGE_SOURCE).transformed(QTransform().rotate(orientation));

    /* set the wind rose pixmap to the screen handlers */
    pUserInterface->Label_WindRose->setPixmap(QPixmap::fromImage(windRoseImage).scaled(pUserInterface->Label_WindRose->size()));
    m_playerScreenHandler.setWindRoseGraphicsItemPixmap(QPixmap::fromImage(windRoseImage));
}

/*!
 * \brief This function handles a toggle of Mode_Select.
 */
void MainWindow::toggled_Mode_Select(bool checked)
{
    if(checked)
    {
        m_masterScreenHandler.setOperationMode(Select);
        m_playerScreenHandler.setOperationMode(Select);
    }
}

/*!
 * \brief This function handles a toggle of Mode_CoverBattleMap.
 */
void MainWindow::toggled_Mode_CoverBattleMap(bool checked)
{
    if(checked)
    {
        m_masterScreenHandler.setOperationMode(CoverBattleMap);
        m_playerScreenHandler.setOperationMode(CoverBattleMap);
    }
}

/*!
 * \brief This function handles the action Action_CoverBattleMap and covers the selected Battle Map squares on the master screen.
 */
void MainWindow::triggered_Action_CoverBattleMap()
{
    m_masterScreenHandler.handleCoverBattleMap(true);
}

/*!
 * \brief This function handles a toggle of Mode_UncoverBattleMap.
 */
void MainWindow::toggled_Mode_UncoverBattleMap(bool checked)
{
    if(checked)
    {
        m_masterScreenHandler.setOperationMode(UncoverBattleMap);
        m_playerScreenHandler.setOperationMode(UncoverBattleMap);
    }
}

/*!
 * \brief This function handles the action Action_UncoverBattleMap and uncovers the selected Battle Map squares on the master screen.
 */
void MainWindow::triggered_Action_UncoverBattleMap()
{
    m_masterScreenHandler.handleCoverBattleMap(false);
}

/*!
 * \brief This function updates the label that shows the value of the scale factor.
 */
void MainWindow::changed_ScaleFactor(qreal scaleFactor)
{
    pUserInterface->Label_ScaleFactor->setText(QString::number(static_cast<quint32>(scaleFactor * HUNDRED_PERCENTAGE)) + QString("%"));
}

/*!
 * \brief This function handles a click of the right mouse button.
 */
void MainWindow::clicked_RightMouseButton(QPoint position)
{
    /* check whether the mouse button click was positioned at the Battle Map scene */
    QPointF positionOnScene = pUserInterface->GraphicsView_BattleMapMasterScreen->mapToScene(position);
    if ((0 <= positionOnScene.x()) && (positionOnScene.x() <= pUserInterface->GraphicsView_BattleMapMasterScreen->scene()->width()) &&
            (0 <= positionOnScene.y()) && (positionOnScene.y() <= pUserInterface->GraphicsView_BattleMapMasterScreen->scene()->height()))
    {
        QMenu *menu = new QMenu();
        menu->setAttribute(Qt::WA_DeleteOnClose);

        menu->addAction(pUserInterface->Action_CoverBattleMap);
        menu->addAction(pUserInterface->Action_UncoverBattleMap);

        menu->popup(pUserInterface->GraphicsView_BattleMapMasterScreen->viewport()->mapToGlobal(position));
    }
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
