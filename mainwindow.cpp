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
    pDialog_NewBattleMap(nullptr),
    pBattleMap(new BattleMap())
{
    pUserInterface->setupUi(this);

    m_masterScreenHandler.setGraphicsView(pUserInterface->GraphicsView_BattleMapMasterScreen);
    m_masterScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);
    m_playerScreenHandler.setGraphicsView(playerWindow);
    m_playerScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);

    /* connect signals and slots of the main window actions */
    connect(pUserInterface->Action_NewBattleMap, SIGNAL(triggered()), this, SLOT(triggered_Action_NewBattleMap()));
    connect(pUserInterface->Action_Quit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    connect(pUserInterface->Action_UpdatePlayerScreen, SIGNAL(triggered()), this, SLOT(triggered_Action_UpdatePlayerScreen()));
    connect(pUserInterface->Action_Select, SIGNAL(toggled(bool)), this, SLOT(toggled_Action_Select(bool)));
    connect(pUserInterface->Action_CoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_Action_CoverBattleMap(bool)));
    connect(pUserInterface->Action_UncoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_Action_UncoverBattleMap(bool)));

    connect(pUserInterface->GraphicsView_BattleMapMasterScreen, SIGNAL(changed_ScaleFactor(qreal)), this, SLOT(changed_ScaleFactor(qreal)));

    pUserInterface->Label_ScaleFactor->setVisible(false);
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    delete pUserInterface;
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
    pUserInterface->Action_Select->setEnabled(true);
    pUserInterface->Action_Select->setChecked(true);
    pUserInterface->Action_CoverBattleMap->setEnabled(true);
    pUserInterface->Action_UncoverBattleMap->setEnabled(true);
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
 * \brief This function handles a toggle of Action_Select.
 */
void MainWindow::toggled_Action_Select(bool checked)
{
    if(checked)
    {
        pUserInterface->Action_CoverBattleMap->setChecked(false);
        pUserInterface->Action_UncoverBattleMap->setChecked(false);

        m_masterScreenHandler.setOperationMode(Select);
        m_playerScreenHandler.setOperationMode(Select);
    }
}

/*!
 * \brief This function handles a toggle of Action_CoverBattleMap.
 */
void MainWindow::toggled_Action_CoverBattleMap(bool checked)
{
    if(checked)
    {
        pUserInterface->Action_Select->setChecked(false);
        pUserInterface->Action_UncoverBattleMap->setChecked(false);

        m_masterScreenHandler.setOperationMode(CoverBattleMap);
        m_playerScreenHandler.setOperationMode(CoverBattleMap);
    }
}

/*!
 * \brief This function handles a toggle of Action_UncoverBattleMap.
 */
void MainWindow::toggled_Action_UncoverBattleMap(bool checked)
{
    if(checked)
    {
        pUserInterface->Action_Select->setChecked(false);
        pUserInterface->Action_CoverBattleMap->setChecked(false);

        m_masterScreenHandler.setOperationMode(UncoverBattleMap);
        m_playerScreenHandler.setOperationMode(UncoverBattleMap);
    }
}

/*!
 * \brief This function updates the label that shows the value of the scale factor.
 */
void MainWindow::changed_ScaleFactor(qreal scaleFactor)
{
    pUserInterface->Label_ScaleFactor->setText(QString::number(static_cast<quint32>(scaleFactor * HUNDRED_PERCENTAGE)) + QString("%"));
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
